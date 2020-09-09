#include <unordered_map>
#include <regex>

#include "tl/expected.hpp"

#include "core/op_core.h"
#include "config/op_config_file.hpp"
#include "config/op_config_prefix.hpp"
#include "packetio/drivers/dpdk/arg_parser.hpp"

#include <iostream>

namespace openperf::packetio::dpdk::config {

using namespace openperf::config;

inline constexpr std::string_view program_name = "op_eal";
inline constexpr std::string_view log_level_arg = "--log-level";
inline constexpr std::string_view file_prefix_arg = "--file-prefix";
inline constexpr std::string_view no_pci_arg = "--no-pci";

template <typename Container, typename Thing>
bool contains(const Container& c, const Thing& t)
{
    return (std::any_of(std::begin(c), std::end(c), [&](const auto& item) {
        return (item == t);
    }));
}

static void add_log_level_arg(enum op_log_level level,
                              std::vector<std::string>& args)
{
    /* Map OP log levels to DPDK log levels */
    static std::unordered_map<enum op_log_level, std::string> log_level_map = {
        {OP_LOG_NONE, "0"},     /* RTE_LOG_EMERG */
        {OP_LOG_CRITICAL, "1"}, /* RTE_LOG_ERERG */
        {OP_LOG_ERROR, "2"},    /* RTE_LOG_ALERT */
        {OP_LOG_WARNING, "3"},  /* RTE_LOG_CRIT */
        {OP_LOG_INFO, "4"},     /* RTE_LOG_ERR */
        {OP_LOG_DEBUG, "7"},    /* RTE_LOG_INFO */
        {OP_LOG_TRACE, "8"}     /* RTE_LOG_DEBUG */
    };

    args.emplace_back(log_level_arg);
    args.push_back(log_level_map[level]);
}

static void add_file_prefix_arg(std::string_view prefix,
                                std::vector<std::string>& args)
{
    args.emplace_back(file_prefix_arg);
    args.emplace_back(prefix);
}

static void add_no_pci_arg(std::vector<std::string>& args)
{
    args.emplace_back(no_pci_arg);
}

static std::optional<uint16_t> to_uint16(std::string_view input)
{
    std::stringstream ss(std::string(input), std::ios_base::in);
    uint16_t out;
    if ((ss >> out).fail()) { return (std::nullopt); }
    return (out);
}

// Split portX and return just the X part.
// Return -1 if no valid X part is found.
static std::optional<uint16_t> get_port_index(std::string_view name)
{
    auto index_offset = name.find_first_not_of("port");
    if (index_offset == std::string_view::npos) { return (std::nullopt); }

    return (to_uint16(name.substr(
        index_offset, name.find_first_not_of("0123456789", index_offset + 1))));
}

static tl::expected<std::map<uint16_t, std::string>, std::string>
process_dpdk_port_ids(const std::map<std::string, std::string>& input)
{
    auto output = std::map<uint16_t, std::string>{};

    for (auto& entry : input) {
        // split port index from "port" part.
        auto port_idx = get_port_index(entry.first);
        if (!port_idx) {
            return (tl::make_unexpected(
                std::string(entry.first) + " is not a valid port id specifier."
                + " It must have the form portX=id,"
                + " where X is the zero-based DPDK port index and"
                + " where id may only contain"
                + " lower-case letters, numbers, and hyphens."));
        }

        // check for duplicate port index.
        if (output.find(*port_idx) != output.end()) {
            return (
                tl::make_unexpected("Error: detected a duplicate port index: "
                                    + std::to_string(*port_idx)));
        }

        // check for duplicate port ID.
        auto port_id = entry.second;
        auto it =
            std::find_if(output.begin(),
                         output.end(),
                         [&port_id](const std::pair<int, std::string>& val) {
                             return val.second == port_id;
                         });
        if (it != output.end()) {
            return (tl::make_unexpected("Error: detected a duplicate port id: "
                                        + port_id));
        }

        output[*port_idx] = port_id;
    }

    return (output);
}

unsigned dpdk_test_portpairs()
{
    auto result = config::file::op_config_get_param<OP_OPTION_TYPE_LONG>(
        "modules.packetio.dpdk.test-portpairs");

    return (result.value_or(dpdk_test_mode() ? 1 : 0));
}

bool dpdk_test_mode()
{
    auto result = config::file::op_config_get_param<OP_OPTION_TYPE_NONE>(
        "modules.packetio.dpdk.test-mode");

    return (result.value_or(false));
}

/*
 * Our list argument type splits arguments on commas, however some DPDK options
 * use commas to support key=value modifiers.  This function reconstructs the
 * commas so that arguments are parsed correctly.
 */
static void add_dpdk_argument(std::vector<std::string>& args,
                              std::string_view input)
{
    if (args.empty() || input.front() == '-'
        || (!args.empty() && args.back().front() == '-')) {
        args.emplace_back(input);
    } else {
        args.back().append("." + std::string(input));
    }
}

std::vector<std::string> dpdk_args()
{
    // Add name value in straight away.
    std::vector<std::string> to_return{std::string(program_name)};

    // Get the DPDK options from the framework.
    if (auto args = config::file::op_config_get_param<OP_OPTION_TYPE_OPTIONS>(
            "modules.packetio.dpdk.options")) {
        // Walk through them and rebuild the arguments DPDK expects
        for (auto&& arg : *args) { add_dpdk_argument(to_return, arg); }
    }

    /* Append a log level option if needed */
    if (!contains(to_return, log_level_arg)) {
        add_log_level_arg(op_log_level_get(), to_return);
    }
    if (!contains(to_return, file_prefix_arg)) {
        if (auto prefix = config::get_prefix()) {
            add_file_prefix_arg(*prefix, to_return);
        }
    }
    if (dpdk_test_mode() && !contains(to_return, no_pci_arg)) {
        add_no_pci_arg(to_return);
    }

    return (to_return);
}

std::map<uint16_t, std::string> dpdk_id_map()
{
    auto src_map = config::file::op_config_get_param<OP_OPTION_TYPE_MAP>(
        "modules.packetio.dpdk.port-ids");

    if (!src_map) { return (std::map<uint16_t, std::string>{}); }

    auto to_return = process_dpdk_port_ids(*src_map);
    if (!to_return) {
        throw std::runtime_error("Could not process port id map: "
                                 + to_return.error());
    }

    return (*to_return);
}

static std::vector<uint16_t> parse_queues(std::string_view input)
{
    static constexpr auto delimiters = ",-";
    auto queues = std::vector<uint16_t>{};
    auto tmp = std::stack<uint16_t>{};

    size_t cursor = 0, end = 0;
    while ((cursor = input.find_first_not_of(delimiters, end))
           != std::string::npos) {
        end = input.find_first_of(delimiters, cursor + 1);

        if (auto value = to_uint16(input.substr(cursor, end - cursor))) {
            if (end > input.length()) { /* no more input */
                if (tmp.empty()) {
                    queues.push_back(*value);
                } else {
                    for (uint16_t i = tmp.top(); i <= *value; i++) {
                        queues.push_back(i);
                    }
                    tmp.pop();
                }
            } else { /* check delimiter */
                switch (input[end]) {
                case '-':
                    tmp.push(*value);
                    break;
                case ',':
                    queues.push_back(*value);
                    break;
                default:
                    throw std::invalid_argument("Invalid queue syntax");
                }
            }
        }
    }

    return (queues);
}

static std::map<uint16_t, std::vector<uint16_t>>
get_port_queues(std::string_view opt_name)
{
    auto map = std::map<uint16_t, std::vector<uint16_t>>{};

    auto opt_arg =
        config::file::op_config_get_param<OP_OPTION_TYPE_MAP>(opt_name);

    if (!opt_arg) { return (map); }

    for (auto&& pair : *opt_arg) {
        if (auto port_idx = get_port_index(pair.first)) {
            map[*port_idx] = parse_queues(pair.second);
        }
    }

    return (map);
}

std::map<uint16_t, std::vector<uint16_t>> rx_port_queues()
{
    assert(rte_eal_process_type() == RTE_PROC_SECONDARY);
    return (get_port_queues("modules.packetio.dpdk.secondary.rx-port-queues"));
}

std::map<uint16_t, std::vector<uint16_t>> tx_port_queues()
{
    assert(rte_eal_process_type() == RTE_PROC_SECONDARY);
    return (get_port_queues("modules.packetio.dpdk.secondary.tx-port-queues"));
}

static std::optional<model::core_mask> get_core_mask(std::string_view opt_name)
{
    auto mask = config::file::op_config_get_param<OP_OPTION_TYPE_HEX>(opt_name);

    if (mask) { return (model::core_mask{*mask}); }

    return (std::nullopt);
}

std::optional<model::core_mask> misc_core_mask()
{
    return (get_core_mask("modules.packetio.dpdk.misc-worker-mask"));
}

std::optional<model::core_mask> rx_core_mask()
{
    return (get_core_mask("modules.packetio.dpdk.rx-worker-mask"));
}

std::optional<model::core_mask> tx_core_mask()
{
    return (get_core_mask("modules.packetio.dpdk.tx-worker-mask"));
}

bool rx_interrupts()
{
    auto result =
        openperf::config::file::op_config_get_param<OP_OPTION_TYPE_NONE>(
            "modules.packetio.dpdk.no-rx-interrupts");
    /* XXX: A negative times a negative equals a positive. Say it! */
    return (!result.value_or(false));
}

} /* namespace openperf::packetio::dpdk::config */
