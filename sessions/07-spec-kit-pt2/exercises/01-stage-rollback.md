# Exercise 01 — Execute a stage roll-back

**Time:** 15 min · **Difficulty:** intermediate

## Goal

Deliberately introduce a vague spec, observe the cascade of poor downstream stages, then roll back to `/specify` and tighten.

## Steps

1. Run `/specify` for a _new_ trivial feature (e.g., a 64-bit counter type) with deliberately vague acceptance criteria ("counts things").
2. Run `/plan`, `/tasks`. Note the gaps.
3. Roll back: edit `spec.md` to be precise (overflow policy, atomicity, monotonicity).
4. Re-run `/plan`. Diff against the first attempt.

## Acceptance

You can articulate which spec edits triggered which plan changes.

## Reflection

Roll-back is not failure. It is the cheapest possible way to discover what `/specify` should have said.
