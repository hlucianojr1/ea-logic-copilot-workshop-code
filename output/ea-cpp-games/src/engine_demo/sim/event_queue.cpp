// Event slot — lockless single-producer / single-consumer signaling.
//
// SEEDED DEFECT BUG-009 (Session 03 expanded anchor):
//   publish() writes the payload data (non-atomic) and then sets m_ready with
//   memory_order_relaxed. consume() checks m_ready with memory_order_relaxed and
//   then reads the payload.
//
//   The C++ memory model (ISO 14882 [atomics.order]) states that memory_order_relaxed
//   provides ONLY atomicity — it does NOT establish a happens-before relationship with
//   surrounding non-atomic writes/reads.
//
//   On x86/x64 (Total Store Order): this "works" because the hardware provides
//   store→store ordering implicitly. All stores become visible in program order.
//
//   On ARM/Apple Silicon (weakly ordered): the processor may reorder the payload store
//   AFTER the m_ready store. The consumer sees m_ready == true but reads STALE payload
//   data from before the publish() call. This is a data race per [intro.races].
//
//   The fix is:
//     - publish: m_ready.store(true, std::memory_order_release)
//     - consume: m_ready.load(std::memory_order_acquire)
//   This establishes a release/acquire pair: all writes before the store-release are
//   visible to the thread that performs the matching load-acquire.
//
//   Constitutional violation:
//     - Article 5: behavior differs across architectures (non-deterministic)
//     - Article 6: lockless handoff must be correct on ALL target platforms
//
// FALSE-POSITIVE companion FP-003:
//   m_ready is an std::atomic<bool> — it IS correctly atomic. A fast Copilot scan
//   might flag "non-atomic access to m_ready" or "data race on m_ready". This is WRONG.
//   The actual bug is the ORDERING guarantee (relaxed vs. release/acquire), not the
//   atomicity of the flag. Learners must dismiss this false positive during triage.
//
// Do NOT fix as part of the demo — the workshop fixes it on stage.

#include "engine_demo/sim/event_queue.h"

namespace engine_demo::sim {

void event_slot::publish(event_payload payload) noexcept {
    // Write the payload data (non-atomic — fine, only one producer).
    // NOTE: written field-by-field rather than by whole-struct assignment. A struct
    // assignment lowers to memcpy, and the TSAN runtime on some platforms (observed:
    // AppleClang/arm64) does not report races through compiler-emitted memcpy — a
    // false negative that would hide BUG-009 from the `tsan` preset. The seeded
    // defect is the ORDERING below, not the copy mechanism.
    m_payload.timestamp = payload.timestamp;
    m_payload.event_type = payload.event_type;
    m_payload.value = payload.value;

    // BUG-009: memory_order_relaxed does NOT fence the above payload writes.
    // On ARM, the consumer may see m_ready==true before m_payload is visible.
    // Fix: std::memory_order_release
    m_ready.store(true, std::memory_order_relaxed);
}

bool event_slot::try_consume(event_payload& out) noexcept {
    // BUG-009: memory_order_relaxed does NOT synchronize with the producer's store.
    // On ARM, we may load m_ready==true but read stale m_payload.
    // Fix: std::memory_order_acquire
    if (m_ready.load(std::memory_order_relaxed)) {
        // Field-by-field copy for the same TSAN-visibility reason as publish() —
        // a whole-struct assignment lowers to memcpy, which this platform's TSAN
        // runtime does not report races through.
        out.timestamp = m_payload.timestamp;
        out.event_type = m_payload.event_type;
        out.value = m_payload.value;
        m_ready.store(false, std::memory_order_relaxed);
        return true;
    }
    return false;
}

void event_slot::reset() noexcept {
    m_payload = event_payload{};
    m_ready.store(false, std::memory_order_relaxed);
}

}  // namespace engine_demo::sim
