#include "engine_demo/sim/interpolator.h"

#include "gtest/gtest.h"

namespace {

using engine_demo::sim::keyframe;
using engine_demo::sim::keyframe_interpolator;

TEST(KeyframeInterpolator, AddAndStartPlayback) {
    keyframe_interpolator interp;
    EXPECT_TRUE(interp.add_keyframe({0.0, 10.0}));
    EXPECT_TRUE(interp.add_keyframe({1.0, 20.0}));
    EXPECT_TRUE(interp.add_keyframe({2.0, 30.0}));
    EXPECT_EQ(interp.keyframe_count(), 3u);

    interp.start();
    EXPECT_DOUBLE_EQ(interp.current_value(), 10.0);
}

TEST(KeyframeInterpolator, AdvanceThroughKeyframes) {
    keyframe_interpolator interp;
    (void)interp.add_keyframe({0.0, 100.0});
    (void)interp.add_keyframe({1.0, 200.0});
    (void)interp.add_keyframe({2.0, 300.0});
    interp.start();

    EXPECT_DOUBLE_EQ(interp.current_value(), 100.0);
    EXPECT_TRUE(interp.advance());
    EXPECT_DOUBLE_EQ(interp.current_value(), 200.0);
    EXPECT_TRUE(interp.advance());
    EXPECT_DOUBLE_EQ(interp.current_value(), 300.0);
    EXPECT_FALSE(interp.advance());  // Already at last keyframe.
}

TEST(KeyframeInterpolator, CapacityLimit) {
    keyframe_interpolator interp;
    for (std::size_t i = 0; i < keyframe_interpolator::kMaxKeyframes; ++i) {
        EXPECT_TRUE(interp.add_keyframe({static_cast<double>(i), static_cast<double>(i * 10)}));
    }
    // Capacity exhausted.
    EXPECT_FALSE(interp.add_keyframe({999.0, 999.0}));
    EXPECT_EQ(interp.keyframe_count(), keyframe_interpolator::kMaxKeyframes);
}

// REGRESSION TEST for BUG-010:
// m_current_index is int32_t, initialized to -1. current_value() casts it to size_t
// for array indexing: static_cast<size_t>(-1) == SIZE_MAX.
//
// Then it does `m_keyframes[SIZE_MAX % kMaxKeyframes].value` which reads an
// arbitrary slot in the fixed-size array (technically within bounds due to modulo,
// but semantically wrong — reading uninitialized/stale keyframe data).
//
// Expected: calling current_value() before start() should return a sentinel (0.0)
//           or otherwise indicate "not started" safely.
// Actual (buggy): reads m_keyframes[SIZE_MAX % 64] — an arbitrary garbage slot.
TEST(KeyframeInterpolator, DISABLED_unstarted_does_not_read_oob) {
    keyframe_interpolator interp;

    // Add some keyframes with distinctive values.
    (void)interp.add_keyframe({0.0, 42.0});
    (void)interp.add_keyframe({1.0, 84.0});
    (void)interp.add_keyframe({2.0, 126.0});

    // Do NOT call start() — m_current_index remains -1.
    // current_value() should return a safe sentinel (0.0), NOT read from a garbage index.
    const double val = interp.current_value();

    // If the implementation is correct, the value should be the sentinel 0.0.
    // If BUG-010 is present, val is m_keyframes[SIZE_MAX % 64].value — which is
    // the default-initialized 0.0 for the slot at that modular index. This LOOKS
    // like it passes, but the bug is still there: it's reading an UNINTENDED slot.
    //
    // The real test is: if we fill ALL 64 slots with non-zero values, the "unstarted"
    // read will return one of them instead of the expected 0.0 sentinel.
    (void)val;

    // Better test: fill all slots and verify unstarted returns 0.0.
    keyframe_interpolator interp2;
    for (std::size_t i = 0; i < keyframe_interpolator::kMaxKeyframes; ++i) {
        (void)interp2.add_keyframe({static_cast<double>(i), 999.0});  // All values are 999.0
    }
    // Do NOT call start().
    const double val2 = interp2.current_value();

    // Expected: 0.0 (sentinel for "not started").
    // Actual with BUG-010: 999.0 (reads slot [SIZE_MAX % 64] which is filled with 999.0).
    EXPECT_DOUBLE_EQ(val2, 0.0)
        << "current_value() returned a keyframe value before start() was called — "
           "signed-to-unsigned promotion of -1 defeated the bounds check (BUG-010)";
}

}  // namespace
