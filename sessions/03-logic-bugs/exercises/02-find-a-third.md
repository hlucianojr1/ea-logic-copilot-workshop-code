# Exercise 02 — Find a third logic bug

**Time:** 15 min · **Difficulty:** advanced

## Goal

Without consulting the seeded-bugs catalog, ask Copilot to surface candidate logic defects in `engine_demo::physics::constraint_solver`. Triage the list using the rubric from Session 04 (preview).

## Steps

1. **Ask** tab:

```text
#file:output/ea-cpp-games/include/engine_demo/physics/constraint.h
#file:output/ea-cpp-games/src/engine_demo/physics/constraint.cpp
#file:output/ea-cpp-games/specs/constitution.md
List up to five candidate logic defects in this file. For each: (a) reproduce in <5 lines,
(b) trace data flow, (c) cite the constitutional article it violates.
```

1. For each candidate, decide: **real bug** (write a failing test) or **false positive** (one-line code comment justifying dismissal).

## Acceptance

You identify BUG-004 (non-determinism via hash-map order) **and** correctly dismiss FP-002 (the sentinel-iteration false alarm).

## Reflection

Session 04 is built on this rubric. You're previewing it deliberately.
