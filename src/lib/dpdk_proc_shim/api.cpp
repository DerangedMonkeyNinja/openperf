#include "rte_eal.h"
#include "rte_errno.h"

#include "primary.hpp"
#include "secondary.hpp"

extern "C" {

struct rte_mempool* dps_pktmbuf_pool_create_by_ops(const char* name,
                                                   unsigned n,
                                                   unsigned cache_size,
                                                   uint16_t priv_size,
                                                   uint16_t data_room_size,
                                                   int socket_id,
                                                   const char* ops_name)
{
    switch (rte_eal_process_type()) {
    case RTE_PROC_PRIMARY:
        return (dpdk_proc_shim::primary::pktmbuf_pool_create(name,
                                                             n,
                                                             cache_size,
                                                             priv_size,
                                                             data_room_size,
                                                             socket_id,
                                                             ops_name));
    case RTE_PROC_SECONDARY:
        return (dpdk_proc_shim::secondary::pktmbuf_pool_create(name,
                                                               n,
                                                               cache_size,
                                                               priv_size,
                                                               data_room_size,
                                                               socket_id,
                                                               ops_name));
    default:
        rte_errno = ESRCH;
        return (nullptr);
    }
}

struct rte_mempool* dps_pktmbuf_pool_create(const char* name,
                                            unsigned n,
                                            unsigned cache_size,
                                            uint16_t priv_size,
                                            uint16_t data_room_size,
                                            int socket_id)
{
    return (dps_pktmbuf_pool_create_by_ops(
        name, n, cache_size, priv_size, data_room_size, socket_id, nullptr));
}

void dps_mempool_free(struct rte_mempool* mp)
{
    switch (rte_eal_process_type()) {
    case RTE_PROC_PRIMARY:
        dpdk_proc_shim::primary::mempool_free(mp);
        break;
    case RTE_PROC_SECONDARY:
        dpdk_proc_shim::secondary::mempool_free(mp);
        break;
    default:
        break;
    }
}

int dps_mbuf_dynfield_register(const struct rte_mbuf_dynfield* params)
{
    switch (rte_eal_process_type()) {
    case RTE_PROC_PRIMARY:
        return (dpdk_proc_shim::primary::mbuf_dynfield_register(params));
    case RTE_PROC_SECONDARY:
        return (dpdk_proc_shim::secondary::mbuf_dynfield_register(params));
    default:
        rte_errno = ESRCH;
        return (-1);
    }
}

int dps_mbuf_dynflag_register(const struct rte_mbuf_dynflag* params)
{
    switch (rte_eal_process_type()) {
    case RTE_PROC_PRIMARY:
        return (dpdk_proc_shim::primary::mbuf_dynflag_register(params));
    case RTE_PROC_SECONDARY:
        return (dpdk_proc_shim::secondary::mbuf_dynflag_register(params));
    default:
        rte_errno = ESRCH;
        return (-1);
    }
}
}
