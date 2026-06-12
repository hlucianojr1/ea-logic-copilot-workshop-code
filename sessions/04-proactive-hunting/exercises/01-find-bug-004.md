# Exercise 01 — Find BUG-004 from cold

**Time:** 15 min · **Difficulty:** advanced

## Goal

Without consulting the seeded-bugs catalog, run the logic-enumeration prompt against `engine_demo::physics::constraint_solver` and surface BUG-004 (non-determinism via hash-map iteration order).

## Steps

1. Plan Mode, belt: header + implementation + constitution.
2. Run:

```text
List up to five candidate defects in this file. For each: (a) one-line description, (b)
the constitutional article it most likely violates, (c) the smallest test that would
demonstrate it.
```

1. Triage with the rubric. Decide.

## Acceptance

You identify the hash-map traversal as a determinism risk and articulate Article 5 as the violated article.

## Stretch

Sketch a deterministic remediation in a follow-up Plan Mode prompt — _do not implement it_. Save the sketch for an office-hours review.
