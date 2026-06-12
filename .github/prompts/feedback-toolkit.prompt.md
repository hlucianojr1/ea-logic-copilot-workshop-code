---
description: Generate docs/feedback-toolkit.md — central hub for retro questions, scoring rubrics, and reporting templates.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: docs/feedback-toolkit.md
    kind: file
    overwrite: false
validation:
  - "grep -q 'series-level' docs/feedback-toolkit.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Centralize every survey, scoring rubric, and reporting template used across the engagement.
The per-session retro forms link back here; the series-level report is generated from data
collected per these templates.

## Steps

Sections:

1. **Per-session retro** — 5 canonical questions (matches `survey-template.instructions.md`),
   distribution mechanism (Forms link), 60-second time budget rationale.
2. **Mid-series retro (after Session 4 or 5)** — Likert + free-text; 5 questions; targets
   pacing and difficulty.
3. **Series-end retro** — 10–12 questions; covers each track (A–E); explicit "would you
   adopt this in your team?" + "what blocked adoption?" — these are Bert's questions.
4. **Scoring rubrics** — 1–5 Likert per question; aggregation rules; how to handle missing
   responses.
5. **Reporting templates** — per-session 1-pager to Megan; weekly cumulative to Bert; final
   series report.
6. **Privacy + handling** — no PII captured beyond opt-in name; raw data retained 90 days
   then aggregated and deleted.

## Output contract

File exists; all five canonical questions verbatim; templates copy-pasteable.

## Failure modes

- **Drifting from `survey-template.instructions.md`**: this file is the source of truth for
  the canonical questions. Any change happens there first.
