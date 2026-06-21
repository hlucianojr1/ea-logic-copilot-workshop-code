# Exercise 06 — The sentinel trap

**Time:** 20 min · **Difficulty:** intermediate

## Goal

Resolve BUG-010 — a `-1` sentinel in an `int32_t` index is cast to `size_t`, becoming
`SIZE_MAX` and defeating the bounds check — and measure CoT against ToT on the same bug
to learn when each technique earns its cost.

> 🔧 **Setup** — start from a clean baseline. Paste into the **Agent** panel:

```text
@logic-bug-planner
Confirm output/ea-cpp-games/ is clean for BUG-010: ctest --preset default-debug is green and
unstarted_does_not_read_oob is still DISABLED_. Run ./reset_workshop.sh if not. Do not fix.
```

## Steps

1. Open `tests/engine_demo/test_interpolator.cpp`, drop the `DISABLED_` prefix from
   `unstarted_does_not_read_oob`, and watch it fail:

   ```bash
   cd output/ea-cpp-games
   cmake --build --preset default-debug && ctest --preset default-debug -R interpolator
   ```

2. **Round 1 — CoT.** Ask tab, linear reasoning only:

   ```text
   #file:output/ea-cpp-games/src/engine_demo/sim/interpolator.cpp
   #file:output/ea-cpp-games/include/engine_demo/sim/interpolator.h
   An unstarted interpolator reads an arbitrary array slot instead of returning the
   default value. Reason step by step through sample()'s control flow with
   m_current_index == -1: trace the value through every conversion, state where the
   bounds check stops protecting, and name the root cause. One linear chain — no
   alternatives.
   ```

3. **Round 2 — ToT.** New chat (fresh context), same files plus the constitution:

   ```text
   #file:output/ea-cpp-games/src/engine_demo/sim/interpolator.cpp
   #file:output/ea-cpp-games/include/engine_demo/sim/interpolator.h
   #file:output/ea-cpp-games/specs/constitution.md
   Same symptom: unstarted interpolator reads out of bounds. Simulate three experts
   with distinct hypotheses (e.g., off-by-one in the bounds check, signed-to-unsigned
   conversion at the sentinel, stale keyframe pointer). Each: hypothesis, evidence,
   confidence %, one-line disproof. Converge.
   ```

4. Compare the two transcripts: time to root cause, confidence calibration, wrong
   turns. For a bug with one short data path, CoT usually lands first — record whether
   that held for you.

5. Fix it in the **Edit** tab. Acceptable fixes: early-return on the sentinel before
   any conversion, or replacing the sentinel with `eastl::optional`-style state. The
   cast must never see `-1`. Rerun ctest until green.

## Common pitfalls

- **Widening the bounds check.** The defect is the `-1` → `size_t` conversion becoming
  `SIZE_MAX`, not an off-by-one. Guard the sentinel _before_ the cast.
- **Letting the cast see `-1`.** Any fix where `static_cast<size_t>` still receives the
  sentinel is wrong. Early-return or change the representation.
- **Skipping Round 1 (CoT).** The CoT-vs-ToT comparison is the lesson; don't jump straight to
  the fix.

## Acceptance

The regression test passes, and you wrote a two-line verdict: which technique found the
root cause faster _on this bug_, and one sentence on when you'd pay ToT's token cost
anyway (hint: Exercise 04's intermittent symptom).

## Reflection

`-1` sentinels meeting `size_t` is CWE-195 and endemic in engine code that indexes with
`int` "for the sentinel". What signature change would make this entire bug class
unrepresentable?
