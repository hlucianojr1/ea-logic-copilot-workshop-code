---
description: Generate docs/delivery-runbook.md — the operations checklist a facilitator runs the day before, day of, and day after each session.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: docs/delivery-runbook.md
    kind: file
    overwrite: false
validation:
  - "grep -q 'Day-before' docs/delivery-runbook.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Produce the **delivery runbook** facilitators follow for every session: what to verify, what
to capture, what to send.

## Steps

Sections:

1. **Day-before checklist** — repo green, fixtures freshly captured (Sessions 2/4),
   Coding Agent test issue filed (Session 8), MCP PAT rotated, sample PR pre-merged for S8 fallback.
2. **30-min-before checklist** — VS Code restart, extension status check, mcp.json validates,
   chat history cleared, screen sharing rehearsed, captions on, recording confirmed.
3. **During session** — what to capture (chat transcripts → `output/transcripts/SNN.md`),
   when to pause (HITL gates per session script), when to declare a Plan-B (Coding Agent
   timeout > 5min, Copilot down, MCP server failing).
4. **Immediate post-session** — push retro responses to feedback toolkit, capture qualitative
   moments, file content-bug issues for any defect.
5. **End-of-week** — summary email to Megan (per-session) + cumulative metrics to Bert.
6. **End-of-series** — series-level report; demo workspace handoff; MCP parity demo handoff.
7. **Plan-B catalog** — explicit mitigations for the top 6 likely failures, each with the
   verbatim words to say.

## Output contract

File exists; each section actionable; Plan-Bs explicit.

## Failure modes

- **Vague checklists**: every item has a verifiable yes/no.
