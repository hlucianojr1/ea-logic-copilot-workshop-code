---
description: Generate .vscode/mcp.json with filesystem + GitHub MCP servers for the parity demo.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: .vscode/mcp.json
    kind: file
    overwrite: false
  - path: docs/mcp-parity-strategy.md
    kind: file
    overwrite: false
validation:
  - 'node -e "JSON.parse(require(''fs'').readFileSync(''.vscode/mcp.json''))"'
  - "npm run lint"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Stand up the **MCP parity demo** that Sessions 1, 4, and 5 rely on, so a facilitator can show
EA how an internal context tool would integrate with Copilot without requiring access to
EA-internal infrastructure.

## Context references

- `#file:../../docs/engagement-charter.md` ("Internal tooling integration scope")
- `#file:../../docs/sources/bert-email-2026-04-28.md` (mention of EA internal context tooling)

## Pre-conditions

- Repo bootstrapped.
- The user accepts that this is a parity demo, not a wrap of EA internals.

## Steps

1. **`.vscode/mcp.json`** with two servers:
   - `filesystem` — `@modelcontextprotocol/server-filesystem` scoped to `output/ea-cpp-games`,
     `sessions`, `docs`. Read-only enforcement happens at the MCP layer.
   - `github` — `@modelcontextprotocol/server-github` with PAT prompted via `${input:github_pat}`.
   - An `inputs[]` block defines `github_pat` as `promptString` with `password: true`.
   - JSONC comments explaining the security posture and that no other servers are added by default.
2. **`docs/mcp-parity-strategy.md`** — short doc explaining:
   - What an EA-internal context tool would do (architectural sketch only — no specifics).
   - How to wrap such a tool as an MCP server (the well-known stdio + tools pattern).
   - Recommended boundaries: read-only by default, separate audit log, no secrets in tool
     responses, time-boxed token cache.
   - Three concrete example tool-method names a hypothetical EA tool would expose
     (e.g., `find_symbol`, `get_change_history`, `summarize_subsystem`).

## Output contract

`.vscode/mcp.json` parses as valid JSON. `docs/mcp-parity-strategy.md` exists and links back
to the engagement charter.

## Self-validation

```bash
node -e "JSON.parse(require('fs').readFileSync('.vscode/mcp.json'))"
test -f docs/mcp-parity-strategy.md
grep -q "parity" docs/mcp-parity-strategy.md
```

## Failure modes

- **Inlining a token**: never. The PAT input is `${input:github_pat}` and the user fills it
  at session start.
- **Adding too many servers**: keep to filesystem + github. Anything else lands in a separate
  PR with rationale.
