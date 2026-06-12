---
description: Session 3 — "Bug & Defect Fixing pt 2 — Logic Bugs". Full deliverable set.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: sessions/03-logic-bugs/facilitator-script.md
    kind: file
    overwrite: false
  - path: sessions/03-logic-bugs/learner-guide.md
    kind: file
    overwrite: false
  - path: sessions/03-logic-bugs/slides.outline.md
    kind: file
    overwrite: false
  - path: sessions/03-logic-bugs/workshop-guide-advanced.md
    kind: file
    overwrite: false
  - path: sessions/03-logic-bugs/exercises/01-test-before-fix.md
    kind: file
    overwrite: false
  - path: sessions/03-logic-bugs/exercises/02-find-a-third.md
    kind: file
    overwrite: false
  - path: sessions/03-logic-bugs/retro-survey.md
    kind: file
    overwrite: false
  - path: sessions/03-logic-bugs/pre-work-email.md
    kind: file
    overwrite: false
  - path: .github/agents/logic-bug-tutor.agent.md
    kind: file
    overwrite: false
validation:
  - "npm run lint"
  - "npm run validate:snippets"
  - "npm run validate:prompts"
last_reviewed: 2026-05-04
reviewer: Insight Engagement Lead
---

## Objective

Teach how Copilot helps reason about **non-crashing logic bugs** — the kind that produce
incorrect behavior without faulting. Demos BUG-002 (accumulator drift) and BUG-006 (off-by-
one rolling window) using bug reports as context.

## Context references

- `#file:../instructions/facilitator-script.instructions.md`
- `#file:../instructions/learner-guide.instructions.md`
- `#file:../../sessions/03-logic-bugs/workshop-guide-advanced.md`
- `#file:../../output/ea-cpp-games/specs/constitution.md`
- `#file:../../output/ea-cpp-games/fixtures/bug-reports/BUG-002.md`
- `#file:../../output/ea-cpp-games/fixtures/bug-reports/BUG-006.md`

## Pre-conditions

- Bug reports (Tier 2 fixture prompt) committed.
- engine_demo builds and tests pass.

## Session shape (60 ±3 min)

| Block        | Time        | Activities                                                                                                                  |
| ------------ | ----------- | --------------------------------------------------------------------------------------------------------------------------- |
| Opening      | 00:00–05:00 | Recap S2; preview that not all bugs crash (drift, off-by-one).                                                              |
| Demo BUG-002 | 05:00–30:00 | Ask-tab observe → reproduce (re-enable DISABLED test) → bisect; Edit tab for the float→double fix only after HITL approval. |
| Demo BUG-006 | 30:00–50:00 | Ask-tab predict-then-reconcile to expose the off-by-one; Edit tab for the wrap-order fix only after HITL approval.          |
| Q&A          | 50:00–57:00 | When NOT to trust Copilot for logic bugs; drift vs off-by-one repro shapes.                                                 |
| Retro        | 57:00–60:00 | Retro micro-survey.                                                                                                         |

## Steps

Generate the nine files following the same conventions as Session 1/2. Specific notes:

- Use the **Ask / Edit / Agent** tab vocabulary throughout — there is no "Plan Mode".
- Demo flow per bug is **observe → reproduce → fix → verify**: diagnose in the Ask tab and
  re-enable the seeded `DISABLED_` test _before_ any edit; switch to the Edit tab for the fix
  only after the user approves the diagnosis.

  > **HITL gate:** never edit source before the learner has seen the seeded test fail.

- The Ask-tab diagnosis prompt attaches the bug report, the suspect header + source, and
  `specs/constitution.md`, then asks Copilot to name the violated article and cite lines.
- BUG-002 (numerical drift, Article 5) is demoed first; BUG-006 (rolling-window off-by-one,
  Articles 5–6) second. Both fixes are paired with the seeded regression test.
- `learner-guide.md` must be self-contained: it includes environment setup, the green-baseline
  build/test commands, and a "Start the self-guided tutor" path that selects the
  `logic-bug-tutor` agent. Follow `learner-guide.instructions.md`.
- Exercise 01 (`01-test-before-fix.md`) re-enables BUG-002's `DISABLED_` test and has the
  learner articulate why `double` satisfies Article 5 before fixing. Exercise 02
  (`02-find-a-third.md`) has the learner surface candidate defects in the constraint solver,
  identify BUG-004, and dismiss the FP-002 false positive.
- `workshop-guide-advanced.md` is the full advanced set (BUG-002, 004, 006, 007, 008, 009, 010) and walks the learner through building their own `logic-bug-planner.agent.md`.
- `.github/agents/logic-bug-tutor.agent.md` is the pre-built tutor that paces the session one
  bug at a time with HITL gates; keep its workflow aligned with this script.

## Output contract

9 files generated (facilitator script, learner guide, slides outline, advanced guide, two
exercises, retro survey, pre-work email, and the `logic-bug-tutor` agent). Facilitator script
runs 60 ±3 min. Both demo bugs (BUG-002, BUG-006) are referenced with correct
`fixtures/bug-reports/` paths. The learner guide is self-contained and self-guided. The
advanced guide and tutor cover the full set (BUG-002, 004, 006, 007, 008, 009, 010).

> **Note:** `logic-bug-workshop-training.docx` is exported from `workshop-guide-advanced.md`
> out-of-band (a manual Word/Pandoc export); this prompt does not generate the binary.

## Failure modes

- **Asking Copilot to "fix this" before diagnosing**: the whole pedagogy of S3 is "diagnose
  first". Refuse to skip the Ask-tab diagnosis and the seeded failing test.
- **Tests that pass without exercising the bug**: every fix is paired with a `DISABLED_`
  regression test that failed before the fix and passes after.
- **Stale fixture paths**: bug reports live under `fixtures/bug-reports/` (hyphen) as
  `BUG-002.md` / `BUG-006.md` — not `bug_reports/` and not the long descriptive filenames.
