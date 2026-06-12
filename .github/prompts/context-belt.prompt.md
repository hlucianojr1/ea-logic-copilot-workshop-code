---
description: Generate docs/ea-context-belt.md — named context recipes for multi-million-line C++ codebases.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: docs/ea-context-belt.md
    kind: file
    overwrite: false
validation:
  - "grep -q 'Recipe:' docs/ea-context-belt.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Catalog the named context-engineering recipes EA engineers will reuse. Each recipe is named,
has a one-line problem statement, the technique, an example invocation, and the verification
step.

## Steps

Produce 10–12 recipes minimum. Required recipes:

- **Recipe: Subsystem summary anchor** — write `SUBSYSTEM.md` next to a folder; add `applyTo`-scoped
  instruction file; reference by `#file:` in chat.
- **Recipe: Cross-subsystem trace** — Plan Mode + multiple `#sym:` references.
- **Recipe: Header-only skim** — restrict context to `**/*.h` to fit token budget.
- **Recipe: Summarization-as-compression** — Copilot summarizes; commit summary; future
  prompts reference the summary, not the raw subsystem.
- **Recipe: Bug-report context bundle** — bug report + suspect file + adjacent test.
- **Recipe: Crash-dump triage bundle** — `.dmp` + `.pdb` + faulting source.
- **Recipe: Spec → plan → tasks chain** — chain of `#file:` references through spec-kit
  artifacts.
- **Recipe: MCP parity tool wrapping** — wrap an internal tool as a read-only MCP server.
- **Recipe: AGENTS.md handoff** — Coding-Agent-friendly issue framing.
- **Recipe: Squad brief** — coordinator → specialist chat-mode brief format.
- **Recipe: Off-the-rails recovery** — redirect Copilot when it drifts.
- **Recipe: Drift detection** — clang-tidy as objective drift detector.

Each recipe has the sub-sections: Problem, Technique, Example, Verification.

## Output contract

File exists; ≥10 recipes; each with all four subsections.

## Failure modes

- **"Just paste more code"**: never recommend that. Always teach a _named_ technique.
