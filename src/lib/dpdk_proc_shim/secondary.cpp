#include <cassert>
#include <cstring>

#include "rte_eal.h"
#include "rte_errno.h"
#include "rte_mbuf_dyn_wrapper.h"
#include "rte_mbuf_pool_ops.h"
#include "rte_mempool.h"

#include "messages.hpp"
#include "secondary.hpp"

namespace dpdk_proc_shim::secondary {

static const struct timespec timeout = {5, 0};

struct rte_mempool* pktmbuf_pool_create(const char* name,
                                        unsigned n,
                                        unsigned cache_size,
                                        uint16_t priv_size,
                                        uint16_t data_room_size,
                                        int socket_id,
                                        const char* ops_name)
{
    assert(rte_eal_process_type() == RTE_PROC_SECONDARY);

    auto request = rte_mp_msg{};
    std::strncpy(
        request.name, messages::pktmbuf_pool_create_key, sizeof(request.name));
    request.len_param = sizeof(messages::pktmbuf_pool_create_request);
    auto* args =
        reinterpret_cast<messages::pktmbuf_pool_create_request*>(request.param);
    *args = {.n = n,
             .cache_size = cache_size,
             .priv_size = priv_size,
             .data_room_size = data_room_size,
             .socket_id = socket_id};
    std::strncpy(args->name, name, RTE_MEMZONE_NAMESIZE);
    std::strncpy(args->ops_name,
                 ops_name ? ops_name : rte_mbuf_best_mempool_ops(),
                 RTE_MEMPOOL_OPS_NAMESIZE);

    struct rte_mp_reply reply;

    if (auto error =
            rte_mp_request_sync(&request, &reply, &timeout) || !reply.msgs) {
        return (nullptr);
    }

    auto r = *(reinterpret_cast<messages::pktmbuf_pool_create_reply*>(
        reply.msgs->param));
    free(reply.msgs);

    if (r.error) {
        rte_errno = r.error;
        return (nullptr);
    }

    return (r.mpool);
}

void mempool_free(struct rte_mempool* mp)
{
    assert(rte_eal_process_type() == RTE_PROC_SECONDARY);

    auto request = rte_mp_msg{};
    std::strncpy(
        request.name, messages::mempool_free_key, sizeof(request.name));
    request.len_param = sizeof(mp);
    auto* args =
        reinterpret_cast<messages::mempool_free_request*>(request.param);
    args->mpool = mp;

    rte_mp_sendmsg(&request);
}

int mbuf_dynfield_register(const struct rte_mbuf_dynfield* params)
{
    assert(rte_eal_process_type() == RTE_PROC_SECONDARY);

    auto request = rte_mp_msg{};
    std::strncpy(request.name,
                 messages::mbuf_dynfield_register_key,
                 sizeof(request.name));
    request.len_param = sizeof(*params);
    memcpy(request.param, params, sizeof(*params));

    struct rte_mp_reply reply;

    if (auto error =
            rte_mp_request_sync(&request, &reply, &timeout) || !reply.msgs) {
        return (-1);
    }

    auto r = *(reinterpret_cast<messages::mbuf_dynfield_register_reply*>(
        reply.msgs->param));
    free(reply.msgs);

    return (r.value);
}

int mbuf_dynflag_register(const struct rte_mbuf_dynflag* params)
{
    assert(rte_eal_process_type() == RTE_PROC_SECONDARY);

    auto request = rte_mp_msg{};
    std::strncpy(request.name,
                 messages::mbuf_dynflag_register_key,
                 sizeof(request.name));
    request.len_param = sizeof(*params);
    memcpy(request.param, params, sizeof(*params));

    struct rte_mp_reply reply;

    if (auto error =
            rte_mp_request_sync(&request, &reply, &timeout) || !reply.msgs) {
        return (-1);
    }

    auto r = *(reinterpret_cast<messages::mbuf_dynflag_register_reply*>(
        reply.msgs->param));
    free(reply.msgs);

    return (r.value);
}

extern "C" {

int dps_secondary_init() { return (0); }

int dps_secondary_fini() { return (0); }
}

} // namespace dpdk_proc_shim::secondary
