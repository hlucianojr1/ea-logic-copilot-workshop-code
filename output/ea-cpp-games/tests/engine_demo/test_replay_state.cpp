#include "engine_demo/sim/replay_state.h"

#include "gtest/gtest.h"

#include <cstring>

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

// REGRESSION TEST for BUG-008 (post-fix regression guard — re-enable after applying the fix).
//
// BUG-008: snapshot_equals uses memcmp which reads ALL bytes including uninitialised
// padding. Two independently-constructed snapshots with identical member values may
// have different padding bytes → memcmp falsely returns non-zero → "not equal".
//
// Reliability: the volatile-disturber approach does NOT work on Apple Silicon (AArch64).
// A 48-byte struct is returned via a hidden sret pointer into the caller's stack frame;
// writing to a nearby volatile local array touches a *different* stack slot and leaves
// the sret slot's prior contents intact. Both calls to make_snapshot() happen to use the
// same prior stack contents, so padding bytes are identical and the bug does not manifest.
//
// Fix: explicitly overwrite the padding bytes of each struct with a distinct known pattern
// after construction. This makes the failure deterministic on all platforms and compilers.
// Padding layout (see replay_state.h): 7 bytes at offset 1, 4 bytes at offset 28.
TEST(ReplayState, DISABLED_padding_does_not_affect_comparison) {
    static_assert(sizeof(replay_snapshot) == 48,
                  "Layout assumption changed — update padding offsets below.");

    auto a = make_snapshot(0x01, 1.0, 2.0, 42, 3.0, 4.0);
    auto b = make_snapshot(0x01, 1.0, 2.0, 42, 3.0, 4.0);

    // Poison the uninitialized padding bytes with distinct known patterns.
    // reinterpret_cast is required for byte-level access to struct internals.
    auto* a_bytes = reinterpret_cast<unsigned char*>(&a);  // NOLINT: padding manipulation
    auto* b_bytes = reinterpret_cast<unsigned char*>(&b);  // NOLINT: padding manipulation
    std::memset(a_bytes + 1,  0xAB, 7);  // 7-byte pad after flags       (offset 1..7)
    std::memset(a_bytes + 28, 0xAB, 4);  // 4-byte pad after frame_number (offset 28..31)
    std::memset(b_bytes + 1,  0xCD, 7);  // same locations, different pattern
    std::memset(b_bytes + 28, 0xCD, 4);

    // Both structs are logically identical (same flags, positions, frame, velocities).
    // snapshot_equals MUST return true; memcmp will return non-zero under the bug.
    EXPECT_TRUE(snapshot_equals(a, b))
        << "snapshot_equals returned false for logically-equal snapshots — "
           "memcmp is comparing padding bytes that were set to different patterns (BUG-008)";
}

}  // namespace
