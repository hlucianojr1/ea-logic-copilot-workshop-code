---
description: Session 7 — "Spec-Kit Mastery pt 2 — /tasks → /implement". Full deliverable set.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: sessions/07-spec-kit-pt2/facilitator-script.md
    kind: file
    overwrite: false
  - path: sessions/07-spec-kit-pt2/learner-guide.md
    kind: file
    overwrite: false
  - path: sessions/07-spec-kit-pt2/slides.outline.md
    kind: file
    overwrite: false
  - path: sessions/07-spec-kit-pt2/exercises/01-tasks-and-implement.md
    kind: file
    overwrite: false
  - path: sessions/07-spec-kit-pt2/exercises/02-fixed-string-end-to-end.md
    kind: file
    overwrite: false
  - path: sessions/07-spec-kit-pt2/retro-survey.md
    kind: file
    overwrite: false
  - path: sessions/07-spec-kit-pt2/pre-work-email.md
    kind: file
    overwrite: false
validation:
  - "npm run lint"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Teach the back half of spec-kit: `/tasks` (decompose plan into discrete work items) and
`/implement` (execute one task at a time with HITL between tasks). Live-implement the
**lockless ring-buffer** end-to-end, producing `include/engine_demo/util/lockless_ring_buffer.h`,
`src/util/...` (if any), and `tests/util/lockless_ring_buffer_test.cpp`. Tests pass live.

## Context references

- `#file:../instructions/spec-kit-artifacts.instructions.md`
- `#file:../../output/ea-cpp-games/specs/specs/lockless-ring-buffer.md`
- `#file:../../sessions/06-spec-kit-pt1/facilitator-script.md`

## Pre-conditions

- Session 6 completed; the plan exists.
- engine_demo builds.

## Session shape (60 ±3 min)

| Block             | Time        | Activities                                                     |
| ----------------- | ----------- | -------------------------------------------------------------- |
| Recap + setup     | 00:00–05:00 | Recap S6; load the plan.                                       |
| /tasks demo       | 05:00–18:00 | Generate task list; reorder; commit.                           |
| /implement task 1 | 18:00–32:00 | Implement first task (header + skeleton); HITL review; commit. |
| /implement task 2 | 32:00–45:00 | Implement push/pop logic; tests; HITL review; commit.          |
| Hands-on          | 45:00–55:00 | Learners run /implement on their own machine.                  |
| Q&A + survey      | 55:00–60:00 | Retro.                                                         |

## Steps

Generate 7 files. Specific:

- The HITL gate **between every task** is the most important pedagogical point.
- Tests must pass live; if they don't, the facilitator pauses and walks the failure with
  Copilot in Plan Mode (this is itself a teaching moment).
- Exercise 02 is end-to-end on the simpler `fixed-string` spec — take-home deliverable.

## Output contract

7 files; HITL gate explicit between tasks; ring-buffer header + test land in repo by end
of demo; both pass.

## Failure modes

- **Implementing the whole plan in one shot**: defeats the lifecycle's purpose. Always
  task-by-task.
- **Skipping tests**: every `/implement` task ships with the test it claims to satisfy.
