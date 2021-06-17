#ifndef _OP_TIMESYNC_ERROR_TRACKER_HPP_
#define _OP_TIMESYNC_ERROR_TRACKER_HPP_

#include <chrono>

//#include "regurgitate/regurgitate.hpp"

namespace openperf::timesync {

using namespace std::chrono_literals;

struct error_tracker
{
    using pop_t = std::chrono::duration<int32_t, std::nano>;
    using sum_t = std::chrono::nanoseconds;
    using var_t = std::chrono::duration<float, std::nano>;

    // using error_digest = regurgitate::digest<float, float, 32>;

    pop_t min = pop_t::max();
    pop_t max = pop_t::min();
    sum_t total = sum_t::zero();
    var_t m2 = var_t::zero();
    uint64_t count = 0;
    // error_digest digest;
};

void update(error_tracker& tracker, std::chrono::nanoseconds error);

void dump(const error_tracker& tracker);

} // namespace openperf::timesync

#endif /* _OP_TIMESYNC_ERROR_TRACKER_HPP_ */
