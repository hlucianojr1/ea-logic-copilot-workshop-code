#include "engine_demo/sim/event_queue.h"

#include <thread>

#include "gtest/gtest.h"

namespace {

using engine_demo::sim::event_payload;
using engine_demo::sim::event_slot;

TEST(EventSlot, PublishAndConsumeSingleThread) {
    event_slot slot;

    event_payload published{};
    published.timestamp = 12345;
    published.event_type = 7;
    published.value = 3.14;
    slot.publish(published);

    event_payload consumed{};
    EXPECT_TRUE(slot.try_consume(consumed));
    EXPECT_EQ(consumed.timestamp, 12345u);
    EXPECT_EQ(consumed.event_type, 7u);
    EXPECT_DOUBLE_EQ(consumed.value, 3.14);
}

TEST(EventSlot, ConsumeWithoutPublishReturnsFalse) {
    event_slot slot;
    event_payload out{};
    EXPECT_FALSE(slot.try_consume(out));
}

TEST(EventSlot, ConsumeOnlyOnce) {
    event_slot slot;

    event_payload p{};
    p.timestamp = 1;
    p.event_type = 2;
    p.value = 9.9;
    slot.publish(p);

    event_payload out{};
    EXPECT_TRUE(slot.try_consume(out));

    // Second consume should fail — event already consumed.
    event_payload out2{};
    EXPECT_FALSE(slot.try_consume(out2));
}

TEST(EventSlot, ResetClearsSlot) {
    event_slot slot;

    event_payload p{};
    p.timestamp = 999;
    slot.publish(p);
    slot.reset();

    event_payload out{};
    EXPECT_FALSE(slot.try_consume(out));
}

// REGRESSION TEST for BUG-009:
// The bug is that publish() uses memory_order_relaxed on the m_ready flag, which does
// NOT establish a happens-before relationship for the non-atomic m_payload write.
//
// On weakly-ordered architectures (ARM/Apple Silicon), the consumer thread can observe
// m_ready == true BEFORE the payload writes are visible — reading partially-written or
// stale payload data.
//
// On x86 (TSO), the hardware provides implicit store→store ordering so the torn read
// rarely manifests. The reliable reproduction is ThreadSanitizer, which flags the
// data race on m_payload even when the torn read does not actually occur:
//
//   cmake --preset tsan && cmake --build --preset tsan
//   ctest --preset tsan -R event_queue
//
// The test is deliberately a SINGLE cross-thread handoff with no other synchronization.
// Any extra sync (e.g., an acquire/release handshake counter between handoffs) creates
// happens-before edges that mask the race from TSAN's vector clocks.
//
// Expected (correct with release/acquire): TSAN is silent; consumer reads a complete
// payload.
// Actual (buggy with relaxed): TSAN reports "data race" on m_payload and the run aborts.
TEST(EventSlot, DISABLED_consumer_observes_complete_payload) {
    event_slot slot;

    std::thread producer([&slot] {
        event_payload p{};
        p.timestamp = 0xDEAD'BEEF'CAFE'BABE;
        p.event_type = 42;
        p.value = 2.718281828;
        slot.publish(p);
    });

    // Consumer: spin until the producer's publish is visible, then read the payload.
    // The producer→consumer edge is exactly what publish()/try_consume() must provide —
    // and with memory_order_relaxed it does not.
    event_payload consumed{};
    while (!slot.try_consume(consumed)) {
    }

    // If ordering is correct, ALL fields must match exactly.
    EXPECT_EQ(consumed.timestamp, 0xDEAD'BEEF'CAFE'BABE)
        << "Timestamp mismatch — torn/stale read due to relaxed ordering (BUG-009)";
    EXPECT_EQ(consumed.event_type, 42u) << "Event type mismatch — torn/stale read (BUG-009)";
    EXPECT_DOUBLE_EQ(consumed.value, 2.718281828) << "Value mismatch — torn/stale read (BUG-009)";

    producer.join();
}

}  // namespace
