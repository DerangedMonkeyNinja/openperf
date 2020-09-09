#include "packetio/generic_driver.hpp"
#include "packetio/drivers/dpdk/eal.hpp"

#include <memory>

namespace openperf::packetio::driver {

std::unique_ptr<generic_driver> make()
{
    return (std::make_unique<generic_driver>(openperf::packetio::dpdk::eal()));
}

} // namespace openperf::packetio::driver
