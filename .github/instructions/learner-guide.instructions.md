---
description: Authoring rules for learner-guide.md follow-along documents.
applyTo: "sessions/**/learner-guide.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

# Learner Guide — Authoring Rules

The learner guide is the **self-paced companion** to the live session. A learner who missed
the live delivery should be able to reproduce every demo and complete every exercise from
this document alone.

## Required structure

1. `## Before you start` — prerequisites, env check, files to clone, plan tier required.
2. `## Outcomes` — what the learner will be able to do (mirror facilitator script).
3. `## Walk-through` — narrated reproduction of every demo, with copy-pasteable prompts.
4. `## Try it yourself` — 1–3 numbered exercises, each with:
   - Goal
   - Starter file or branch
   - Suggested prompt (in a `text` fence)
   - Expected outcome / acceptance criteria
   - Hint (collapsible via `<details>`)
5. `## Troubleshooting` — top 5 likely failures and recovery steps.
6. `## Going further` — 2–3 optional next steps, links to docs/blog posts (no dead links).
7. `## Feedback` — link to `retro-survey.md`.

## Copy-pasteability

Every prompt in the walk-through must be in a fenced ` ```text ` block of its own, on its
own line, with no shell prompt prefix. Learners must be able to triple-click + copy.

## Voice

Second person, present tense, concise. "You'll see Copilot suggest…" not "The user might
observe Copilot suggesting…".

## Forbidden

- Screenshots that include EA-confidential UI or data.
- "TODO" / "TBD" placeholders in committed learner guides — fail the review.
- Prompts that haven't been executed live in the demo workspace.
