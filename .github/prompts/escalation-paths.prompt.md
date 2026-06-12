---
description: Generate docs/escalation-paths.md — when, how, and to whom to escalate during the engagement.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: docs/escalation-paths.md
    kind: file
    overwrite: false
validation:
  - "grep -q 'Engagement Lead' docs/escalation-paths.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Make escalation paths explicit so facilitators don't freelance under pressure.

## Steps

Sections:

1. **Severity rubric** — Sev1/2/3 with examples.
2. **Roles & owners** — Insight Engagement Lead, Insight Facilitator(s), EA Sponsor (Bert),
   EA Operations (Megan), Copilot Support, GitHub Enterprise Support, Cyber/Compliance.
3. **Triggers** — what causes a Sev1 (e.g., EA-internal IP committed, Copilot outage during
   a live session, Coding Agent producing unsafe code).
4. **Comms templates** — per role + severity.
5. **Post-incident** — write-up requirement; CHANGELOG entry; review-mode pass.

## Output contract

File exists; all roles named; templates copy-pasteable.

## Failure modes

- **Vague "contact the lead" instructions**: every escalation has a name and a channel.
