#include "engine_demo/sim/timer.h"

#include <climits>

#include "gtest/gtest.h"

namespace {

using engine_demo::sim::elapsed_timer;

TEST(ElapsedTimer, TickAccumulatesTime) {
    elapsed_timer timer;
    EXPECT_EQ(timer.elapsed_ms(), 0);
    (void)timer.tick(16);
    EXPECT_EQ(timer.elapsed_ms(), 16);
    (void)timer.tick(16);
    EXPECT_EQ(timer.elapsed_ms(), 32);
}

TEST(ElapsedTimer, ResetClearsAccumulator) {
    elapsed_timer timer;
    (void)timer.tick(100);
    EXPECT_EQ(timer.elapsed_ms(), 100);
    timer.reset();
    EXPECT_EQ(timer.elapsed_ms(), 0);
}

TEST(ElapsedTimer, MultipleLargeTicks) {
    elapsed_timer timer;
    (void)timer.tick(1'000'000);
    (void)timer.tick(1'000'000);
    (void)timer.tick(1'000'000);
    EXPECT_EQ(timer.elapsed_ms(), 3'000'000);
}

// REGRESSION TEST for BUG-007:
// When compiled at -O2, the overflow guard `if (x + delta > x)` is elided by the
// compiler because signed overflow is UB. The counter wraps to negative values
// instead of saturating.
//
// To reproduce: accumulate past INT32_MAX (2,147,483,647 ms ≈ 24.8 days, or ~35 min
// at 1000× speed). At -O2 the guard is deleted and the timer wraps negative.
//
// Expected (correct): timer saturates at or near INT32_MAX.
// Actual (buggy at -O2): timer wraps to a large negative value.
TEST(ElapsedTimer, overflow_guard_not_elided) {
    elapsed_timer timer;

    // Accumulate to near INT32_MAX.
    constexpr std::int32_t big_step = 1'000'000'000;  // 1 billion ms
    (void)timer.tick(big_step);
    (void)timer.tick(big_step);
    // Now at 2,000,000,000 — below INT32_MAX (2,147,483,647).
    EXPECT_GT(timer.elapsed_ms(), 0);

    // This tick SHOULD overflow: 2,000,000,000 + 1,000,000,000 = 3 billion > INT32_MAX.
    // Correct behavior: saturate or reject the tick.
    // Buggy behavior: wraps to -1,294,967,296 (at -O2, guard elided).
    (void)timer.tick(big_step);

    // The timer should never go negative if the guard works.
    EXPECT_GT(timer.elapsed_ms(), 0)
        << "Timer wrapped negative — overflow guard was elided by the compiler "
           "(BUG-007: signed overflow UB enables dead-code elimination at -O2)";
}

}  // namespace
