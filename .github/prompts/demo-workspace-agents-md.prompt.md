---
description: Generate the demo workspace's AGENTS.md (cross-IDE durable agent guidance for engine_demo).
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: output/ea-cpp-games/AGENTS.md
    kind: file
    overwrite: true
validation:
  - "grep -q '## Build & validation' output/ea-cpp-games/AGENTS.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Produce a clean, self-contained `AGENTS.md` for the demo workspace. This file is shipped
with the workspace and is what EA engineers' agents (Copilot, Cursor, Claude Code) will read
when operating in `engine_demo`.

## Context references

- `#file:../../AGENTS.md` (build-system version — structure only)
- `#file:../../output/ea-cpp-games/.github/copilot-instructions.md`

## Steps

Sections:

1. **Mission** — engine_demo is a teaching artifact, not production game code.
2. **Non-negotiables** — no std::, no exceptions, no RTTI, allocator-aware, deterministic sim,
   `[[nodiscard]]`, `noexcept` on moves.
3. **Build & validation** — `cmake --preset default-debug`, `cmake --build`, `ctest`.
4. **File-authoring conventions** — clang-format on save, clang-tidy passes, EASTL-only.
5. **Hand-off conventions** — describes the demo workspace's own chat modes
   (`architect`, `test-author`).
6. **Safety** — destructive operations require human approval.
7. **Where to look first** — the constitution (`specs/constitution.md`), the engagement
   charter (parent repo), the seeded-bugs catalog (`fixtures/seeded-bugs.md`).

## Output contract

`AGENTS.md` overwritten with the canonical content.

## Self-validation

```bash
grep -q "## Mission" output/ea-cpp-games/AGENTS.md
grep -q "## Build & validation" output/ea-cpp-games/AGENTS.md
```

## Failure modes

- **Re-introducing exceptions** in the example snippets: don't.
