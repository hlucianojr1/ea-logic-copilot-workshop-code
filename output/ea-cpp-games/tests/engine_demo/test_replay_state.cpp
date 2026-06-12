#include "engine_demo/sim/replay_state.h"

#include "gtest/gtest.h"

namespace {

using engine_demo::sim::make_snapshot;
using engine_demo::sim::replay_snapshot;
using engine_demo::sim::snapshot_equals;

TEST(ReplayState, IdenticalSnapshotsSameObject) {
    // Comparing a snapshot to itself should always be true (same memory → same padding).
    auto snap = make_snapshot(0x01, 1.0, 2.0, 42, 3.0, 4.0);
    EXPECT_TRUE(snapshot_equals(snap, snap));
}

TEST(ReplayState, CopiedSnapshotEquals) {
    // Copying via assignment copies ALL bytes (including padding), so memcmp works
    // in this narrow case. This test passes even with the bug.
    auto snap = make_snapshot(0x02, 10.0, 20.0, 100, 0.5, -0.5);
    replay_snapshot copy = snap;
    EXPECT_TRUE(snapshot_equals(snap, copy));
}

TEST(ReplayState, DifferentValuesNotEqual) {
    auto a = make_snapshot(0x01, 1.0, 2.0, 42, 3.0, 4.0);
    auto b = make_snapshot(0x01, 1.0, 2.0, 43, 3.0, 4.0);  // different frame_number
    EXPECT_FALSE(snapshot_equals(a, b));
}

// REGRESSION TEST for BUG-008:
// Two independently-constructed snapshots with identical member values should compare
// equal. But because snapshot_equals uses memcmp and the struct has padding bytes that
// are uninitialized, independently-constructed snapshots may have different padding
// contents → memcmp returns non-zero → "not equal" for logically-equal data.
//
// This test constructs two snapshots independently (not via copy) from a helper function
// that sets each member individually. The padding bytes are whatever the stack had before.
//
// Expected: snapshot_equals returns true (logically equal).
// Actual (buggy): sometimes returns false due to differing padding bytes.
TEST(ReplayState, DISABLED_padding_does_not_affect_comparison) {
    // We call make_snapshot twice from different call sites to maximize the chance
    // that their stack frames have different prior contents (different padding bytes).
    // To be extra sure, we use a volatile write to dirty the stack between calls.
    volatile char stack_disturber[64]{};
    for (auto& c : stack_disturber) c = static_cast<char>(0xCC);

    auto a = make_snapshot(0x01, 1.0, 2.0, 42, 3.0, 4.0);

    // Disturb the stack again.
    for (auto& c : stack_disturber) c = static_cast<char>(0xDD);

    auto b = make_snapshot(0x01, 1.0, 2.0, 42, 3.0, 4.0);

    // Logically identical: same flags, positions, frame, velocities.
    EXPECT_TRUE(snapshot_equals(a, b))
        << "snapshot_equals returned false for logically-equal snapshots — "
           "memcmp is comparing uninitialized padding bytes (BUG-008)";
}

}  // namespace
