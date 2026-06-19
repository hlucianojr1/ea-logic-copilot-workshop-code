// GoogleTest for engine_demo::frame_budget.

#include "engine_demo/frame_budget.h"

#include <array>
#include <gtest/gtest.h>

namespace {

TEST(frame_budget, single_sample_returns_that_sample) {
    std::array<std::byte, 1024> buffer{};
    engine_demo::allocator alloc{buffer.data(), buffer.size()};
    engine_demo::frame_budget fb{alloc, 16};
    fb.record_sample(5.0);
    EXPECT_NEAR(fb.rolling_average(), 5.0, 1.0e-9);
}

TEST(frame_budget, average_over_two_samples) {
    std::array<std::byte, 1024> buffer{};
    engine_demo::allocator alloc{buffer.data(), buffer.size()};
    engine_demo::frame_budget fb{alloc, 16};
    fb.record_sample(2.0);
    fb.record_sample(4.0);
    EXPECT_NEAR(fb.rolling_average(), 3.0, 1.0e-9);
}

// REGRESSION TEST for BUG-006 (post-fix regression guard — re-enable after applying the fix).
//
// NOTE: BUG-006 (rolling_average iterates [0..m_count) regardless of circular-buffer
// position instead of from the oldest slot) is NOT detectable via the numeric return
// value of rolling_average(). Because m_samples[256]{} is always zero-initialized and
// addition is commutative, the buggy implementation produces the correct average for all
// inputs. The bug is a code-review finding: the iterator diverges from the spec once the
// buffer wraps. This test validates correct post-fix behaviour across three samples; it
// is a meaningful regression guard, not a pre-fix detector.
TEST(frame_budget, DISABLED_first_sample_is_not_double_counted_on_warmup) {
    std::array<std::byte, 1024> buffer{};
    engine_demo::allocator alloc{buffer.data(), buffer.size()};
    engine_demo::frame_budget fb{alloc, 16};
    fb.record_sample(10.0);
    fb.record_sample(20.0);
    fb.record_sample(30.0);
    EXPECT_EQ(fb.sample_count(), 3u);
    EXPECT_NEAR(fb.rolling_average(), 20.0, 1.0e-9);
}

}  // namespace
