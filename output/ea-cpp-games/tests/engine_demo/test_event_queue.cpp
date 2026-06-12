#include "engine_demo/sim/event_queue.h"

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
// On x86 (TSO), this test ALWAYS passes because the hardware provides implicit
// store→store ordering. The test is DISABLED because it demonstrates a race that is
// only reliably observable on ARM with TSAN or stress tools.
//
// To reproduce on ARM:
//   1. Compile with -fsanitize=thread (TSAN)
//   2. Run with TSAN — it flags the data race on m_payload.
//
// Expected (correct with release/acquire): consumer always reads complete payload.
// Actual (buggy with relaxed): TSAN reports data race; on ARM hardware, payload may
// be partially written when consumed.
TEST(EventSlot, DISABLED_consumer_observes_complete_payload) {
    // NOTE: This test is a simplified single-threaded stand-in. The real validation
    // requires multi-threaded stress testing or TSAN. In single-threaded execution,
    // relaxed ordering has no observable effect. The test documents intent.
    event_slot slot;

    event_payload published{};
    published.timestamp = 0xDEAD'BEEF'CAFE'BABE;
    published.event_type = 42;
    published.value = 2.718281828;
    slot.publish(published);

    event_payload consumed{};
    ASSERT_TRUE(slot.try_consume(consumed));

    // If ordering is correct, ALL fields must match exactly.
    EXPECT_EQ(consumed.timestamp, 0xDEAD'BEEF'CAFE'BABE)
        << "Timestamp mismatch — possible torn read due to relaxed ordering (BUG-009)";
    EXPECT_EQ(consumed.event_type, 42u)
        << "Event type mismatch — possible torn read (BUG-009)";
    EXPECT_DOUBLE_EQ(consumed.value, 2.718281828)
        << "Value mismatch — possible torn read (BUG-009)";
}

}  // namespace
