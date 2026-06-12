---
description: Specialized C++ snippet review — verify every fenced cpp block in the target compiles under the engagement constraints.
mode: agent
model: Claude Opus 4.6
tools: ["codebase", "search", "runCommands"]
inputs:
  - name: target_path
    required: true
outputs:
  - path: docs/reviews/cpp-snippets-${target_slug}.md
    kind: file
    overwrite: false
validation:
  - "test -f tools/extract-snippets.mjs"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Pass every `cpp` block in the target through `tools/extract-snippets.mjs` and report
compile failures plus rule violations (std::, exceptions, RTTI, missing nodiscard/noexcept).

## Steps

1. Extract all `cpp` blocks from `target_path` using the same regex as `extract-snippets.mjs`.
2. For each block:
   - Compile with `-std=c++20 -fno-exceptions -fno-rtti -Wall -Wextra -Werror`.
   - Lint with clang-tidy if available.
   - Check for: `std::vector|string|unique_ptr|shared_ptr|map|unordered_map`, `try|catch|throw`,
     `dynamic_cast|typeid`, missing `[[nodiscard]]` on factories, missing `noexcept` on moves.
3. Emit a per-block table: block id, line range, compile result, lint result, rule violations.
4. Output to `docs/reviews/cpp-snippets-${target_slug}.md`.

## Output contract

Report file exists; one row per `cpp` block; failing blocks have line:column citations.

## Failure modes

- **Marking a block "passed" without compiling it**: never. If extract-snippets isn't
  available, abort and request bootstrap-ci to run first.
