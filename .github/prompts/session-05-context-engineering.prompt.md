---
description: Session 5 — "Context Engineering at Scale". Full deliverable set.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: sessions/05-context-engineering/facilitator-script.md
    kind: file
    overwrite: false
  - path: sessions/05-context-engineering/learner-guide.md
    kind: file
    overwrite: false
  - path: sessions/05-context-engineering/slides.outline.md
    kind: file
    overwrite: false
  - path: sessions/05-context-engineering/exercises/01-write-instructions-md.md
    kind: file
    overwrite: false
  - path: sessions/05-context-engineering/exercises/02-mcp-parity-demo.md
    kind: file
    overwrite: false
  - path: sessions/05-context-engineering/retro-survey.md
    kind: file
    overwrite: false
  - path: sessions/05-context-engineering/pre-work-email.md
    kind: file
    overwrite: false
validation:
  - "npm run lint"
  - "npm run validate:snippets"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Teach EA engineers how to **engineer context** for Copilot in a multi-million-line codebase:
the precedence chain (`copilot-instructions.md` → scoped `*.instructions.md` → per-prompt →
user message), MCP servers (parity demo), summarization-as-compression, and named context
recipes (the "context belt").

## Context references

- `#file:../instructions/facilitator-script.instructions.md`
- `#file:../instructions/prompt-authoring.instructions.md`
- `#file:../instructions/chat-mode-authoring.instructions.md`
- `#file:../../docs/ea-context-belt.md`
- `#file:../../docs/mcp-parity-strategy.md`
- `#file:../../.vscode/mcp.json`

## Session shape (60 ±3 min)

| Block         | Time        | Activities                                                                                                |
| ------------- | ----------- | --------------------------------------------------------------------------------------------------------- |
| Recap + intro | 00:00–05:00 | Recap; tease "stop pasting code".                                                                         |
| Concept       | 05:00–18:00 | The 4-tier precedence chain; `applyTo` patterns; SUBSYSTEM.md anchors; MCP at a glance.                   |
| Demo: instr.  | 18:00–32:00 | Author an `eastl.instructions.md` LIVE; observe Copilot's behavior shift on the same prompt before/after. |
| Demo: MCP     | 32:00–45:00 | Configure mcp.json; demo filesystem MCP; sketch an internal-tool wrapper.                                 |
| Hands-on      | 45:00–52:00 | Exercises 01 + 02 (light pass — most work is post-session).                                               |
| Q&A           | 52:00–58:00 | When custom instructions backfire.                                                                        |
| Survey        | 58:00–60:00 | Retro.                                                                                                    |

## Steps

Generate the 7 files. Specific notes:

- The "before/after" demo is the centerpiece — show Copilot generating `std::vector` first,
  then add the instruction file, then show it generating EASTL.
- The MCP demo uses the filesystem server scoped to `output/ea-cpp-games`.
- Exercise 01 is "Author a `cpp-snippets.instructions.md`-equivalent for YOUR repo" — this
  is a **take-home asset** for EA engineers.
- Exercise 02 is "Wire one MCP server" — minimal acceptance: filesystem server pointing at
  a learner-chosen folder.

## Output contract

7 files; before/after demo concrete; MCP parity strategy referenced.

## Failure modes

- **Treating MCP as a wrapper for arbitrary internal tooling without governance**: the
  parity strategy must include the read-only-by-default + audit-log boundaries.
- **Overpromising "infinite context"**: explicitly call out token budgets and the
  summarization-as-compression pattern.
