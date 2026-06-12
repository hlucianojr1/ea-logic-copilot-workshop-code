# Exercise 02 — Finish backpressure on your own

**Time:** 20 min · **Difficulty:** advanced

## Goal

Take the backpressure spec produced in the live demo and drive it through `/plan → /tasks → /implement`. Tests must be green.

## Steps

1. Read `specs/lockless-ring-buffer/spec.md` — confirm backpressure section was added.
2. `/plan` then `/tasks`.
3. `/implement` each task, HITL on every diff.
4. Tests must include: drop_oldest preserves capacity, drop_newest rejects new entries when full, spin_until_space respects the timeout deadline.

## Acceptance

- ctest green.
- No `std::` containers introduced.
- The backpressure_policy enum is `[[nodiscard]]`-safe (callers cannot accidentally drop a returned status).

## Stretch

Add a fuzz test that randomizes producer/consumer cadence and asserts no ABA-class bugs.
