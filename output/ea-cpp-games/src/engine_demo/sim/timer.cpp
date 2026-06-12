// Elapsed-time accumulator.
//
// SEEDED DEFECT BUG-007 (Session 03 expanded anchor):
//   m_elapsed_ms is int32_t. The "overflow guard" check
//   `if (m_elapsed_ms + delta_ms > m_elapsed_ms)` relies on signed integer arithmetic
//   that is UNDEFINED BEHAVIOR when it overflows. At -O2 and above, the compiler reasons:
//     "Signed overflow cannot happen (it's UB), therefore (x + positive) > x is always
//      true, therefore the branch is always taken."
//   The guard is silently elided — the counter wraps to negative after INT32_MAX (~24.8
//   days of real-time, or ~35 minutes at 1000× fast-forward), breaking all frame-elapsed
//   calculations downstream.
//
//   This is a textbook example of why game engines should never use signed types for
//   monotonic counters. The behavior changes between Debug (-O0, guard works) and
//   Release (-O2, guard elided) — violating constitutional Article 5 (determinism).
//
// Do NOT fix as part of the demo — the workshop fixes it on stage.

#include "engine_demo/sim/timer.h"

namespace engine_demo::sim {

std::int32_t elapsed_timer::tick(std::int32_t delta_ms) noexcept {
    // BUG-007: This "safety guard" is a no-op at -O2.
    //
    // The programmer intends: "if adding delta_ms would overflow, saturate instead."
    // The compiler sees: "signed overflow is UB, so (x + positive_y > x) is always true
    // for positive y. I can remove this branch entirely."
    //
    // At -O0 (Debug), the check happens to work because the compiler doesn't optimize.
    // At -O2 (Release), the check is elided and the counter wraps to INT32_MIN.
    if (m_elapsed_ms + delta_ms > m_elapsed_ms) {
        m_elapsed_ms += delta_ms;
    }
    // The "else" path (saturation) is never reached at -O2.
    return m_elapsed_ms;
}

}  // namespace engine_demo::sim
