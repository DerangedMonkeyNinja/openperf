#ifndef _OP_PACKETIO_DPDK_RXTX_QUEUE_CONTAINER_HPP_
#define _OP_PACKETIO_DPDK_RXTX_QUEUE_CONTAINER_HPP_

#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

namespace openperf::packetio::dpdk {

template <typename RxQueue, typename TxQueue> class rxtx_queue_container
{
    std::vector<std::unique_ptr<RxQueue>> m_rxqs;
    std::vector<std::unique_ptr<TxQueue>> m_txqs;

public:
    rxtx_queue_container(uint16_t port_id,
                         const std::vector<uint16_t>& rxq_ids,
                         const std::vector<uint16_t>& txq_ids)
    {
        if (rxq_ids.size()) {
            m_rxqs.resize(
                *std::max_element(std::begin(rxq_ids), std::end(rxq_ids)) + 1);
            std::for_each(
                std::begin(rxq_ids), std::end(rxq_ids), [&](uint16_t q) {
                    m_rxqs[q] = std::make_unique<RxQueue>(port_id, q);
                });
        }

        if (txq_ids.size()) {
            m_txqs.resize(
                *std::max_element(std::begin(txq_ids), std::end(txq_ids)) + 1);
            std::for_each(
                std::begin(txq_ids), std::end(txq_ids), [&](uint16_t q) {
                    m_txqs[q] = std::make_unique<TxQueue>(port_id, q);
                });
        }
    }

    std::vector<uint16_t> rx_queues() const
    {
        auto q_ids = std::vector<uint16_t>{};
        std::for_each(
            std::begin(m_rxqs), std::end(m_rxqs), [&](const auto& rxq) {
                if (rxq) { q_ids.emplace_back(rxq->queue_id()); }
            });

        return (q_ids);
    }

    std::vector<uint16_t> tx_queues() const
    {
        auto q_ids = std::vector<uint16_t>{};
        std::for_each(
            std::begin(m_txqs), std::end(m_txqs), [&](const auto& txq) {
                if (txq) { q_ids.emplace_back(txq->queue_id()); }
            });

        return (q_ids);
    }

    uint16_t rx_queue_id(uint32_t hash) const { return (hash % m_rxqs.size()); }

    uint16_t tx_queue_id(uint32_t hash) const { return (hash % m_txqs.size()); }

    RxQueue* rx(uint16_t queue_id) const { return (m_rxqs.at(queue_id).get()); }

    RxQueue* rx(uint32_t hash) const
    {
        return (m_rxqs.at(hash % m_rxqs.size()).get());
    }

    TxQueue* tx(uint16_t queue_id) const { return (m_txqs.at(queue_id).get()); }

    TxQueue* tx(uint32_t hash) const
    {
        return (m_txqs.at(hash % m_txqs.size()).get());
    }
};

} // namespace openperf::packetio::dpdk

#endif /* _OP_PACKETIO_DPDK_RXTX_QUEUE_CONTAINER_HPP_ */
