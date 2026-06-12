# Exercise 02 — Dismiss FP-002 with a one-line comment

**Time:** 10 min · **Difficulty:** intermediate

## Goal

For FP-002 (the constraint-solver "sentinel iteration" false positive), use the bit-level / data-flow walkthrough technique to confirm it's not a defect, then commit a one-line dismissal comment.

## Steps

1. Plan Mode:

```text
#file:output/ea-cpp-games/src/engine_demo/physics/constraint.cpp
Walk the loop in solve(). Does the trailing iteration ever read past m_constraints.size()?
Show your reasoning.
```

1. If the answer is "no, sentinel only", switch to Edit Mode and add a comment immediately above the loop:

```text
Append a one-line comment above the for-loop in solve() noting the sentinel-iteration
behavior and pointing to FP-002 in fixtures/seeded-bugs.md.
```

## Acceptance

The comment is < 100 columns, cites FP-002, and does not change executable code.

## Reflection

Dismissal comments compound: future Copilot sessions reading this file see the comment, fold the dismissal into their context, and don't re-flag.
