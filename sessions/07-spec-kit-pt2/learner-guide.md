# Session 07 — Spec-Kit Mastery, Part 2 (learner guide)

## Before you start

- Session 06 left the workspace with `specs/lockless-ring-buffer/{spec,plan,tasks}.md` plus the first task implemented.
- `specs/fixed-string/` is at skeleton state.

## Outcomes

1. Finish a multi-task `/implement` cycle with HITL on every task.
2. Drive a second feature through the full flow at higher speed.
3. Recognize and execute a stage roll-back.

## Walk-through

### Finish ring buffer

Repeat `/implement` per task. HITL each diff: read it, run ctest, approve or reject.

### `fixed-string` end-to-end

```text
/specify A fixed-capacity string in engine_demo, allocator-aware, capacity known at
construction. Must satisfy constitutional articles 1, 2, 3, 4. Provide append, view, clear.
Truncation policy on overflow: caller specifies.
/plan
/tasks
/implement
```

### Stretch — backpressure policy

```text
/specify Extend ring_buffer with backpressure_policy: drop_oldest, drop_newest,
spin_until_space (with caller-supplied timeout). Default drop_oldest.
```

Stop after `/plan`; Session 09 implements via the squad pattern.

## Try it yourself

- [Exercise 01 — execute a stage roll-back](exercises/01-stage-rollback.md)
- [Exercise 02 — finish backpressure on your own](exercises/02-backpressure.md)

## Troubleshooting

| Symptom                                      | Fix                                                   |
| -------------------------------------------- | ----------------------------------------------------- |
| Three rejected `/implement` attempts         | Roll back to `/specify`; the spec is wrong.           |
| Tests pass but a constitutional rule slipped | Reviewer chat mode catches it; re-roll the task.      |
| Pace too slow on second feature              | Trust the HITL fatigue; speed comes from familiarity. |

## Going further

- Apply the full flow to a small feature in your day-job repo. Capture the first vs. third feature timings.

## Feedback

[`retro-survey.md`](retro-survey.md).
