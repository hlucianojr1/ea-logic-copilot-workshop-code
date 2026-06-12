# Exercise 01 — Rewrite an acceptance criterion

**Time:** 15 min · **Difficulty:** intermediate

## Goal

After `/specify` produces `specs/lockless-ring-buffer/spec.md`, manually rewrite **one** acceptance criterion to be sharper. Re-run `/plan` and observe the diff.

## Steps

1. Read `spec.md`'s acceptance section.
2. Pick the vaguest criterion. Rewrite it with a concrete invariant (e.g., a happens-before relationship, a memory-order guarantee).
3. Re-run `/plan`. Diff against the prior plan.

## Acceptance

The new plan reflects the sharpened criterion (different test cases, tighter atomics ordering, etc.).

## Reflection

Which kinds of vagueness in the spec produced the largest plan deltas? Those are the ones to police hardest in your day job.
