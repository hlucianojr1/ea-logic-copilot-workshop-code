---
description: Session 6 — "Spec-Kit Mastery pt 1 — Constitution → /specify → /plan". Full deliverable set.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: sessions/06-spec-kit-pt1/facilitator-script.md
    kind: file
    overwrite: false
  - path: sessions/06-spec-kit-pt1/learner-guide.md
    kind: file
    overwrite: false
  - path: sessions/06-spec-kit-pt1/slides.outline.md
    kind: file
    overwrite: false
  - path: sessions/06-spec-kit-pt1/exercises/01-author-spec.md
    kind: file
    overwrite: false
  - path: sessions/06-spec-kit-pt1/exercises/02-author-plan.md
    kind: file
    overwrite: false
  - path: sessions/06-spec-kit-pt1/retro-survey.md
    kind: file
    overwrite: false
  - path: sessions/06-spec-kit-pt1/pre-work-email.md
    kind: file
    overwrite: false
validation:
  - "npm run lint"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Teach the front half of the GitHub spec-kit lifecycle: `/constitution` (already authored
in `output/ea-cpp-games/specs/constitution.md`), `/specify` (refine the existing
`lockless-ring-buffer.md` spec), `/plan` (produce `specs/plans/lockless-ring-buffer.plan.md`).

## Context references

- `#file:../instructions/spec-kit-artifacts.instructions.md`
- `#file:../../factory-overlay/demo-patterns/spec-kit-flow.md`
- `#file:../../output/ea-cpp-games/specs/constitution.md`
- `#file:../../output/ea-cpp-games/specs/specs/lockless-ring-buffer.md`

## Session shape (60 ±3 min)

| Block          | Time        | Activities                                                                       |
| -------------- | ----------- | -------------------------------------------------------------------------------- |
| Recap + intro  | 00:00–05:00 | Recap S5; preview spec-kit as "Plan Mode at scale".                              |
| Constitution   | 05:00–15:00 | Walk the EA Engineering Constitution; explain why it precedes /plan.             |
| /specify demo  | 15:00–32:00 | Refine ring-buffer spec interactively; iterate on Copilot's suggestions; commit. |
| /plan demo     | 32:00–48:00 | Generate plan; review for constitution conformance; commit.                      |
| Hands-on       | 48:00–55:00 | Exercises (light — most is take-home).                                           |
| Survey + recap | 55:00–60:00 | Retro + tease S7.                                                                |

## Steps

Generate 7 files. Specific:

- The **constitution-first** flow is non-negotiable. The script opens the constitution
  before opening the spec.
- Live-edit `lockless-ring-buffer.md`: add an invariant Copilot missed; observe `/plan`
  reflecting it.
- HITL gate at 48:00 — review the generated plan against the constitution before declaring it
  done.

## Output contract

7 files; constitution prominent; HITL gate at 48:00; plan output committed by end of demo.

## Failure modes

- **Skipping constitution review**: defeats the entire point. Always open it first.
- **Treating /plan output as the final answer**: it's a draft. Human-edit before merging.
