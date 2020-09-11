#ifndef _LIB_DPDK_PROC_SHIM_API_H_
#define _LIB_DPDK_PROC_SHIM_API_H_

#include <stdint.h>
#include <stdio.h>

/**
 * @file
 *
 * This file contains the API for a DPDK process shim library to allow
 * DPDK applications to transparently operate as either a primary or
 * seconary process.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Forward declarations
 */

struct rte_mempool;
struct rte_mbuf_dynfield;
struct rte_mbuf_dynflag;

/**
 * Typedefs and structures
 */

typedef struct rte_mempool* (*on_pktmbuf_pool_create_by_ops)(
    const char* name,
    unsigned n,
    unsigned cache_size,
    uint16_t priv_size,
    uint16_t data_room_size,
    int socket_id,
    const char* ops_name);

typedef void (*on_mempool_free)(struct rte_mempool*);

typedef int (*on_mbuf_dynfield_register)(const struct rte_mbuf_dynfield*);

typedef int (*on_mbuf_dynflag_register)(const struct rte_mbuf_dynflag*);

/**
 * Primary process hooks
 */

int dps_primary_init();

int dps_primary_custom_init();

void dps_primary_fini();

int dps_primary_register_on_pktmbuf_pool_create_by_ops(
    on_pktmbuf_pool_create_by_ops f);

int dps_primary_register_on_mempool_free(on_mempool_free f);

int dps_primary_register_on_mbuf_dynfield_register(on_mbuf_dynfield_register f);

int dps_primary_register_on_mbuf_dynflag_register(on_mbuf_dynflag_register f);

/**
 * Secondary process hooks
 */

int dps_secondary_init();
int dps_secondary_fini();

/**
 * Functions that may be called from either primary or secondary
 * process
 */

struct rte_mempool* dps_pktmbuf_pool_create(const char* name,
                                            unsigned n,
                                            unsigned cache_size,
                                            uint16_t priv_size,
                                            uint16_t data_room_size,
                                            int socket_id);

struct rte_mempool* dps_pktmbuf_pool_create_by_ops(const char* name,
                                                   unsigned n,
                                                   unsigned cache_size,
                                                   uint16_t priv_size,
                                                   uint16_t data_room_size,
                                                   int socket_id,
                                                   const char* ops_name);

void dps_mempool_free(struct rte_mempool* mp);

int dps_mbuf_dynfield_register(const struct rte_mbuf_dynfield* params);

int dps_mbuf_dynflag_register(const struct rte_mbuf_dynflag* params);

#ifdef __cplusplus
}
#endif

#endif /* _LIB_DPDK_PROC_SHIM_API_H_ */
