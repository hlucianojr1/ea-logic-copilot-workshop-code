// Replay snapshot for deterministic replay comparison.
//
// Constitutional articles satisfied:
//   - 1 (no exceptions)
//   - 5 (determinism — note SEEDED DEFECT)
//
// SEEDED DEFECT BUG-008: see src/engine_demo/sim/replay_state.cpp.

#pragma once

#include <cstdint>

namespace engine_demo::sim {

// NOTE: This struct has intentional padding due to member ordering.
// sizeof(replay_snapshot) is 48 bytes on most platforms, NOT 33 (the sum of member sizes).
//
// Layout (typical LP64 / LLP64):
//   offset 0:  flags          (1 byte)
//   offset 1:  [7 bytes PADDING]
//   offset 8:  position_x     (8 bytes)
//   offset 16: position_y     (8 bytes)
//   offset 24: frame_number   (4 bytes)
//   offset 28: [4 bytes PADDING]
//   offset 32: velocity_x     (8 bytes)
//   offset 40: velocity_y     (8 bytes)
//   total: 48 bytes
struct replay_snapshot {
    std::uint8_t flags{0};          // 1 byte — triggers 7 bytes of padding before next double
    double position_x{0.0};         // 8 bytes (alignment: 8)
    double position_y{0.0};         // 8 bytes
    std::uint32_t frame_number{0};  // 4 bytes — triggers 4 bytes of padding before next double
    double velocity_x{0.0};         // 8 bytes (alignment: 8)
    double velocity_y{0.0};         // 8 bytes
};

// Compare two replay snapshots for logical equality.
// BUG-008: uses memcmp which reads padding bytes — see implementation.
[[nodiscard]] bool snapshot_equals(const replay_snapshot& a, const replay_snapshot& b) noexcept;

// Create a snapshot with specific values (helper for tests and replay capture).
[[nodiscard]] replay_snapshot make_snapshot(std::uint8_t flags,
                                            double px,
                                            double py,
                                            std::uint32_t frame,
                                            double vx,
                                            double vy) noexcept;

}  // namespace engine_demo::sim
