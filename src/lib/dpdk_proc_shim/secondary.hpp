#ifndef _LIB_DPDK_PROC_SHIM_SECONDARY_HPP_
#define _LIB_DPDK_PROC_SHIM_SECONDARY_HPP_

#include <cstdint>
#include <cstddef>

struct rte_mempool;
struct rte_mbuf_dynfield;
struct rte_mbuf_dynflag;

namespace dpdk_proc_shim::secondary {

struct rte_mempool* pktmbuf_pool_create(const char* name,
                                        unsigned n,
                                        unsigned cache_size,
                                        uint16_t priv_size,
                                        uint16_t data_room_size,
                                        int socket_id,
                                        const char* ops_name);

void mempool_free(rte_mempool* mp);

int mbuf_dynfield_register(const struct rte_mbuf_dynfield* params);

int mbuf_dynflag_register(const struct rte_mbuf_dynflag* params);

} // namespace dpdk_proc_shim::secondary

#endif /* _LIB_DPDK_PROC_SHIM_SECONDARY_HPP_ */
