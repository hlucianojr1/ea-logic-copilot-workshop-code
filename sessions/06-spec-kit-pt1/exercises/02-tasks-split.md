# Exercise 02 — Drive your own /tasks split

**Time:** 15 min · **Difficulty:** intermediate

## Goal

When `/tasks` produces an oversized task (one that would be > ~150 lines of diff), reject it and ask spec-kit to split.

## Steps

1. Run `/tasks`.
2. Identify the task with the largest scope.
3. Reply: "Split task N into 2–3 smaller tasks, each producing a single PR-sized diff."
4. Validate the split.

## Acceptance

No task in the final list is estimated at > 150 lines of diff (rough heuristic). Each task has a clear single-line summary.

## Reflection

Right-sized tasks reduce HITL fatigue and keep diffs reviewable. This is non-negotiable for the coding-agent pattern in Session 08.
