---
description: Session 4 — "Bug & Defect Fixing pt 3 — Proactive Hunting". Full deliverable set.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: sessions/04-proactive-hunting/facilitator-script.md
    kind: file
    overwrite: false
  - path: sessions/04-proactive-hunting/learner-guide.md
    kind: file
    overwrite: false
  - path: sessions/04-proactive-hunting/slides.outline.md
    kind: file
    overwrite: false
  - path: sessions/04-proactive-hunting/exercises/01-cwe-sweep.md
    kind: file
    overwrite: false
  - path: sessions/04-proactive-hunting/exercises/02-false-positive-triage.md
    kind: file
    overwrite: false
  - path: sessions/04-proactive-hunting/retro-survey.md
    kind: file
    overwrite: false
  - path: sessions/04-proactive-hunting/pre-work-email.md
    kind: file
    overwrite: false
validation:
  - "npm run lint"
  - "npm run validate:snippets"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Teach **proactive issue hunting** with Copilot — not waiting for a bug report, but sweeping
the codebase for latent issues. Covers logic and security flavors, anchored to BUG-003,
BUG-004, BUG-005 in engine_demo. Heavy emphasis on **false-positive triage** because this
is where Copilot misuse hurts most.

## Context references

- `#file:../instructions/facilitator-script.instructions.md`
- `#file:../../factory-overlay/demo-patterns/proactive-issue-hunt.md`
- `#file:../../output/ea-cpp-games/.github/prompts/security-scan-cwe.prompt.md`

## Pre-conditions

- engine_demo builds; security-scan-cwe prompt installed in the demo workspace's `.github/prompts/`.

## Session shape (60 ±3 min)

| Block          | Time        | Activities                                                                                                                                         |
| -------------- | ----------- | -------------------------------------------------------------------------------------------------------------------------------------------------- |
| Recap + intro  | 00:00–05:00 | Recap; introduce "proactive vs reactive".                                                                                                          |
| Concept        | 05:00–12:00 | CWE primer (787, 416, 476); `security-scan-cwe` prompt; logic-sweep prompt.                                                                        |
| Demo: security | 12:00–28:00 | Run `security-scan-cwe.prompt.md` against engine_demo; surface BUG-003 (UAF) and BUG-005 (RNG downcast); rank findings; triage one false positive. |
| Demo: logic    | 28:00–40:00 | Run logic-sweep against `physics/constraint_solver.cpp`; surface BUG-004 (non-deterministic order).                                                |
| Hands-on       | 40:00–52:00 | Exercises 01 + 02.                                                                                                                                 |
| Q&A            | 52:00–58:00 | False-positive cost vs. true-positive value.                                                                                                       |
| Survey         | 58:00–60:00 | Retro.                                                                                                                                             |

## Steps

Same conventions as previous sessions. Specific:

- The **false-positive triage rubric** (3-step) is taught explicitly: reproduce, analyze
  data flow, decide. Document it in the learner guide.
- Exercise 02 is purely about triage — given 5 Copilot findings (only 2 of which are real),
  learners must classify each.
- Pre-seed exactly 2 false positives in the demo run by including patterns Copilot tends to
  flag wrongly (e.g., `eastl::span` indexing that _looks_ like OOB but isn't).

## Output contract

7 files; both flavors covered; triage rubric explicit; exercise 02 has known correct
answers documented in a separate `exercises/02-false-positive-triage.answers.md` (NOT
shipped to learners — for facilitator only; commit but link only from facilitator script).

## Failure modes

- **Treating every Copilot finding as a bug**: catastrophic failure mode for EA. The session
  exists to inoculate against this.
- **Cherry-picking only true positives in the demo**: include at least one realistic FP and
  walk through rejecting it.
