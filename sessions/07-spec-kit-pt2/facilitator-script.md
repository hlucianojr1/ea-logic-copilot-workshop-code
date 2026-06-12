# Session 07 — Spec-Kit Mastery, Part 2 (facilitator script)

> **Cross-references:** [`learner-guide.md`](learner-guide.md) · [`slides.outline.md`](slides.outline.md) · [`retro-survey.md`](retro-survey.md) · [exercises](exercises/)

## Session at a glance

- **Duration:** 60 min · **Level:** advanced · **Plan tier:** Business
- **Demo state:** Session 06 completed task 1 of `lockless-ring-buffer`. Today we finish that feature, then drive a second feature (`fixed-string`) end-to-end at speed. Stretch: backpressure policy.
- **Outcomes:**
  1. Finish `/implement` for the ring buffer with HITL gates.
  2. Drive a second feature (`fixed-string`) through the full flow inside 25 minutes.
  3. Recognize when to **roll back** a stage.

## Pre-session checklist (T-15 min)

> **Do:** confirm `specs/lockless-ring-buffer/{spec,plan,tasks}.md` exist and the first task's diff is committed.
> **Do:** confirm `specs/fixed-string/` is in skeleton state (README only).

## Opening (0:00 – 0:05)

> **Say:** "Last week we drove one task. Today we drive everything else, plus a second feature, plus a stretch backpressure policy. The reps build muscle."

## Block 1: Finish ring-buffer `/implement` (0:05 – 0:25)

> **Do:** for each remaining task:

```text
/implement
```

> **HITL gate:** every task — read the diff, run ctest, approve or reject. Demonstrate at least one rejection (force a regression by introducing a `std::vector` and let the reviewer chat mode flag it).

> **Watch for:** participants getting fatigued. Acknowledge the friction. The friction is the feature.

## Block 2: Drive `fixed-string` end-to-end (0:25 – 0:50)

> **Say:** "Repeat the flow at speed. We've done it once; we know the moves."

> **Do:**

```text
/specify A fixed-capacity string in engine_demo, allocator-aware, capacity known at
construction. Must satisfy constitutional articles 1, 2, 3, 4. Provide append, view (as
eastl::string_view), clear. Truncation policy on overflow: caller specifies (truncate or
fail).
```

> **HITL gate:** review spec.

```text
/plan
/tasks
/implement
```

> **Watch for:** much faster cadence than ring buffer because participants now know what to look for.

## Block 3: Stretch — backpressure policy (0:50 – 0:55)

> **Say:** "If we have time: extend the ring buffer with a backpressure policy enum. This previews Session 09's squad-pattern demo target."

> **Do:**

```text
/specify Extend ring_buffer with a backpressure_policy enum: drop_oldest, drop_newest,
spin_until_space (with caller-supplied timeout). Default drop_oldest. The policy must not
violate constitutional article 5.
```

If time allows, do the `/plan` and stop there. Implementation lands in Session 09.

## Q&A (0:55 – 0:58)

- **Q: "What if a task is rejected three times in a row?"** → "Stage roll-back. Go back to `/specify`. The spec is wrong, not the implementation."

## Retro micro-survey (0:58 – 1:00)

> **Do:** post [`retro-survey.md`](retro-survey.md).

## Stretch goals

- Author a custom GoogleTest macro suite for the new types.

## Recovery script

If `/implement` produces a diff with a `std::` container: do not fix in place. Reject. Re-prompt with explicit Article 3 citation. Demonstrate the discipline.

## Post-session checklist

- Confirm both features merged and tests green.
- The backpressure spec stays uncommitted-implementation; Session 09 picks it up.
