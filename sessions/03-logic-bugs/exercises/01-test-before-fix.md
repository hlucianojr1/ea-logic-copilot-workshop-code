# Exercise 01 — Test before fix

**Time:** 15 min · **Difficulty:** intermediate

## Goal

For BUG-002, write the failing test **first**, watch it fail, then write the fix and watch it
pass — never the reverse. This is Article 7 (test-first) made concrete.

> 🔧 **Setup** — start from a clean, green baseline. Paste into the **Agent** panel:

```text
@logic-bug-tutor
Confirm output/ea-cpp-games/ is at the clean seeded baseline for BUG-002:
ctest --preset default-debug is green and long_run_does_not_drift is still DISABLED_.
Run ./reset_workshop.sh if it is not. Do not fix anything.
```

## Concept — why test-first matters here

BUG-002 is a _silent_ numerical drift: a `float` accumulator loses precision as `1.0/60.0`
(not representable in binary) is added ~1800 times. Nothing crashes; a replay just diverges.
If you "fix" first and test second, you have no proof the fix addressed _this_ drift rather
than masking it. Writing the failing test first pins the exact symptom — divergence after a
long run — so the green run afterward is real evidence.

## Steps

1. Open `tests/engine_demo/test_game_loop.cpp`. Remove the `DISABLED_` prefix from
   `long_run_does_not_drift`.

2. Build and run just that test — it must go **red** first:

   ```bash
   cd output/ea-cpp-games
   cmake --build --preset default-debug
   ctest --preset default-debug --output-on-failure -R test_game_loop
   ```

3. In the **Edit** tab, drive the fix:

   ```text
   #file:output/ea-cpp-games/include/engine_demo/sim/game_loop.h
   #file:output/ea-cpp-games/src/engine_demo/sim/game_loop.cpp
   Promote m_accumulator_seconds from float to double and remove the now-redundant
   static_cast<float> calls. Constitutional articles 1, 2, and 5 must hold. Show the diff.
   ```

4. Review the diff, accept it, rebuild, and rerun — the test must now be **green**, then run
   the full suite:

   ```bash
   cd output/ea-cpp-games
   ctest --preset default-debug --output-on-failure
   ```

## What good looks like

- The test failed **before** any source edit (you saw red).
- The diff touches only the header + source: `float` → `double`, redundant casts removed. No
  new guard, no `std::`, no epsilon tolerance added to the test.
- `long_run_does_not_drift` and the full suite are green.

## Common pitfalls

- **Fixing before reproducing.** If you edit the source before seeing red, you skipped the
  proof step — revert and start over.
- **Forgetting to rebuild.** `ctest` does not compile; run `cmake --build` after
  un-`DISABLED_`-ing the test.
- **Loosening the test instead of the type.** Adding an epsilon tolerance to make it pass
  hides the drift. The fix is the wider type.

## Acceptance

You can articulate, without looking at the diff, why a `double` accumulator is sufficient
where a `float` was not — and you saw the test go red _before_ it went green.

## Stretch

Add a second test that asserts `accumulator_seconds()` equals zero (within ulp) after `kFrames` exact-period advances.
