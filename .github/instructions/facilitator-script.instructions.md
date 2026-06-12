---
description: Authoring rules for facilitator scripts under sessions/{N}-*/facilitator-script.md.
applyTo: "sessions/**/facilitator-script.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

# Facilitator Script — Authoring Rules

A facilitator script is the **minute-by-minute teleprompter** for a 60-minute live session.
Anyone on the Insight delivery team should be able to deliver any session by reading the
script verbatim, without prior context beyond what is referenced inline.

## Required structure

Every facilitator script MUST have these top-level H2 sections, in this exact order:

1. `## Session at a glance` — duration, level, prerequisites, required Copilot plan,
   demo workspace state required, learner outcomes.
2. `## Pre-session checklist (T-15 min)` — environment checks, files to open, prompts to
   pre-load, recording/transcripts toggles.
3. `## Opening (0:00 – 0:05)` — hook, agenda, "what you'll be able to do by the end".
4. `## Block 1: <name> (0:05 – 0:NN)` — first content block.
5. `## Block 2: ...` — additional content blocks as needed; total teaching ≤ 45 min.
6. `## Q&A (0:45 – 0:55)` — anticipated questions + scripted answers.
7. `## Retro micro-survey (0:55 – 1:00)` — link to the survey, what to read aloud, how to
   capture verbal feedback.
8. `## Stretch goals (skip if behind)` — clearly marked optional content.
9. `## Recovery script (if a demo fails)` — exact prompts/actions to recover gracefully.
10. `## Post-session checklist (T+15 min)` — recording upload, retro export, follow-up
    actions.

## Time markers

Every block heading MUST include a `(MM:SS – MM:SS)` time range. Total time MUST be 60 min ±
3 min. The dry-run validator checks this.

## Callouts

Use these literal Markdown call-outs to keep formatting consistent:

```markdown
> **Facilitator note:** <inside-baseball reminder; not read aloud>

> **Say:** "<verbatim line to speak>"

> **Do:** <action: open file, run prompt, click button>

> **Watch for:** <common pitfall and how to recover>

> **HITL gate:** <explicit human-in-the-loop checkpoint with what to confirm>
```

## Demo prompts

Every live demo prompt the facilitator types into Copilot Chat MUST be presented in a fenced
block tagged ` ```text ` (not `cpp` — the validator would try to compile it):

```text
#file:engine_demo/src/sim/MonteCarloKernel.cpp
Explain the physics model implemented here. Identify any precision issues, missing edge
cases, or opportunities to add [[nodiscard]] that the current code misses.
```

Adjacent prose must explain what model is recommended (Section 4 of `cpp-snippets`) and what
the expected response shape is, so a facilitator knows when the demo has succeeded.

## Cross-references

- Always link to the corresponding `learner-guide.md`, `slides.outline.md`, and
  `retro-survey.md` for the same session at the top of the script.
- Reference any required demo workspace files using **relative** links from the script's
  location.

## Forbidden

- Improv prompts. If a prompt is not in the script, it does not get demoed.
- Vague guidance like "explain to learners how X works". State the words to say.
- Time blocks without `(MM:SS – MM:SS)` headers.
- C++ snippets in `cpp` fences that have not been validated by `npm run validate:snippets`.
