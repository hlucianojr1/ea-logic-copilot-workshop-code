# Exercise 01 — Squad on a different task

**Time:** 20 min · **Difficulty:** advanced

## Goal

Apply the squad pattern to a smaller task: "Add an `engine_demo::frame_budget::worst_sample()` accessor with regression tests."

## Steps

1. Coordinator: produce `decisions.md` decomposition.
2. Architect: produce `api.md`.
3. Developer: implement.
4. Tester: add regression test.
5. ctest green; reviewer chat mode pass.

## Acceptance

- All squad artifacts under `docs/plans/squad-worst-sample/`.
- Each mode stayed in its layer (no cross-layer edits).
- ctest green.

## Reflection

The smallest squad task that's worth the orchestration overhead is _bigger than you'd think_. Note the threshold for your own use.
