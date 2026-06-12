// Elapsed-time accumulator for simulation fast-forward scenarios.
//
// Constitutional articles satisfied:
//   - 1 (no exceptions)
//   - 5 (determinism — note SEEDED DEFECT)
//   - 6 (real-time: no allocation in tick())
//
// SEEDED DEFECT BUG-007: see src/engine_demo/sim/timer.cpp.

#pragma once

#include <cstdint>

namespace engine_demo::sim {

class [[nodiscard]] elapsed_timer {
   public:
    elapsed_timer() noexcept = default;

    // Advance the timer by `delta_ms` milliseconds.
    // Returns the new elapsed time. The "safety guard" is intentionally flawed.
    [[nodiscard]] std::int32_t tick(std::int32_t delta_ms) noexcept;

    [[nodiscard]] std::int32_t elapsed_ms() const noexcept { return m_elapsed_ms; }

    void reset() noexcept { m_elapsed_ms = 0; }

   private:
    // BUG-007 anchor: this is intentionally `int32_t` rather than `uint64_t`.
    // Signed overflow is UB; the compiler will exploit this at -O2.
    std::int32_t m_elapsed_ms{0};
};

}  // namespace engine_demo::sim
