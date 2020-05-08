#include "timesync/counter.hpp"

namespace openperf::timesync::counter {
std::atomic<timecounter*> timecounter_now = nullptr;
}
