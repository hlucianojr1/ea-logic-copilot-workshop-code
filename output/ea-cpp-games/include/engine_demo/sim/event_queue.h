// Single-producer / single-consumer event slot for cross-thread signaling.
//
// Constitutional articles satisfied:
//   - 1 (no exceptions)
//   - 5 (determinism — note SEEDED DEFECT)
//   - 6 (real-time: lockless, no allocation in publish/consume)
//
// SEEDED DEFECT BUG-009: see src/engine_demo/sim/event_queue.cpp.

#pragma once

#include <atomic>
#include <cstdint>

namespace engine_demo::sim {

struct event_payload {
    std::uint64_t timestamp{0};
    std::uint32_t event_type{0};
    double value{0.0};
};

// A single-slot SPSC event channel. The producer writes a payload and signals readiness;
// the consumer polls for readiness and reads the payload.
//
// BUG-009: The memory ordering is insufficient — see implementation.
class [[nodiscard]] event_slot {
   public:
    event_slot() noexcept = default;

    // Producer: publish an event payload and signal consumers.
    void publish(event_payload payload) noexcept;

    // Consumer: attempt to read the latest event. Returns true if a new event was
    // available, and writes it to `out`. Returns false if no new event.
    [[nodiscard]] bool try_consume(event_payload& out) noexcept;

    // Reset the slot to empty state.
    void reset() noexcept;

   private:
    event_payload m_payload{};
    // FP-003 (false positive): m_ready IS correctly atomic — the bug is the ORDERING
    // (memory_order_relaxed), not the atomicity of the flag itself.
    std::atomic<bool> m_ready{false};
};

}  // namespace engine_demo::sim
