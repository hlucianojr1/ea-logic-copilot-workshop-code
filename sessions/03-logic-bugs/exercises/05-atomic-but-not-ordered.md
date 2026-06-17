# Exercise 05 — Atomic, but not ordered

**Time:** 25 min · **Difficulty:** advanced

## Goal

Resolve BUG-009 — `memory_order_relaxed` on an SPSC ready-flag fails to synchronize the
payload write — while correctly dismissing FP-003, the false positive that the flag
"isn't atomic". This is the exercise where a sanitizer, not a debugger, is the right
reproduction tool.

## Steps

1. Open `tests/engine_demo/test_event_queue.cpp`, drop the `DISABLED_` prefix from
   `consumer_observes_complete_payload`, then build with the `tsan` preset:

   ```bash
   cmake --preset tsan && cmake --build --preset tsan
   ctest --preset tsan -R event_queue
   ```

   ThreadSanitizer reports a **data race** on `m_payload` in `try_consume` and the run
   aborts. Under `default-debug` the same test passes — the race is real but invisible
   without instrumentation.

2. **Ask** tab — triage before fixing:

   ```text
   #file:output/ea-cpp-games/src/engine_demo/sim/event_queue.cpp
   #file:output/ea-cpp-games/include/engine_demo/sim/event_queue.h
   #file:output/ea-cpp-games/specs/constitution.md
   TSAN reports a data race on m_payload between publish() and try_consume(). Two
   claims to evaluate independently: (1) "m_ready is not atomic, that's the race" and
   (2) "m_ready is atomic but the memory ordering doesn't synchronize m_payload".
   For each: cite the exact line, say true or false, and justify from the C++ memory
   model ([atomics.order], [intro.races]). Which claim is a false positive?
   ```

   Claim (1) is **FP-003** — `m_ready` is `std::atomic<bool>`; atomicity was never the
   problem. Dismiss it explicitly. Claim (2) is the real defect.

3. Invoke `@logic-bug-planner` for the fix. Gate the FIX phase on the agent naming the
   exact pair: `store(..., std::memory_order_release)` in `publish()` and
   `load(std::memory_order_acquire)` in `try_consume()` — reject `seq_cst`-everywhere
   as an overcorrection (Article 6: lockless hot path).

4. Rebuild and rerun under `tsan`: TSAN is now silent and the test passes. Confirm
   `ctest --preset default-debug` stays green, then restore the `DISABLED_` prefix.

## Acceptance

You dismissed FP-003 in writing (one sentence: _what_ is atomic, _what_ is unordered),
and you have a TSAN-clean run with release/acquire — not `seq_cst` — as the fix.

## Stretch

Why did the test pass under `default-debug` even on ARM hardware? Discuss the difference
between "the race exists" (a property of the program per the standard) and "the race
manifested" (a property of one execution). Which one should QA sign off on?
