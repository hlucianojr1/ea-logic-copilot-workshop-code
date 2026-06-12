---
description: Generate docs/build-graph.md — the DAG of prompts → outputs, used to choose run order.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: docs/build-graph.md
    kind: file
    overwrite: false
validation:
  - "grep -q 'mermaid' docs/build-graph.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Produce a Mermaid DAG showing prompt dependencies and a phased run order. This is how a new
contributor (or Coding Agent) figures out what to run when.

## Steps

Produce these sections:

1. **Phases** — table:
   - Phase 0: `docs-sources` → `engagement-charter`.
   - Phase 1: `bootstrap-repo` → `bootstrap-copilot-customization` → `bootstrap-ci` → `bootstrap-mcp`.
   - Phase 2: factory-overlay (5 prompts).
   - Phase 3: demo-workspace (8 prompts).
   - Phase 4: tier-4 cross-cutting (delivery-runbook, feedback-toolkit, context-belt).
   - Phase 5: sessions 01–09 (parallelizable after demo workspace).
   - Phase 6: review prompts (Tier 5).
2. **Mermaid DAG** — `flowchart TD` with edges showing dependencies; clusters per phase.
3. **Parallelism notes** — which prompts can run in parallel within a phase.
4. **Re-run safety** — confirms every prompt is idempotent (`overwrite: false` everywhere
   except `demo-workspace-instructions-prompts-chatmodes` and `demo-workspace-agents-md`,
   which overwrite stubs by design).

## Output contract

File exists; mermaid block validates; all prompts referenced.

## Failure modes

- **Phase numbering drift**: any future prompt added must update this graph.
