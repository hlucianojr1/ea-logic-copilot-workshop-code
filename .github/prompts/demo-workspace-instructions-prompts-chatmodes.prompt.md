---
description: Generate the demo workspace's own .github/copilot-instructions.md, scoped instruction files, prompts, and chat modes — the customization layer EA engineers learn from.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: output/ea-cpp-games/.github/copilot-instructions.md
    kind: file
    overwrite: true
  - path: output/ea-cpp-games/.github/instructions/eastl.instructions.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/.github/instructions/no-exceptions.instructions.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/.github/instructions/allocator-aware.instructions.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/.github/instructions/tests.instructions.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/.github/prompts/eastl-conformance-review.prompt.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/.github/prompts/cppcheck-this.prompt.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/.github/prompts/explain-subsystem.prompt.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/.github/prompts/sequence-diagram.prompt.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/.github/prompts/security-scan-cwe.prompt.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/.github/chatmodes/architect.chatmode.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/.github/chatmodes/test-author.chatmode.md
    kind: file
    overwrite: false
validation:
  - "test -f output/ea-cpp-games/.github/copilot-instructions.md"
  - "ls output/ea-cpp-games/.github/instructions/*.instructions.md | wc -l | grep -q 4"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Produce the customization layer for the **demo workspace** — this is the artifact EA's
engineers will study and adapt for their own repos. It is structurally similar to the
build-system's customization layer (this repo's `.github/`) but with content focused on the
demo workspace's own code (engine_demo).

## Context references

- `#file:../../.github/copilot-instructions.md` (build-system equivalent — different
  audience, similar structure)
- `#file:../instructions/cpp-snippets.instructions.md`
- `#file:../../factory-overlay/stack-profiles/cpp-game-engine.md`

## Steps

1. **`output/ea-cpp-games/.github/copilot-instructions.md`** — repo-wide rules for the
   demo workspace: C++20, EASTL-first, no exceptions, no RTTI, allocator-aware, real-time
   constraints, deterministic sim. Link to subsystem instruction files. Include a
   "Off-the-rails recovery" section that mirrors the build-system's but is specific to
   game-engine drift patterns.
2. **`instructions/eastl.instructions.md`** — `applyTo: "**/*.{h,hpp,cpp,cc,cxx,inl}"`.
   Specific EASTL idioms: `eastl::vector` with allocator-ref, `eastl::fixed_string`,
   `eastl::span` for views, EASTL hash_map vs std unordered_map.
3. **`instructions/no-exceptions.instructions.md`** — `applyTo: "**/*.{h,hpp,cpp}"`. The
   error-handling alternative pattern: `expected<T, error_code>` (pre-C++23 implementation in
   the engine_demo or via `tl::expected` if vendored), `[[nodiscard]]` everywhere, status
   returns, `assert(...)` for invariants in debug.
4. **`instructions/allocator-aware.instructions.md`** — every container takes `engine_demo::allocator&`.
   Show the right way to write a class that owns an EASTL container with an injected allocator.
5. **`instructions/tests.instructions.md`** — `applyTo: "tests/**/*.cpp"`. GoogleTest fixture
   patterns; mock allocator; determinism assertion helpers; how to write a test that
   detects allocator misuse.
6. **Prompts** (5 files):
   - `eastl-conformance-review.prompt.md` — review the open file, flag every `std::*` use,
     suggest EASTL replacements with allocator-aware migration steps.
   - `cppcheck-this.prompt.md` — full lint sweep on the open file, prioritized by severity.
   - `explain-subsystem.prompt.md` — generate big-picture + class-diagram explanation of the
     given subsystem; produces Mermaid diagrams.
   - `sequence-diagram.prompt.md` — generate runtime sequence diagram for the given function
     entry point; Mermaid sequenceDiagram.
   - `security-scan-cwe.prompt.md` — scan for CWE-787, -416, -476 specifically; output a
     ranked list with false-positive triage.
7. **Chat modes** (2 files):
   - `architect.chatmode.md` — read-only architecture analysis specialist.
   - `test-author.chatmode.md` — test-only author specialist.

## Output contract

All 12 files exist. The `.github/copilot-instructions.md` may overwrite the stub from the
scaffold prompt — it's the only `overwrite: true` here.

## Self-validation

```bash
test -f output/ea-cpp-games/.github/copilot-instructions.md
test -f output/ea-cpp-games/.github/instructions/eastl.instructions.md
ls output/ea-cpp-games/.github/prompts/*.prompt.md | wc -l | grep -q 5
ls output/ea-cpp-games/.github/chatmodes/*.chatmode.md | wc -l | grep -q 2
```

## Failure modes

- **Duplicating the build-system's customization layer verbatim**: the audience is different
  (EA engineers writing game code, not facilitators building workshops). Tailor accordingly.
- **Inventing engine APIs in instructions**: every `cpp` snippet must reference real
  `engine_demo` types and compile.
