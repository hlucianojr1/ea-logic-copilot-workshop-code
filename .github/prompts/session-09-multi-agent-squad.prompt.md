---
description: Session 9 — "Multi-Agent pt 2 — Squad Pattern". Full deliverable set.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: sessions/09-multi-agent-squad/facilitator-script.md
    kind: file
    overwrite: false
  - path: sessions/09-multi-agent-squad/learner-guide.md
    kind: file
    overwrite: false
  - path: sessions/09-multi-agent-squad/slides.outline.md
    kind: file
    overwrite: false
  - path: sessions/09-multi-agent-squad/exercises/01-coordinator-brief.md
    kind: file
    overwrite: false
  - path: sessions/09-multi-agent-squad/exercises/02-end-to-end-feature.md
    kind: file
    overwrite: false
  - path: sessions/09-multi-agent-squad/retro-survey.md
    kind: file
    overwrite: false
  - path: sessions/09-multi-agent-squad/pre-work-email.md
    kind: file
    overwrite: false
validation:
  - "npm run lint"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Teach the **multi-agent squad pattern**: a `squad-coordinator` chat mode dispatches briefs
to specialist chat modes (`cpp-architect`, `cpp-developer`, `cpp-tester`) to deliver a
non-trivial feature end-to-end. Frame it as an **architectural pattern over real Copilot
primitives**, not a magical "AI orchestration" product. The user message ALWAYS overrides.

## Context references

- `#file:../../factory-overlay/demo-patterns/multi-agent-squad.md`
- `#file:../chatmodes/squad-coordinator.chatmode.md`
- `#file:../chatmodes/cpp-architect.chatmode.md`
- `#file:../chatmodes/cpp-developer.chatmode.md`
- `#file:../chatmodes/cpp-tester.chatmode.md`

## Session shape (60 ±3 min)

| Block           | Time        | Activities                                                                                                                   |
| --------------- | ----------- | ---------------------------------------------------------------------------------------------------------------------------- |
| Recap + concept | 00:00–10:00 | Frame as pattern, not product; show the 4 chat modes.                                                                        |
| Demo: brief     | 10:00–22:00 | Coordinator receives task: "Add `entity_view` iterator with bounds-checked & deterministic order"; produces architect brief. |
| Demo: architect | 22:00–32:00 | Architect produces `01-architecture.md` (text only).                                                                         |
| Demo: developer | 32:00–42:00 | Developer implements per architecture; commits.                                                                              |
| Demo: tester    | 42:00–52:00 | Tester writes tests; verifies determinism; commits.                                                                          |
| Wrap + survey   | 52:00–60:00 | Series-end retro (uses the end-of-series form from `survey-template.instructions.md`).                                       |

## Steps

Generate 7 files. Specific:

- The coordinator NEVER writes code; it only writes briefs and updates a decisions log.
- Each specialist responds with a single artifact (architecture doc, code, tests).
- HITL gate between each handoff.
- The "Hand-off table" in `AGENTS.md` is referenced explicitly during the session.
- Exercise 02 is the take-home: deliver a feature using the squad pattern in their own repo.
- Survey is the **series-end** form (10–12 questions, Likert + free text) — distinct from
  per-session retros.

## Output contract

7 files; squad pattern grounded in real chat modes; series-end survey present and matches
`survey-template.instructions.md`.

## Failure modes

- **Selling "multi-agent" as autonomous orchestration**: it isn't. Each specialist is a chat
  mode the human invokes. Be explicit.
- **Coordinator writing code**: hard rule. If it does, it's a misuse.
- **Skipping the series-end survey**: this is the final data we hand to Megan + Bert. Do
  not skip.
