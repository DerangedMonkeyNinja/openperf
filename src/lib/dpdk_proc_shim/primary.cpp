#include <cassert>
#include <cstring>
#include <map>
#include <variant>

#include "rte_eal.h"
#include "rte_errno.h"
#include "rte_ethdev.h"
#include "rte_mbuf.h"
#include "rte_mbuf_dyn_wrapper.h"
#include "rte_mempool.h"

#include "api.h"
#include "messages.hpp"
#include "singleton.hpp"

namespace dpdk_proc_shim::primary {

using dpdk_callback = std::variant<on_pktmbuf_pool_create_by_ops,
                                   on_mempool_free,
                                   on_mbuf_dynfield_register,
                                   on_mbuf_dynflag_register>;

struct primary_config : dpdk_proc_shim::utils::singleton<primary_config>
{
    std::map<std::string, dpdk_callback> callbacks;
};

static int handle_pktmbuf_pool_create(const struct rte_mp_msg* msg,
                                      const void* peer)
{
    assert(rte_eal_process_type() == RTE_PROC_PRIMARY);

    auto reply_msg = rte_mp_msg{};
    std::strcpy(reply_msg.name, messages::pktmbuf_pool_create_key);
    reply_msg.len_param = sizeof(messages::pktmbuf_pool_create_reply);

    auto* reply =
        reinterpret_cast<messages::pktmbuf_pool_create_reply*>(reply_msg.param);

    auto& config = primary_config::instance();
    auto it = config.callbacks.find(messages::pktmbuf_pool_create_key);
    if (it == config.callbacks.end()) {
        reply->error = ENOSYS;
        return (rte_mp_reply(&reply_msg, reinterpret_cast<const char*>(peer)));
    }

    auto create = std::get<on_pktmbuf_pool_create_by_ops>(it->second);
    const auto* args =
        reinterpret_cast<const messages::pktmbuf_pool_create_request*>(
            msg->param);

    reply->mpool = create(args->name,
                          args->n,
                          args->cache_size,
                          args->priv_size,
                          args->data_room_size,
                          args->socket_id,
                          args->ops_name);
    reply->error = reply->mpool ? 0 : rte_errno;

    return (rte_mp_reply(&reply_msg, reinterpret_cast<const char*>(peer)));
}

static int handle_mempool_free(const struct rte_mp_msg* msg, const void*)
{
    assert(rte_eal_process_type() == RTE_PROC_PRIMARY);

    auto& config = primary_config::instance();
    auto it = config.callbacks.find(messages::mempool_free_key);
    if (it == config.callbacks.end()) { return (0); }

    auto free = std::get<on_mempool_free>(it->second);
    auto* args =
        reinterpret_cast<const messages::mempool_free_request*>(msg->param);

    free(args->mpool);

    return (0);
}

static int handle_mbuf_dynfield_register(const struct rte_mp_msg* msg,
                                         const void* peer)
{
    assert(rte_eal_process_type() == RTE_PROC_PRIMARY);

    auto reply_msg = rte_mp_msg{};
    std::strcpy(reply_msg.name, messages::mbuf_dynfield_register_key);
    reply_msg.len_param = sizeof(rte_mbuf_dynfield);

    auto* reply = reinterpret_cast<messages::mbuf_dynfield_register_reply*>(
        reply_msg.param);

    auto& config = primary_config::instance();
    auto it = config.callbacks.find(messages::mbuf_dynfield_register_key);
    if (it == config.callbacks.end()) {
        reply->value = ENOSYS;
        return (rte_mp_reply(&reply_msg, reinterpret_cast<const char*>(peer)));
    }

    auto reg = std::get<on_mbuf_dynfield_register>(it->second);
    const auto* args = reinterpret_cast<const rte_mbuf_dynfield*>(msg->param);

    reply->value = reg(args);

    return (rte_mp_reply(&reply_msg, reinterpret_cast<const char*>(peer)));
}

static int handle_mbuf_dynflag_register(const struct rte_mp_msg* msg,
                                        const void* peer)
{
    assert(rte_eal_process_type() == RTE_PROC_PRIMARY);

    auto reply_msg = rte_mp_msg{};
    std::strcpy(reply_msg.name, messages::mbuf_dynflag_register_key);
    reply_msg.len_param = sizeof(rte_mbuf_dynflag);

    auto* reply = reinterpret_cast<messages::mbuf_dynflag_register_reply*>(
        reply_msg.param);

    auto& config = primary_config::instance();
    auto it = config.callbacks.find(messages::mbuf_dynflag_register_key);
    if (it == config.callbacks.end()) {
        reply->value = ENOSYS;
        return (rte_mp_reply(&reply_msg, reinterpret_cast<const char*>(peer)));
    }

    auto reg = std::get<on_mbuf_dynflag_register>(it->second);
    const auto* args = reinterpret_cast<const rte_mbuf_dynflag*>(msg->param);

    reply->value = reg(args);

    return (rte_mp_reply(&reply_msg, reinterpret_cast<const char*>(peer)));
}

static int handle_ethdev_event(uint16_t port_id,
                               enum rte_eth_event_type event,
                               void*,
                               void*)
{
    auto request = rte_mp_msg{};
    std::strncpy(
        request.name, messages::ethdev_event_key, sizeof(request.name));
    request.len_param = sizeof(messages::ethdev_event);
    auto* args = reinterpret_cast<messages::ethdev_event*>(request.param);
    args->port_id = port_id;
    args->event_type = event;

    return (rte_mp_sendmsg(&request));
}

struct rte_mempool* pktmbuf_pool_create(const char* name,
                                        unsigned n,
                                        unsigned cache_size,
                                        uint16_t priv_size,
                                        uint16_t data_room_size,
                                        int socket_id,
                                        const char* ops_name)
{
    assert(rte_eal_process_type() == RTE_PROC_PRIMARY);

    auto& config = primary_config::instance();

    auto it = config.callbacks.find(messages::pktmbuf_pool_create_key);
    if (it == config.callbacks.end()) {
        rte_errno = ENOSYS;
        return (nullptr);
    }

    auto create = std::get<on_pktmbuf_pool_create_by_ops>(it->second);

    return (create(
        name, n, cache_size, priv_size, data_room_size, socket_id, ops_name));
}

void mempool_free(struct rte_mempool* mp)
{
    assert(rte_eal_process_type() == RTE_PROC_PRIMARY);

    auto& config = primary_config::instance();

    auto it = config.callbacks.find(messages::mempool_free_key);
    if (it == config.callbacks.end()) { return; }

    auto free = std::get<on_mempool_free>(it->second);

    free(mp);
}

int mbuf_dynfield_register(const struct rte_mbuf_dynfield* params)
{
    assert(rte_eal_process_type() == RTE_PROC_PRIMARY);

    auto& config = primary_config::instance();

    auto it = config.callbacks.find(messages::mbuf_dynfield_register_key);
    if (it == config.callbacks.end()) {
        rte_errno = ENOSYS;
        return (-1);
    }

    auto reg = std::get<on_mbuf_dynfield_register>(it->second);

    return (reg(params));
}

int mbuf_dynflag_register(const struct rte_mbuf_dynflag* params)
{
    assert(rte_eal_process_type() == RTE_PROC_PRIMARY);

    auto& config = primary_config::instance();

    auto it = config.callbacks.find(messages::mbuf_dynflag_register_key);
    if (it == config.callbacks.end()) {
        rte_errno = ENOSYS;
        return (-1);
    }

    auto reg = std::get<on_mbuf_dynflag_register>(it->second);

    return (reg(params));
}

template <typename Function, typename Callback>
int register_function(const std::string& key, Function f, Callback cb)
{
    assert(rte_eal_process_type() == RTE_PROC_PRIMARY);

    auto& config = primary_config::instance();

    if (config.callbacks.count(key)) {
        rte_errno = EEXIST;
        return (-1);
    }

    auto [it, success] = config.callbacks.emplace(key, f);
    if (!success) {
        rte_errno = ENOMEM;
        return (-1);
    }

    if (auto error = rte_mp_action_register(key.c_str(), cb)) {
        config.callbacks.erase(it);
        return (error);
    }

    return (0);
}

void init_common() {}

} // namespace dpdk_proc_shim::primary

extern "C" {

using namespace dpdk_proc_shim::primary;

int dps_primary_init()
{
    auto error = (dps_primary_custom_init()
                  || dps_primary_register_on_pktmbuf_pool_create_by_ops(
                      rte_pktmbuf_pool_create_by_ops)
                  || dps_primary_register_on_mempool_free(rte_mempool_free)
                  || dps_primary_register_on_mbuf_dynfield_register(
                      rte_mbuf_dynfield_register)
                  || dps_primary_register_on_mbuf_dynflag_register(
                      rte_mbuf_dynflag_register));

    return (error);
}

int dps_primary_custom_init()
{
    assert(rte_eal_process_type() == RTE_PROC_PRIMARY);

    for (auto event = static_cast<int>(RTE_ETH_EVENT_INTR_LSC);
         event < static_cast<int>(RTE_ETH_EVENT_MAX);
         event++) {
        if (auto error =
                rte_eth_dev_callback_register(RTE_ETH_ALL,
                                              rte_eth_event_type(event),
                                              handle_ethdev_event,
                                              nullptr)) {
            throw std::runtime_error(
                "Could not register callback for ethdev event "
                + std::to_string(event) + ": "
                + std::string(rte_strerror(rte_errno)));
        }
    }

    return (0);
}

void dps_primary_fini()
{
    assert(rte_eal_process_type() == RTE_PROC_PRIMARY);

    for (auto event = static_cast<int>(RTE_ETH_EVENT_INTR_LSC);
         event < static_cast<int>(RTE_ETH_EVENT_MAX);
         event++) {
        rte_eth_dev_callback_unregister(RTE_ETH_ALL,
                                        rte_eth_event_type(event),
                                        handle_ethdev_event,
                                        nullptr);
    }

    auto& config = primary_config::instance();

    for (auto& pair : config.callbacks) {
        rte_mp_action_unregister(pair.first.c_str());
    }

    config.callbacks.clear();
}

int dps_primary_register_on_pktmbuf_pool_create_by_ops(
    on_pktmbuf_pool_create_by_ops f)
{
    return (register_function(dpdk_proc_shim::messages::pktmbuf_pool_create_key,
                              f,
                              handle_pktmbuf_pool_create));
}

int dps_primary_register_on_mempool_free(on_mempool_free f)
{
    return (register_function(
        dpdk_proc_shim::messages::mempool_free_key, f, handle_mempool_free));
}

int dps_primary_register_on_mbuf_dynfield_register(on_mbuf_dynfield_register f)
{
    return (
        register_function(dpdk_proc_shim::messages::mbuf_dynfield_register_key,
                          f,
                          handle_mbuf_dynfield_register));
}

int dps_primary_register_on_mbuf_dynflag_register(on_mbuf_dynflag_register f)
{
    return (
        register_function(dpdk_proc_shim::messages::mbuf_dynflag_register_key,
                          f,
                          handle_mbuf_dynflag_register));
}
}
