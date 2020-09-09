#ifndef _OP_PACKETIO_DPDK_EAL_HPP_
#define _OP_PACKETIO_DPDK_EAL_HPP_

#include <map>
#include <memory>
#include <optional>
#include <vector>
#include <variant>

#include "packetio/generic_port.hpp"

struct rte_ring;

namespace openperf::packetio::dpdk {

class pool_allocator;

template <typename PortHandler> struct primary_process
{
    std::unique_ptr<pool_allocator> m_allocator;

    std::map<uint16_t, std::string> init();
    void shutdown();
};

struct test_port_process : primary_process<test_port_process>
{
    struct rte_ring_deleter
    {
        void operator()(rte_ring*);
    };

    using ring_ptr = std::unique_ptr<rte_ring, rte_ring_deleter>;
    using ring_pair = std::pair<ring_ptr, ring_ptr>;

    std::vector<ring_pair> m_ring_pairs;

    void do_setup();
};

struct live_port_process : primary_process<live_port_process>
{
    void do_callbacks();
    void do_shutdown();
};

struct secondary_process
{
    std::map<uint16_t, std::string> init();
    void shutdown();
};

using process_type =
    std::variant<test_port_process, live_port_process, secondary_process>;

class eal
{
public:
    eal();
    ~eal();

    /* This object is basically a non-copyable singleton */
    eal& operator=(eal&& other) noexcept;
    eal(eal&& other) noexcept;

    eal(const eal&) = delete;
    eal& operator=(const eal&&) = delete;

    std::vector<std::string> port_ids() const;
    std::optional<port::generic_port> port(std::string_view id) const;
    std::optional<int> port_index(std::string_view id) const;

    tl::expected<std::string, std::string>
    create_port(std::string_view id, const port::config_data& config);
    tl::expected<void, std::string> delete_port(std::string_view id);

    void start_all_ports() const;
    void stop_all_ports() const;

private:
    process_type m_process;
    std::map<uint16_t, std::string> m_port_ids;
    std::map<uint16_t, std::string> m_bond_ports;
};

} // namespace openperf::packetio::dpdk

#endif /* _OP_PACKETIO_DPDK_EAL_HPP_ */
