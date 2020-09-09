#include <algorithm>
#include <numeric>

#include "core/op_common.h"
#include "core/op_log.h"
#include "config/op_config_utils.hpp"
#include "dpdk_proc_shim/api.h"
#include "packetio/drivers/dpdk/arg_parser.hpp"
#include "packetio/drivers/dpdk/eal.hpp"
#include "packetio/drivers/dpdk/mbuf_rx_prbs.hpp"
#include "packetio/drivers/dpdk/mbuf_signature.hpp"
#include "packetio/drivers/dpdk/mbuf_tx.hpp"
#include "packetio/drivers/dpdk/model/core_mask.hpp"
#include "packetio/drivers/dpdk/model/physical_port.hpp"
#include "packetio/drivers/dpdk/topology_utils.hpp"
#include "packetio/memory/dpdk/pool_allocator.hpp"
#include "utils/overloaded_visitor.hpp"

namespace openperf::packetio::dpdk {

/***
 * Various DPDK static functions
 ***/

static void log_port(uint16_t idx, std::string_view id)
{
    auto mac_addr = rte_ether_addr{};
    rte_eth_macaddr_get(idx, &mac_addr);

    auto info = model::port_info(idx);

    if (auto if_name = info.interface_name()) {
        OP_LOG(OP_LOG_INFO,
               "Port index %u is using id = %.*s (MAC = "
               "%02x:%02x:%02x:%02x:%02x:%02x, driver = %s attached to %s)",
               idx,
               static_cast<int>(id.length()),
               id.data(),
               mac_addr.addr_bytes[0],
               mac_addr.addr_bytes[1],
               mac_addr.addr_bytes[2],
               mac_addr.addr_bytes[3],
               mac_addr.addr_bytes[4],
               mac_addr.addr_bytes[5],
               info.driver_name().c_str(),
               if_name.value().c_str());
    } else {
        OP_LOG(OP_LOG_INFO,
               "Port index %u is using id = %.*s (MAC = "
               "%02x:%02x:%02x:%02x:%02x:%02x, driver = %s)",
               idx,
               static_cast<int>(id.length()),
               id.data(),
               mac_addr.addr_bytes[0],
               mac_addr.addr_bytes[1],
               mac_addr.addr_bytes[2],
               mac_addr.addr_bytes[3],
               mac_addr.addr_bytes[4],
               mac_addr.addr_bytes[5],
               info.driver_name().c_str());
    }
}

static int log_link_status_change(uint16_t port_id,
                                  rte_eth_event_type event
                                  __attribute__((unused)),
                                  void* cb_arg __attribute__((unused)),
                                  void* ret_param __attribute__((unused)))
{
    assert(event == RTE_ETH_EVENT_INTR_LSC);
    struct rte_eth_link link;
    rte_eth_link_get_nowait(port_id, &link);
    if (link.link_status == ETH_LINK_UP) {
        OP_LOG(OP_LOG_INFO,
               "Port %u Link Up - speed %u Mbps - %s-duplex\n",
               port_id,
               link.link_speed,
               link.link_duplex == ETH_LINK_FULL_DUPLEX ? "full" : "half");
    } else {
        OP_LOG(OP_LOG_INFO, "Port %u Link Down\n", port_id);
    }

    return (0);
}

static void log_idle_workers(const std::vector<queue::descriptor>& descriptors)
{
    /* Generate a mask for all available cores */
    auto eal_mask = model::core_mask{};
    unsigned lcore_id = 0;
    RTE_LCORE_FOREACH_SLAVE (lcore_id) {
        eal_mask.set(lcore_id);
    }
    const auto worker_count = eal_mask.count();

    /* Clear the bits used to support port queues */
    std::for_each(std::begin(descriptors),
                  std::end(descriptors),
                  [&](const auto& d) { eal_mask.reset(d.worker_id); });

    /* Clear the bit used by the stack */
    eal_mask.reset(topology::get_stack_lcore_id());

    /* Warn if we are unable to use any of our available cores */
    if (eal_mask.count()) {
        OP_LOG(OP_LOG_WARNING,
               "Only utilizing %zu of %zu available workers\n",
               worker_count - eal_mask.count(),
               worker_count);
    }
}

static void
configure_all_ports(const std::map<uint16_t, queue::count>& port_queue_counts,
                    const pool_allocator* allocator,
                    const std::map<uint16_t, std::string>& id_name)
{
    assert(rte_eal_process_type() == RTE_PROC_PRIMARY);

    uint16_t port_id = 0;
    RTE_ETH_FOREACH_DEV (port_id) {
        auto info = model::port_info(port_id);
        auto mempool = allocator->rx_mempool(info.socket_id());
        auto port = model::physical_port(port_id, id_name.at(port_id), mempool);

        const auto cursor = port_queue_counts.find(port_id);
        if (cursor == port_queue_counts.end()) {
            throw std::runtime_error(
                "No worker threads available for port "
                + std::to_string(port_id)
                + ". Do you need to adjust your core mask?\n");
        }
        const auto& q_count = cursor->second;
        if (auto result = port.low_level_config(q_count.rx, q_count.tx);
            !result) {
            throw std::runtime_error(result.error());
        }
    }
}

static void sanity_check_environment()
{
    if (rte_lcore_count() <= 1) {
        throw std::runtime_error("No DPDK workers cores are available! "
                                 "At least 2 CPU cores are required.");
    }

    const auto misc_mask =
        config::misc_core_mask().value_or(model::core_mask{});
    const auto rx_mask = config::rx_core_mask().value_or(model::core_mask{});
    const auto tx_mask = config::tx_core_mask().value_or(model::core_mask{});
    const auto user_mask = misc_mask | rx_mask | tx_mask;

    if (user_mask[rte_get_master_lcore()]) {
        throw std::runtime_error("User specified mask, "
                                 + model::to_string(user_mask)
                                 + ", conflicts with DPDK master core "
                                 + std::to_string(rte_get_master_lcore()));
    }
}

constexpr const char* dpdk_logtype(int logtype)
{
    /* Current as of DPDK release 18.08 */
    constexpr const char* logtype_strings[] = {
        "lib.eal",   "lib.malloc",    "lib.ring",  "lib.mempool",
        "lib.timer", "pmd",           "lib.hash",  "lib.lpm",
        "lib.kni",   "lib.acl",       "lib.power", "lib.meter",
        "lib.sched", "lib.port",      "lib.table", "lib.pipeline",
        "lib.mbuf",  "lib.cryptodev", "lib.efd",   "lib.eventdev",
        "lib.gso",   "reserved1",     "reserved2", "reserved3",
        "user1",     "user2",         "user3",     "user4",
        "user5",     "user6",         "user7",     "user8"};

    return ((logtype >= 0
             && logtype < static_cast<int>(op_count_of(logtype_strings)))
                ? logtype_strings[logtype]
                : "unknown");
}

constexpr enum op_log_level dpdk_loglevel(int loglevel)
{
    /*
     * This should be kept in sync with the inferred log levels found in the
     * argument parser.
     */
    switch (loglevel) {
    case RTE_LOG_EMERG:
        return OP_LOG_CRITICAL;
    case RTE_LOG_ALERT:
        return OP_LOG_ERROR;
    case RTE_LOG_CRIT:
        return OP_LOG_WARNING;
    case RTE_LOG_ERR:
        return OP_LOG_INFO;
    case RTE_LOG_WARNING:
    case RTE_LOG_NOTICE:
    case RTE_LOG_INFO:
        return OP_LOG_DEBUG;
    case RTE_LOG_DEBUG:
        return OP_LOG_TRACE;
    default:
        return OP_LOG_NONE;
    }
}

static ssize_t eal_log_write(void* cookie __attribute__((unused)),
                             const char* buf,
                             size_t size)
{
    /*
     * The manpage says size == 0 is an error (by corollary) but dare
     * we not check?
     */
    if (size == 0) return (0);

    /*
     * op_log needs all of the messages to be terminated with a new-line, so fix
     * up any messages that lack such niceties.
     */
    const char* format = (buf[size - 1] == '\n') ? "%.*s" : "%.*s\n";

    /*
     * We can't grab the right function with a macro, so call the
     * actual function and provide the logtype instead.
     */
    op_log(dpdk_loglevel(rte_log_cur_msg_loglevel()),
           dpdk_logtype(rte_log_cur_msg_logtype()),
           format,
           static_cast<int>(size),
           buf);

    return (size);
}

/***
 * Utility templates
 ***/
namespace impl {

template <typename, typename = std::void_t<>>
struct has_do_setup : std::false_type
{};

template <typename T>
struct has_do_setup<T, std::void_t<decltype(std::declval<T>().do_setup())>>
    : std::true_type
{};

template <typename, typename = std::void_t<>>
struct has_do_callbacks : std::false_type
{};

template <typename T>
struct has_do_callbacks<T,
                        std::void_t<decltype(std::declval<T>().do_callbacks())>>
    : std::true_type
{};

template <typename, typename = std::void_t<>>
struct has_do_shutdown : std::false_type
{};

template <typename T>
struct has_do_shutdown<T,
                       std::void_t<decltype(std::declval<T>().do_shutdown())>>
    : std::true_type
{};

} // namespace impl

void test_port_process::rte_ring_deleter::operator()(rte_ring* ring)
{
    rte_ring_free(ring);
}

void test_port_process::do_setup()
{
    constexpr auto eth_prefix = "net_ring";
    constexpr auto ring_prefix = "test_ring";
    constexpr auto ring_flags = RING_F_SP_ENQ | RING_F_SC_DEQ;
    constexpr auto ring_slots = 256;
    constexpr auto socket_id = SOCKET_ID_ANY;

    const auto nb_test_portpairs = config::dpdk_test_portpairs();
    assert(nb_test_portpairs);

    /* Generate rings for our test ports to use */
    unsigned idx = 0;
    std::generate_n(std::back_inserter(m_ring_pairs),
                    nb_test_portpairs,
                    [&]() -> ring_pair {
                        auto name0 = ring_prefix + std::to_string(idx++);
                        auto ring0 = rte_ring_create(
                            name0.c_str(), ring_slots, socket_id, ring_flags);
                        if (!ring0) {
                            throw std::runtime_error(
                                "Failed to create test port ring " + name0);
                        }

                        auto name1 = ring_prefix + std::to_string(idx++);
                        auto ring1 = rte_ring_create(
                            name1.c_str(), ring_slots, socket_id, ring_flags);
                        if (!ring1) {
                            throw std::runtime_error(
                                "Failed to create test port ring " + name1);
                        }

                        return {ring_ptr(ring0), ring_ptr(ring1)};
                    });

    assert(m_ring_pairs.size() == nb_test_portpairs);

    /*
     * Transform our unique ptrs into raw pointers so that we can treat
     * each pointer as an array of 1. This is neccessary for the function
     * that creates the ring based ethernet devices.
     */
    auto raw_ring_pairs = std::vector<std::pair<rte_ring*, rte_ring*>>{};
    std::transform(std::begin(m_ring_pairs),
                   std::end(m_ring_pairs),
                   std::back_inserter(raw_ring_pairs),
                   [](auto& pair) -> std::pair<rte_ring*, rte_ring*> {
                       return {pair.first.get(), pair.second.get()};
                   });

    /* Finally, create test port pairs */
    idx = 0;
    std::for_each(
        std::begin(raw_ring_pairs), std::end(raw_ring_pairs), [&](auto& pair) {
            auto name0 = eth_prefix + std::to_string(idx++);
            if (rte_eth_from_rings(name0.c_str(),
                                   std::addressof(pair.first),
                                   1,
                                   std::addressof(pair.second),
                                   1,
                                   socket_id)
                == -1) {
                throw std::runtime_error(
                    "Failed to create test port device: "
                    + std::string(rte_strerror(rte_errno)));
            }

            auto name1 = eth_prefix + std::to_string(idx++);
            if (rte_eth_from_rings(name1.c_str(),
                                   std::addressof(pair.second),
                                   1,
                                   std::addressof(pair.first),
                                   1,
                                   socket_id)
                == -1) {
                throw std::runtime_error(
                    "Failed to create test port device: "
                    + std::string(rte_strerror(rte_errno)));
            }
        });
}

void live_port_process::do_callbacks()
{
    if (auto error = rte_eth_dev_callback_register(RTE_ETH_ALL,
                                                   RTE_ETH_EVENT_INTR_LSC,
                                                   log_link_status_change,
                                                   nullptr)) {
        OP_LOG(OP_LOG_WARNING,
               "Could not register link status change callback: %s\n",
               rte_strerror(std::abs(error)));
    }
}

void live_port_process::do_shutdown()
{
    rte_eth_dev_callback_unregister(
        RTE_ETH_ALL, RTE_ETH_EVENT_INTR_LSC, log_link_status_change, nullptr);
}

template <typename PortHandler>
std::map<uint16_t, std::string> primary_process<PortHandler>::init()
{
    assert(rte_eal_process_type() == RTE_PROC_PRIMARY);
    auto derived = static_cast<PortHandler*>(this);
    auto port_ids = config::dpdk_id_map();

    dps_primary_init();

    /* Perform required port setup */
    if constexpr (impl::has_do_setup<PortHandler>::value) {
        derived->do_setup();
    }

    /*
     * Load available port information; make sure that all ports
     * have ids and then use the information to generate a topology
     */
    auto port_info = topology::get_port_info();
    std::for_each(
        std::begin(port_info), std::end(port_info), [&](const auto& info) {
            if (!port_ids.count(info.id())) {
                port_ids[info.id()] = core::to_string(core::uuid::random());
            }
        });

    auto q_descriptors = topology::queue_distribute(port_info);
    log_idle_workers(q_descriptors);
    auto q_counts = queue::get_port_queue_counts(q_descriptors);

    m_allocator = std::make_unique<pool_allocator>(port_info, q_counts);

    configure_all_ports(q_counts, m_allocator.get(), port_ids);

    if constexpr (impl::has_do_callbacks<PortHandler>::value) {
        derived->do_callbacks();
    }

    return (port_ids);
}

template <typename PortHandler> void primary_process<PortHandler>::shutdown()
{
    if constexpr (impl::has_do_shutdown<PortHandler>::value) {
        static_cast<PortHandler*>(this)->do_shutdown();
    }

    dps_primary_fini();
}

std::map<uint16_t, std::string> secondary_process::init()
{
    assert(rte_eal_process_type() == RTE_PROC_SECONDARY);

    dps_secondary_init();

    auto port_ids = config::dpdk_id_map();

    /*
     * Load available port information; make sure that all ports
     * have ids and then use the information to generate a topology
     */
    auto port_info = topology::get_port_info();
    std::for_each(
        std::begin(port_info), std::end(port_info), [&](const auto& info) {
            if (!port_ids.count(info.id())) {
                port_ids[info.id()] = core::to_string(core::uuid::random());
            }

            auto mode = rte_eth_burst_mode{};
            rte_eth_rx_burst_mode_get(0, 0, &mode);
            fprintf(stderr, "Using RX mode = %s\n", mode.info);
        });

    return (port_ids);
}

void secondary_process::shutdown() { dps_secondary_fini(); }

/*
 * Perform the minimal amount of work necessary to load the DPDK environment
 * and return an object that can handle the process type correctly.
 */
static process_type bootstrap()
{
    /*
     * Create a stream so we can forward DPDK logging messages to our own
     * internal logger.
     */
    cookie_io_functions_t stream_functions = {.write = eal_log_write};
    auto stream = fopencookie(nullptr, "w+", stream_functions);
    if (!stream || rte_openlog_stream(stream) < 0) {
        throw std::runtime_error("Failed to set DPDK log stream");
    }

    /* Convert args to c-strings for DPDK consumption */
    auto args = config::dpdk_args();
    auto eal_args = std::vector<char*>{};
    eal_args.reserve(args.size() + 1);
    std::transform(std::begin(args),
                   std::end(args),
                   std::back_inserter(eal_args),
                   [](auto& s) { return s.data(); });
    eal_args.emplace_back(nullptr); /* null terminator */

    OP_LOG(OP_LOG_INFO,
           "Initializing DPDK with \\\"%s\\\"\n",
           std::accumulate(std::begin(args),
                           std::end(args),
                           std::string{},
                           [](std::string& lhs, const std::string& rhs) {
                               return (lhs += (lhs.length() ? " " : "") + rhs);
                           })
               .c_str());

    auto parsed_or_err =
        rte_eal_init(static_cast<int>(eal_args.size() - 1), eal_args.data());
    if (parsed_or_err < 0) {
        throw std::runtime_error("Failed to initialize DPDK: "
                                 + std::string(rte_strerror(rte_errno)));
    }

    /*
     * rte_eal_init returns the number of parsed arguments; warn if some
     * arguments were unparsed. We subtract two to account for the trailing
     * null and the program name.
     */
    if (parsed_or_err != static_cast<int>(eal_args.size() - 2)) {
        OP_LOG(OP_LOG_ERROR,
               "DPDK initialization function only parsed %d of %" PRIu64
               " arguments\n",
               parsed_or_err,
               eal_args.size() - 2);
    }

    switch (rte_eal_process_type()) {
    case RTE_PROC_PRIMARY:
        if (config::dpdk_test_mode()) { return (test_port_process{}); }
        return (live_port_process{});
    case RTE_PROC_SECONDARY:
        return (secondary_process{});
    default:
        throw std::runtime_error("Invalid DPDK process type");
    }
}

eal::eal()
    : m_process(bootstrap())
    , m_port_ids(std::visit([](auto& p) { return (p.init()); }, m_process))
{
    /* Verify that our environment is usable */
    sanity_check_environment();

    if (m_port_ids.empty()) {
        throw std::runtime_error("No DPDK ports are available! "
                                 "At least 1 port is required.");
    }

    /* Log port details */
    std::for_each(std::begin(m_port_ids),
                  std::end(m_port_ids),
                  [](const auto& item) { log_port(item.first, item.second); });

    /* Setup our specific mbuf features */
    mbuf_signature_init();
    mbuf_rx_prbs_init();
    mbuf_tx_init();
}

eal::eal(eal&& other) noexcept
    : m_process(std::move(other.m_process))
    , m_port_ids(std::move(other.m_port_ids))
    , m_bond_ports(std::move(other.m_bond_ports))
{}

eal& eal::operator=(eal&& other) noexcept
{
    if (this != &other) {
        m_process = std::move(other.m_process);
        m_port_ids = std::move(other.m_port_ids);
        m_bond_ports = std::move(other.m_bond_ports);
    }
    return (*this);
}

eal::~eal()
{
    if (m_port_ids.empty()) { return; }

    std::visit([](auto& p) { p.shutdown(); }, m_process);
}

std::vector<std::string> eal::port_ids() const
{
    auto ids = std::vector<std::string>{};

    std::transform(std::begin(m_port_ids),
                   std::end(m_port_ids),
                   std::back_inserter(ids),
                   [](const auto& item) { return (item.second); });

    return (ids);
}

std::optional<port::generic_port> eal::port(std::string_view id) const
{
    auto idx = port_index(id);
    if (!idx || !rte_eth_dev_is_valid_port(idx.value())) {
        return (std::nullopt);
    }

    return (
        port::generic_port(model::physical_port(idx.value(), std::string(id))));
}

std::optional<int> eal::port_index(std::string_view id) const
{
    if (auto it = std::find_if(
            std::begin(m_port_ids),
            std::end(m_port_ids),
            [id](const auto& pair) { return (pair.second == id); });
        it != std::end(m_port_ids)) {
        return (it->first);
    }

    return (std::nullopt);
}

tl::expected<std::string, std::string>
eal::create_port(std::string_view id, const port::config_data& config)
{
    static unsigned bond_idx = 0;
    /* Sanity check input */
    if (!std::holds_alternative<port::bond_config>(config)) {
        return tl::make_unexpected("Missing bond configuration data");
    }

    std::vector<int> port_indexes;
    /* Make sure that all ports in the vector actually exist */
    for (const auto& port_id : std::get<port::bond_config>(config).ports) {
        // Verify port id is valid.
        auto id_check = openperf::config::op_config_validate_id_string(port_id);
        if (!id_check) { return tl::make_unexpected(id_check.error()); }

        auto idx = port_index(port_id);
        if (!idx || !rte_eth_dev_is_valid_port(idx.value())) {
            return tl::make_unexpected("Port id " + std::string(id)
                                       + " is invalid");
        }
        port_indexes.push_back(idx.value());
    }

    /* Well all right.  Let's create a port, shall we? */
    /*
     * XXX: DPDK uses the prefix of the name to find the proper driver;
     * ergo, this name cannot change.
     */
    std::string name = "net_bonding" + std::to_string(bond_idx++);
    /**
     * Use the port ids to figure out the most common socket.  We'll use that
     * as the socket id for the bonded port.
     */
    int id_or_error =
        rte_eth_bond_create(name.c_str(),
                            BONDING_MODE_8023AD,
                            topology::get_most_common_numa_node(port_indexes));
    if (id_or_error < 0) {
        return tl::make_unexpected(
            "Failed to create bond port: "
            + std::string(rte_strerror(std::abs(id_or_error))));
    }

    std::vector<int> success_record;
    for (auto port_idx : port_indexes) {
        int error = rte_eth_bond_slave_add(id_or_error, port_idx);
        if (error) {
            for (auto added_id : success_record) {
                rte_eth_bond_slave_remove(id_or_error, added_id);
            }
            rte_eth_bond_free(name.c_str());
            return tl::make_unexpected(
                "Failed to add slave port " + std::to_string(port_idx)
                + "to bond port " + std::to_string(id_or_error) + ": "
                + std::string(rte_strerror(std::abs(error))));
        }
        success_record.push_back(port_idx);
    }

    m_bond_ports[id_or_error] = name;
    m_port_ids[id_or_error] = id;
    return (std::string(id));
}

tl::expected<void, std::string> eal::delete_port(std::string_view id)
{
    auto idx = port_index(id);
    if (!idx || !rte_eth_dev_is_valid_port(*idx)) {
        /* Deleting a non-existent port is fine */
        return {};
    }

    /* Port exists */
    auto port_idx = *idx;
    if (m_bond_ports.find(port_idx) == m_bond_ports.end()) {
        /* but it's not one we can delete */
        return tl::unexpected("Port " + std::string(id) + " cannot be deleted");
    }

    /*
     * There is apparently no way to query the number of slaves a port has,
     * so resort to brute force here.
     */
    std::array<uint16_t, RTE_MAX_ETHPORTS> slaves;
    int length_or_err =
        rte_eth_bond_slaves_get(port_idx, slaves.data(), slaves.size());
    if (length_or_err < 0) {
        /* Not sure what else we can do here... */
        OP_LOG(OP_LOG_ERROR,
               "Could not retrieve slave port ids from bonded port %s\n",
               id.data());
    } else if (length_or_err > 0) {
        for (int i = 0; i < length_or_err; i++) {
            rte_eth_bond_slave_remove(port_idx, slaves[i]);
        }
    }
    rte_eth_bond_free(m_bond_ports[port_idx].c_str());
    m_bond_ports.erase(port_idx);
    m_port_ids.erase(port_idx);
    return {};
}

void eal::start_all_ports() const
{
    auto port_info = topology::get_port_info();
    for (const auto& info : port_info) {
        model::physical_port(info.id(), m_port_ids.at(info.id())).start();
    }
}

void eal::stop_all_ports() const
{
#if 0
    auto port_info = topology::get_port_info();
    for (const auto& info : port_info) {
        model::physical_port(info.id(), m_port_ids.at(info.id())).stop();
    }
#endif
}

} // namespace openperf::packetio::dpdk
