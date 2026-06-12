# Exercise 01 — Score three candidate tasks

**Time:** 10 min · **Difficulty:** beginner

## Goal

For each candidate, score against the rubric (deterministic / well-tested / single-PR-sized) and decide: dispatch, refine, or do-yourself.

## Candidates

1. "Add a `to_string()` member to `entity_handle`."
2. "Make the constraint solver deterministic."
3. "Update README.md to mention the lockless ring buffer."
4. "Refactor the allocator to be lock-free."
5. "Add an `observed_max()` accessor to `frame_budget`."

## Acceptance

You can name, for each candidate: which rubric criteria pass, which fail, and the resulting decision.

## Reflection

Tasks that fail the rubric usually fail "single-PR-sized" first. The fix is decomposition, not delegation.
