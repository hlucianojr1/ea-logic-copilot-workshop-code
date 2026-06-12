---
description: Authoring rules for prompt files under .github/prompts/.
applyTo: ".github/prompts/**/*.prompt.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

# Prompt File Authoring Rules

Every prompt file in this repo is the **executable specification** for one slice of work.
Prompts are idempotent — re-running a prompt with the same inputs and a clean tree must
produce the same outputs.

## Required front-matter (schema)

```yaml
---
description: <one-line user-visible purpose>
mode: agent | edit | ask
model: <recommended model; e.g., "Claude Sonnet 4.6"; fall back to default if unavailable>
tools: [<tool allowlist>]
inputs:
  - name: <var>
    required: true | false
    description: <what the input is>
    default: <optional>
outputs:
  - path: <relative path or glob>
    kind: file | directory
    overwrite: true | false
validation:
  - <command or check that must pass>
last_reviewed: <YYYY-MM-DD>
reviewer: <name or role>
---
```

Validator (`npm run validate:prompts`) enforces:

- All required fields present.
- `last_reviewed` within 90 days.
- At least one `outputs[]` entry.
- At least one `validation[]` entry.
- `mode` is one of the allowed values.
- File name matches `kebab-case`, ends with `.prompt.md`.

## Required body sections (in order)

1. `## Objective` — 1–2 sentences. Plain English; no jargon.
2. `## Context references` — explicit `#file:` links to the engagement charter, relevant
   instruction files, and any prior prompt outputs this prompt depends on.
3. `## Pre-conditions` — bullet list of what must already exist or be true before running.
4. `## Steps` — numbered. Each step states **what** to do and **why**. Mark HITL checkpoints
   with `> **HITL gate:**`.
5. `## Output contract` — exact paths produced; exact front-matter requirements; exact CHANGELOG
   entry expected.
6. `## Self-validation` — commands the agent runs and must pass before declaring done.
7. `## Failure modes` — known traps + escapes. Mirrors the "off-the-rails" demo philosophy.

## Idempotency

- Re-running the prompt must not duplicate content. Use deterministic file paths.
- If `overwrite: false` and the file exists, the prompt MUST stop and report — never
  silently merge.

## Cross-prompt dependencies

If prompt A depends on prompt B's output, A's `## Pre-conditions` MUST list the file paths
B produces, and `## Context references` MUST `#file:` them. The build graph in
[`docs/build-graph.md`](../../docs/build-graph.md) reflects this.

## Forbidden

- Side effects outside declared `outputs[]`.
- Network access not declared in `tools[]`.
- "Best-effort" steps without an explicit success criterion.
- Auto-committing or auto-pushing.
- Long prose in steps; if a step is more than 5 lines, break it up.
