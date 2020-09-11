#ifndef _LIB_DPDK_PROC_SHIM_MESSAGES_HPP_
#define _LIB_DPDK_PROC_SHIM_MESSAGES_HPP_

#include <cstdint>

struct rte_mempool;

namespace dpdk_proc_shim::messages {

inline constexpr auto pktmbuf_pool_create_key = "pktmbuf_pool_create";
inline constexpr auto mempool_free_key = "mempool_free";
inline constexpr auto mbuf_dynfield_register_key = "mbuf_dynfield_reserve";
inline constexpr auto mbuf_dynflag_register_key = "mbuf_dynflag_reserve";
inline constexpr auto ethdev_event_key = "ethdev_event";

constexpr auto dpdk_namesize = 32;

struct pktmbuf_pool_create_request
{
    char name[dpdk_namesize];
    unsigned n;
    unsigned cache_size;
    uint16_t priv_size;
    uint16_t data_room_size;
    int socket_id;
    char ops_name[dpdk_namesize];
};

struct pktmbuf_pool_create_reply
{
    rte_mempool* mpool;
    int error;
};

struct mempool_free_request
{
    rte_mempool* mpool;
};

struct mbuf_dynfield_register_reply
{
    int value;
};

struct mbuf_dynflag_register_reply
{
    int value;
};

struct ethdev_event
{
    uint16_t port_id;
    int event_type; /* avoid dragging in dpdk header for the enum */
};

} // namespace dpdk_proc_shim::messages

#endif /* _LIB_DPDK_PROC_SHIM_MESSAGES_HPP_ */
