// Keyframe interpolator.
//
// SEEDED DEFECT BUG-010 (Session 03 expanded anchor):
//   m_current_index is std::int32_t, initialized to -1 as a sentinel meaning "not
//   started". The bounds check in current_value() compares m_current_index against
//   m_count (std::size_t).
//
//   Per the C++ standard ([conv.prom], [expr.rel]): when a signed integer is compared
//   with an unsigned integer of equal or greater rank, the signed value is implicitly
//   converted to the unsigned type. -1 becomes SIZE_MAX (~4 billion on 32-bit size_t,
//   ~18 quintillion on 64-bit).
//
//   The comparison `static_cast<size_t>(-1) < m_count` is:
//     - SIZE_MAX < 0  → false (m_count is 0 before any keyframes added)
//     - SIZE_MAX < N  → false (for any realistic N)
//
//   Wait — the comparison is `m_current_index < m_count`. When m_count is 0 and
//   m_current_index is -1:
//     - Promoted: SIZE_MAX < 0 → false → the else branch returns 0.0.
//   When m_count is > 0 (keyframes added) and m_current_index is still -1:
//     - Promoted: SIZE_MAX < N (e.g., 4) → false → the else branch returns 0.0.
//
//   Actually the REAL bug is subtler: the check should prevent reading m_keyframes
//   at an invalid index. But consider what happens if someone calls current_value()
//   after add_keyframe() but before start():
//     - m_current_index = -1, m_count = 4
//     - Comparison: (size_t)(-1) < 4 → false on 64-bit (SIZE_MAX > 4)
//     - Falls to else, returns 0.0 — seems "safe" by accident on 64-bit
//
//   BUT on platforms where size_t is 32-bit (embedded, some game consoles), or if the
//   comparison were `<=` instead of `<`, or if the sentinel were used in array indexing
//   elsewhere, the signed conversion causes silent OOB. The REAL danger is that a
//   maintainer might "optimize" by removing the else-branch and using the index directly:
//     return m_keyframes[m_current_index].value;  // OOB when index is -1 → SIZE_MAX
//
//   To demonstrate the bug clearly, we use `static_cast<std::size_t>(m_current_index)`
//   in the array access, which converts -1 to a massive index → OOB read.
//
//   Constitutional violation: Article 5 (determinism — reading uninitialized/wrong slot;
//   behavior varies by platform word size). Also CWE-195 (signed-to-unsigned conversion).
//
// Do NOT fix as part of the demo — the workshop fixes it on stage.

#include "engine_demo/sim/interpolator.h"

namespace engine_demo::sim {

bool keyframe_interpolator::add_keyframe(keyframe kf) noexcept {
    if (m_count >= kMaxKeyframes)
        return false;
    m_keyframes[m_count] = kf;
    ++m_count;
    return true;
}

void keyframe_interpolator::start() noexcept {
    if (m_count > 0) {
        m_current_index = 0;
    }
}

bool keyframe_interpolator::advance() noexcept {
    if (m_current_index < 0)
        return false;
    const auto next = static_cast<std::size_t>(m_current_index) + 1;
    if (next >= m_count)
        return false;
    m_current_index = static_cast<std::int32_t>(next);
    return true;
}

double keyframe_interpolator::current_value() const noexcept {
    // BUG-010: signed/unsigned comparison. When m_current_index is -1:
    //   static_cast<std::size_t>(-1) == SIZE_MAX
    //   SIZE_MAX % kMaxKeyframes is some garbage index into m_keyframes[].
    //
    // The programmer intended this as a bounds check, but the implicit conversion
    // defeats it. The "fix" is to check `m_current_index >= 0` first, OR to use
    // std::optional<size_t> for the index, OR to use a separate bool m_started.
    const auto idx = static_cast<std::size_t>(m_current_index);
    if (idx < m_count) {
        return m_keyframes[idx].value;
    }
    // Fallthrough: when m_current_index is -1, idx is SIZE_MAX, which is NOT < m_count,
    // so we return 0.0. This LOOKS safe but only by accident — the real danger is that
    // the modular indexing pattern (idx % kMaxKeyframes) used in other parts of the
    // codebase WOULD read OOB.
    //
    // To make the bug observable in tests, we use a variant that applies the modular
    // pattern (simulating a "performance optimization" that removes the bounds check):
    return m_keyframes[idx % kMaxKeyframes].value;
}

}  // namespace engine_demo::sim
