# Exercise 04 — Bitwise vs. logical equality

**Time:** 15 min · **Difficulty:** intermediate

## Goal

Resolve BUG-008 — `memcmp` over a struct with padding bytes makes two logically
identical `replay_state` values compare unequal — using a Tree-of-Thought prompt to
surface competing hypotheses before committing to one.

## Steps

1. Open `tests/engine_demo/test_replay_state.cpp`, drop the `DISABLED_` prefix from
   `padding_does_not_affect_comparison`, and watch it fail:

   ```bash
   cmake --build --preset default-debug && ctest --preset default-debug -R replay
   ```

   Note: the failure can be intermittent — uninitialized padding sometimes happens to
   match. That intermittency is itself a clue.

2. **Ask** tab — ToT prompt (three experts, per training Section 5):

   ```text
   #file:output/ea-cpp-games/src/engine_demo/sim/replay_state.cpp
   #file:output/ea-cpp-games/include/engine_demo/sim/replay_state.h
   #file:output/ea-cpp-games/specs/constitution.md
   Two replay_state values built from identical inputs compare unequal — but only
   sometimes. Simulate three experts proposing distinct root-cause hypotheses
   (e.g., uninitialized member, padding bytes, float NaN semantics). Each expert:
   state the hypothesis, the evidence in this code, a confidence %, and a one-line
   disproof test. Then converge on the most probable cause.
   ```

3. Triage the three hypotheses. The padding expert should win: `memcmp` compares
   _object representation_ (including indeterminate padding), not _value
   representation_.

4. In the **Edit** tab, apply the fix: replace `memcmp` with member-wise `operator==`
   (or `= default` comparison, C++20). Rerun ctest until green.

## Acceptance

You can state the difference between object representation and value representation,
and your fix compiles warning-free under `-Werror` with no `memcmp` remaining in
`replay_state.cpp`.

## Reflection

`memcmp`-equality is a classic replay/desync bug in lockstep multiplayer engines: two
machines compute identical states that hash differently. Where else in this codebase
would a representation-vs-value confusion bite? (Hint: BUG-004's trace digest.)
