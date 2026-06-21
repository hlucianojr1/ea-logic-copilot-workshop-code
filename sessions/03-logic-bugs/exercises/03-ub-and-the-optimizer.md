# Exercise 03 — UB and the optimizer

**Time:** 20 min · **Difficulty:** advanced

## Goal

Reproduce BUG-007 — a signed-overflow guard that "works" in Debug but is elided by the
optimizer at `-O2` — and experience why Debug-only testing gives false confidence.

## Steps

1. Build and test in Debug first. Open `tests/engine_demo/test_timer.cpp`, drop the
   `DISABLED_` prefix from `overflow_guard_not_elided`, then:

   ```bash
   cd output/ea-cpp-games
   cmake --preset default-debug && cmake --build --preset default-debug
   ctest --preset default-debug -R timer
   ```

   The test **passes**. The bug is invisible in Debug.

2. Now build with the `optimized` preset (RelWithDebInfo, `-O2 -DNDEBUG`):

   ```bash
   cd output/ea-cpp-games
   cmake --preset optimized && cmake --build --preset optimized
   ctest --preset optimized -R timer
   ```

   The same test **fails** — the compiler legally deleted the `x + delta > x` guard
   because signed overflow is undefined behavior.

3. **Ask** tab — have Copilot explain the discrepancy before fixing anything:

   ```text
   #file:output/ea-cpp-games/include/engine_demo/sim/timer.h
   #file:output/ea-cpp-games/src/engine_demo/sim/timer.cpp
   This test passes at -O0 but fails at -O2. Step by step: (a) which expression is
   undefined behavior per [expr.pre]p4 (signed overflow), (b) why the optimizer may assume it never
   overflows, (c) what the compiler does to the guard as a result. Do not propose a
   fix yet.
   ```

4. Invoke `@logic-bug-planner` to drive the fix through its four phases. Approve the
   FIX phase only after the agent states the UB-free guard form (check against
   overflow _before_ adding, e.g. comparing against
   `std::numeric_limits<std::int64_t>::max() - delta`).

5. Rerun **both** presets. The test must pass under `default-debug` **and** `optimized`.

## Acceptance

You can explain, without notes, why "the test passed in Debug" is not evidence of
correctness when UB is involved — and you have a green run under `ctest --preset
optimized` to prove the fix.

## Stretch

Re-run the buggy version with `-fsanitize=undefined` added to `CMAKE_CXX_FLAGS` and
compare UBSan's runtime report with the optimizer's silent elision. Which would your CI
have caught?
