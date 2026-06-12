# Exercise 01 — Test before fix

**Time:** 15 min · **Difficulty:** intermediate

## Goal

For BUG-002, write the failing test **first**, watch it fail, then write the fix and watch it pass — never the reverse.

## Steps

1. Open `tests/engine_demo/test_game_loop.cpp`.
2. Drop the `DISABLED_` prefix from `long_run_does_not_drift`. Run ctest. Observe failure.
3. In the **Edit** tab, apply the BUG-002 fix from the facilitator script.
4. Rerun ctest. Observe pass.

## Acceptance

You can articulate, without looking at the diff, why a `double` accumulator is sufficient where a `float` was not.

## Stretch

Add a second test that asserts `accumulator_seconds()` equals zero (within ulp) after `kFrames` exact-period advances.
