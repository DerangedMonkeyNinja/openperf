#include <cmath>
#include <cstdio>

#include "timesync/error_tracker.hpp"

namespace openperf::timesync {

static inline float to_float(std::chrono::nanoseconds x)
{
    return (
        std::chrono::duration_cast<std::chrono::duration<float>>(x).count());
}

void update(error_tracker& tracker, std::chrono::nanoseconds error)
{
    if (error < tracker.min) { tracker.min = error; }
    if (error > tracker.max) { tracker.max = error; }
    tracker.total += error;
    tracker.count++;

    if (tracker.min != tracker.max) {
        const auto c = static_cast<float>(tracker.count);
        auto tmp = (c * error) - tracker.total;
        auto num = tmp * tmp.count();
        auto den = (c * (c - 1));
        tracker.m2 += num / den;
    }

    // tracker.digest.insert(error.count());
}

void dump(const error_tracker& tracker)
{
    fprintf(stderr, "=== tracker ===\n");
    fprintf(stderr, "min = %0.09f\n", to_float(tracker.min));
    fprintf(stderr, "max = %0.09f\n", to_float(tracker.max));
    fprintf(stderr, "avg = %0.09f\n", to_float(tracker.total / tracker.count));
    // fprintf(stderr,
    //        "std. dev. = %0.09f\n",
    //        std::sqrt(tracker.m2.count() / (tracker.count - 1)));
}

} // namespace openperf::timesync
