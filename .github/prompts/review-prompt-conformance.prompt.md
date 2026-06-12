---
description: Specialized review verifying every prompt / instruction / chat mode file conforms to its authoring schema.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "search", "runCommands"]
inputs: []
outputs:
  - path: docs/reviews/prompt-conformance.md
    kind: file
    overwrite: false
validation:
  - "test -f tools/validate-prompts.mjs"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Run `tools/validate-prompts.mjs` and translate its output into a human-readable
conformance report grouped by file.

## Steps

1. Run `node tools/validate-prompts.mjs --json` (script must support `--json`).
2. Parse the JSON; aggregate per file.
3. For each file, list: front-matter schema violations, missing body sections, stale
   `last_reviewed` (>90 days), missing `reviewer`.
4. Emit `docs/reviews/prompt-conformance.md` with a sortable table.

## Output contract

Single report file; entries sorted by severity then path.

## Failure modes

- **Silent skipping of unparseable files**: every file under the customization roots is
  inspected; failures are reported, not ignored.
