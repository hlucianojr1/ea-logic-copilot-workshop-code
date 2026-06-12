---
description: Generate Session 1 — "Code Comprehension at Scale" — facilitator script, learner guide, slides outline, exercises, retro survey, pre-work email.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: sessions/01-comprehension-at-scale/facilitator-script.md
    kind: file
    overwrite: false
  - path: sessions/01-comprehension-at-scale/learner-guide.md
    kind: file
    overwrite: false
  - path: sessions/01-comprehension-at-scale/slides.outline.md
    kind: file
    overwrite: false
  - path: sessions/01-comprehension-at-scale/exercises/01-find-the-call-graph.md
    kind: file
    overwrite: false
  - path: sessions/01-comprehension-at-scale/exercises/02-summarize-subsystem.md
    kind: file
    overwrite: false
  - path: sessions/01-comprehension-at-scale/retro-survey.md
    kind: file
    overwrite: false
  - path: sessions/01-comprehension-at-scale/pre-work-email.md
    kind: file
    overwrite: false
validation:
  - "npm run lint"
  - "npm run validate:snippets"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Generate the full Session 1 deliverable set. The session teaches **code comprehension at
scale** in a multi-million-line C++ codebase using @workspace, `#file:`, `#sym:`, and the
custom MCP server demo.

## Context references

- `#file:../instructions/facilitator-script.instructions.md`
- `#file:../instructions/learner-guide.instructions.md`
- `#file:../instructions/survey-template.instructions.md`
- `#file:../../factory-overlay/demo-patterns/crash-dump-triage.md` (precedent shape)
- `#file:../../docs/ea-context-belt.md`
- `#file:../../output/ea-cpp-games/include/engine_demo` (anchor files)

## Pre-conditions

- Demo workspace scaffolded and engine module implemented.
- Engagement charter, ea-context-belt.md, and pre-work email exist (Tier 4).

## Session shape (60 ±3 min)

| Block            | Time        | Activities                                                                                                                                    |
| ---------------- | ----------- | --------------------------------------------------------------------------------------------------------------------------------------------- |
| Welcome + recap  | 00:00–05:00 | Frame the series; recap any prior context.                                                                                                    |
| Concept primer   | 05:00–15:00 | "Context belt" patterns (Plan vs. Edit Mode, @workspace, `#file:`, `#sym:`).                                                                  |
| Demo             | 15:00–35:00 | Walk EASTL public repo + engine_demo: ask Copilot to summarize the allocator subsystem; produce a Mermaid call-graph; verify by spot-reading. |
| Hands-on         | 35:00–50:00 | Exercises 01 + 02; learners apply the techniques to engine_demo.                                                                              |
| HITL pause + Q&A | 50:00–58:00 | Discuss false positives; how to verify Copilot's summary.                                                                                     |
| Survey           | 58:00–60:00 | 5-question retro.                                                                                                                             |

## Steps

1. **`facilitator-script.md`** — follow `facilitator-script.instructions.md`. Time markers
   per the table above. Include verbatim prompt strings the facilitator pastes (in `text`
   fences). Include `Watch for:` callouts on the most common stumbles (Copilot inventing a
   class that doesn't exist, summary missing the allocator). Include the `HITL gate:` at
   50:00.
2. **`learner-guide.md`** — follow `learner-guide.instructions.md`. Sections: What you'll
   learn, Prereqs, Setup (clone repo, open in VS Code, install extensions, set MCP PAT),
   Walkthrough, Exercises, Wrap-up, Going further.
3. **`slides.outline.md`** — 12-slide outline (titles + bullet points only); maps 1:1 to the
   facilitator script blocks.
4. **`exercises/01-find-the-call-graph.md`** — given `engine_demo`, produce a call graph for
   `world::create()` using Plan Mode + `#sym:` references; verify by reading the source.
5. **`exercises/02-summarize-subsystem.md`** — produce a 1-page summary of the ECS subsystem
   suitable for committing as `include/engine_demo/ecs/SUBSYSTEM.md`. Critical detail: the
   summary must include "Known limitations" — encourage learners to admit gaps rather than
   hallucinate.
6. **`retro-survey.md`** — the 5 canonical questions from
   `survey-template.instructions.md`, plus one Session-1-specific question:
   "Did the context-belt patterns map to your real codebase? Why / why not?"
7. **`pre-work-email.md`** — one-page email: prereqs, Copilot plan check, repo clone,
   extension install, the 5-minute warm-up exercise, link to `docs/ea-context-belt.md`.

## Output contract

All seven files exist; facilitator script totals 60 ±3 minutes; all `cpp` snippets compile.

## Self-validation

```bash
npm run lint
npm run validate:snippets
grep -E "^### \[?[0-9]{2}:[0-9]{2}-[0-9]{2}:[0-9]{2}" sessions/01-comprehension-at-scale/facilitator-script.md
```

## Failure modes

- **Treating @workspace as magic**: the script must show its limits and how to compose
  context manually.
- **Skipping the "verify" step**: every Copilot output in the demo is verified by reading
  source. Otherwise we teach hallucination.
