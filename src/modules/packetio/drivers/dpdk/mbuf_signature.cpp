#include <stdexcept>
#include <string>

#include "core/op_log.h"
#include "dpdk_proc_shim/api.h"
#include "packetio/drivers/dpdk/dpdk.h"
#include "packetio/drivers/dpdk/mbuf_signature.hpp"

namespace openperf::packetio::dpdk {

size_t mbuf_signature_offset = 0;
uint64_t mbuf_signature_flag = 0;

static constexpr auto mbuf_dynfield_signature =
    rte_mbuf_dynfield{.name = "packetio_dynfield_signature",
                      .size = sizeof(mbuf_signature),
                      .align = __alignof(uint64_t),
                      .flags = 0};

static constexpr auto mbuf_dynflag_signature =
    rte_mbuf_dynflag{.name = "packetio_dynflag_signature", .flags = 0};

void mbuf_signature_init()
{
    auto offset = dps_mbuf_dynfield_register(&mbuf_dynfield_signature);
    if (offset < 0) {
        throw std::runtime_error(
            "Could not register dynamic field for signature: "
            + std::string(rte_strerror(rte_errno)));
    }

    mbuf_signature_offset = offset;

    /* Register the signature flag for any available bit */
    auto bitnum = dps_mbuf_dynflag_register(&mbuf_dynflag_signature);
    if (bitnum < 0) {
        throw std::runtime_error(
            "Could not register dynamic bit number for signature: "
            + std::string(rte_strerror(rte_errno)));
    }

    mbuf_signature_flag = (1ULL << bitnum);

    OP_LOG(OP_LOG_DEBUG,
           "Dynamic signature field registered: offset = %d, bitflag = %d\n",
           offset,
           bitnum);
}

} // namespace openperf::packetio::dpdk
