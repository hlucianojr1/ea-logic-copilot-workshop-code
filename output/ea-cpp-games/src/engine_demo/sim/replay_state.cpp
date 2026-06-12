// Replay snapshot comparison.
//
// SEEDED DEFECT BUG-008 (Session 03 expanded anchor):
//   snapshot_equals() uses std::memcmp to compare two replay_snapshot structs for
//   "performance". This reads ALL bytes in the struct — including the 11 bytes of
//   padding (7 bytes after `flags`, 4 bytes after `frame_number`).
//
//   Padding bytes are UNINITIALIZED when the struct is constructed on the stack without
//   memset. Two structs with identical member values but allocated on different stack
//   frames will have different padding contents. The comparison returns false for
//   logically-equal snapshots.
//
//   This is a textbook C++ pitfall: `memcmp` is only safe for types where
//   `std::has_unique_object_representations_v<T>` is true (no padding, no float NaN
//   bit patterns). replay_snapshot has padding → memcmp is unsafe.
//
//   Constitutional violation: Article 5 (determinism — comparison result depends on
//   memory state, not logical state).
//
// Do NOT fix as part of the demo — the workshop fixes it on stage.

#include "engine_demo/sim/replay_state.h"

#include <cstring>

namespace engine_demo::sim {

bool snapshot_equals(const replay_snapshot& a, const replay_snapshot& b) noexcept {
    // BUG-008: memcmp reads padding bytes which are uninitialized.
    // The "fix" is to compare member-by-member, or to memset the struct to zero at
    // construction, or to reorder members to eliminate padding.
    return std::memcmp(&a, &b, sizeof(replay_snapshot)) == 0;
}

replay_snapshot make_snapshot(std::uint8_t flags,
                              double px,
                              double py,
                              std::uint32_t frame,
                              double vx,
                              double vy) noexcept {
    // NOTE: This does NOT zero-initialize padding bytes. Each call site may have
    // different garbage in padding depending on prior stack usage.
    replay_snapshot snap;
    snap.flags = flags;
    snap.position_x = px;
    snap.position_y = py;
    snap.frame_number = frame;
    snap.velocity_x = vx;
    snap.velocity_y = vy;
    return snap;
}

}  // namespace engine_demo::sim
