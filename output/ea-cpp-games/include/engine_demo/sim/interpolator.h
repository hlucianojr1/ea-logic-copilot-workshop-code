// Keyframe interpolator for animation and parameter curves.
//
// Constitutional articles satisfied:
//   - 1 (no exceptions)
//   - 5 (determinism — note SEEDED DEFECT)
//   - 6 (real-time: no allocation in current_value())
//
// SEEDED DEFECT BUG-010: see src/engine_demo/sim/interpolator.cpp.

#pragma once

#include <cstddef>
#include <cstdint>

namespace engine_demo::sim {

struct keyframe {
    double time{0.0};
    double value{0.0};
};

// Fixed-capacity keyframe interpolator. Stores up to kMaxKeyframes entries.
// Must call start() before current_value(). The sentinel index -1 indicates
// "not yet started".
class [[nodiscard]] keyframe_interpolator {
   public:
    static constexpr std::size_t kMaxKeyframes = 64;

    keyframe_interpolator() noexcept = default;

    // Add a keyframe. Returns false if capacity exhausted.
    [[nodiscard]] bool add_keyframe(keyframe kf) noexcept;

    // Begin playback at keyframe 0.
    void start() noexcept;

    // Advance to the next keyframe. Returns false if already at the last keyframe.
    [[nodiscard]] bool advance() noexcept;

    // Read the current keyframe's value.
    // BUG-010: calling this before start() reads from an invalid index.
    [[nodiscard]] double current_value() const noexcept;

    [[nodiscard]] std::size_t keyframe_count() const noexcept { return m_count; }

   private:
    keyframe m_keyframes[kMaxKeyframes]{};
    std::size_t m_count{0};
    // BUG-010 anchor: -1 sentinel stored in a signed type, compared against unsigned m_count.
    std::int32_t m_current_index{-1};
};

}  // namespace engine_demo::sim
