---
description: Authoring rules for chat modes under .github/chatmodes/.
applyTo: ".github/chatmodes/**/*.chatmode.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

# Chat Mode Authoring Rules

A chat mode is a constrained Copilot Chat persona with a specific role, tool allowlist, and
output contract. This repo defines seven modes; do not invent new ones without a PR that
updates this file and `docs/build-graph.md`.

## Required front-matter

```yaml
---
description: <one-line user-visible purpose>
tools: [<allowlist; see below>]
model: <recommended model tier; e.g., "Claude Sonnet 4.6">
---
```

The `tools` array is the **only** list of tools the mode is permitted to use. The chat
client enforces this; do not rely on the body text alone to constrain behavior.

## Body structure

1. `## Role` — one paragraph: who the mode is, who it isn't.
2. `## When to use` — concrete triggers (e.g., "use this when starting a new session
   bundle"). Reference at least one prompt or instruction file.
3. `## Allowed actions` — bullet list, mirroring the front-matter `tools`.
4. `## Forbidden actions` — bullet list of explicit denials (e.g., "never run `git push`").
5. `## Hand-off` — the exact files this mode produces and which mode consumes them next.
   Mirror the table in [`AGENTS.md`](../../AGENTS.md).
6. `## Self-test` — what the mode must verify before declaring done.

## Tool allowlist matrix

| Mode                | Read | Edit | Terminal       | Web | MCP github | MCP filesystem |
| ------------------- | ---- | ---- | -------------- | --- | ---------- | -------------- |
| `planner`           | ✅   | ❌   | ❌             | ✅  | ❌         | ✅ (read)      |
| `builder`           | ✅   | ✅   | ✅ (HITL)      | ✅  | ✅         | ✅             |
| `reviewer`          | ✅   | ❌   | ✅ (read-only) | ✅  | ❌         | ✅ (read)      |
| `squad-coordinator` | ✅   | ❌   | ❌             | ❌  | ❌         | ✅ (read)      |
| `cpp-architect`     | ✅   | ❌   | ❌             | ❌  | ❌         | ✅ (read)      |
| `cpp-developer`     | ✅   | ✅   | ✅ (HITL)      | ❌  | ❌         | ✅             |
| `cpp-tester`        | ✅   | ✅   | ✅ (HITL)      | ❌  | ❌         | ✅             |

`HITL` = each `runCommands` invocation requires a human approval click. Never bypass.

## Forbidden

- Granting `runCommands` to `planner`, `reviewer`, `squad-coordinator`, or `cpp-architect`.
- Allowing any mode to write outside its hand-off scope.
- Inlining secrets in the body. Reference `.env.example` and `${input:...}` only.
