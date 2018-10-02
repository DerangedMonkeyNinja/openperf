#include <assert.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>

#include "lwip/memp.h"
#include "lwip/sys.h"
#include "lwip/stats.h"

#include "drivers/dpdk/dpdk.h"
#include "memory/dpdk/memp.h"

extern struct rte_mbuf * packetio_memp_pbuf_to_mbuf(const struct pbuf *pbuf);
extern struct pbuf * packetio_memp_mbuf_to_pbuf(const struct rte_mbuf *mbuf);

static struct rte_mempool* get_default_mempool()
{
    static atomic_flag have_mp = ATOMIC_FLAG_INIT;
    static struct rte_mempool* default_mp = NULL;
    if (!atomic_flag_test_and_set(&have_mp)) {
        default_mp = rte_mempool_lookup(memp_default_mempool);
    }
    assert(default_mp);
    return (default_mp);
}

static struct rte_mempool* get_ref_rom_mempool()
{
    static atomic_flag have_mp = ATOMIC_FLAG_INIT;
    static struct rte_mempool* ref_rom_mp = NULL;
    if (!atomic_flag_test_and_set(&have_mp)) {
        ref_rom_mp = rte_mempool_lookup(memp_ref_rom_mempool);
    }
    assert(ref_rom_mp);
    return (ref_rom_mp);
}

void memp_init()
{
    get_default_mempool();
    get_ref_rom_mempool();
}

void * memp_malloc(memp_t type)
{
    void *to_return = NULL;
    struct rte_mbuf *mbuf = NULL;
    switch (type) {
    case MEMP_PBUF:
        mbuf = rte_pktmbuf_alloc(get_default_mempool());
        if (mbuf) {
            to_return = packetio_memp_mbuf_to_pbuf(mbuf);
        }
        break;
    case MEMP_PBUF_POOL:
        mbuf = rte_pktmbuf_alloc(get_ref_rom_mempool());
        if (mbuf) {
            to_return = packetio_memp_mbuf_to_pbuf(mbuf);
        }
        break;
    default:
        to_return = malloc(memp_pools[type]->size);
    }

#if MEMP_STATS
    struct memp_desc *desc = memp_pools[type];
    if (to_return) {
        desc->stats->max = icp_max(++desc->stats->used, desc->stats->max);
    } else {
        LWIP_DEBUGF(MEMP_DEBUG | LWIP_DBG_LEVEL_SERIOUS,
                    ("memp_malloc: out of memory in pool %s\n", desc->desc));
        desc->stats->err++;
    }
#endif

    return (to_return);
}

void memp_free(memp_t type, void *mem)
{
    switch (type) {
    case MEMP_PBUF:
    case MEMP_PBUF_POOL:
        rte_pktmbuf_free_seg(packetio_memp_pbuf_to_mbuf((struct pbuf *)mem));
        break;
    default:
        free(mem);
    }

#if MEMP_STATS
    struct memp_desc *desc = memp_pools[type];
    desc->stats->used--;
#endif
}
