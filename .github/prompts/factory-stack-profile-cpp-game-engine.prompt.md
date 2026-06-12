---
description: Generate factory-overlay/stack-profiles/cpp-game-engine.md — the C++ game-engine stack profile to upstream into copilot-workshop-factory.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit", "search"]
inputs: []
outputs:
  - path: factory-overlay/stack-profiles/cpp-game-engine.md
    kind: file
    overwrite: false
validation:
  - "test -f factory-overlay/stack-profiles/cpp-game-engine.md"
  - "npm run lint"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Produce a **stack profile** describing C++ game-engine conventions so the copilot-workshop-
factory can generate any future engagement targeting the same audience without rediscovering
these rules.

## Context references

- `#file:../../docs/engagement-charter.md`
- `#file:../instructions/cpp-snippets.instructions.md`
- Reference (existing factory): `/Users/rrehman/Documents/projects/copilot-workshop-factory/knowledge-base/stack-profiles/_template.md`
  (read for shape — do not copy verbatim).

## Pre-conditions

- Engagement charter exists.
- `cpp-snippets.instructions.md` exists.

## Steps

1. Generate the file with these sections:
   - **Identity** — id `cpp-game-engine`, language C++20, build CMake 3.28+/Ninja, package
     vcpkg (manifest), test GTest+GMock, format clang-format, lint clang-tidy, docs Doxygen.
   - **Hard constraints** — no exceptions, no RTTI, EASTL preference, allocator-aware
     containers, deterministic sim, real-time perf budgets.
   - **Idioms to prefer** — RAII, `[[nodiscard]]`, `noexcept` move, range-for, structured
     bindings, `if constexpr`, `eastl::span`, concepts, fixed-step integration.
   - **Idioms to avoid (Copilot drift hot-list)** — `std::*`, `using namespace std;`,
     exceptions, `dynamic_cast`, C-style casts, raw `new`/`delete`, `std::bind`, `typedef`,
     `<bits/stdc++.h>`, `float` for sim precision, `std::random_device` in sim.
   - **Common mistakes Copilot makes for this stack** — list keyed to demo-pattern entries;
     each mistake has a short repro and a remediation prompt.
   - **Demo project shape** — recommended layout (`include/`, `src/`, `tests/`, `cmake/`,
     `vcpkg.json`); recommended sample features (game loop, ECS, allocator pool, physics
     constraint solver, fixed-string).
   - **Required Copilot plan tier** — Business minimum; Enterprise for governance/squad demos.
   - **Off-the-rails recovery prompts** — three reusable prompt strings facilitators can paste
     when Copilot drifts.

## Output contract

File exists at the declared path with all eight sections above.

## Self-validation

```bash
grep -q "## Hard constraints" factory-overlay/stack-profiles/cpp-game-engine.md
grep -q "## Idioms to avoid" factory-overlay/stack-profiles/cpp-game-engine.md
npm run lint
```

## Failure modes

- **Listing rules without rationale**: every hard constraint must include a one-line "why".
- **Duplicating `cpp-snippets.instructions.md`**: this file is a _factory_ artifact (intended
  to be upstreamed); it should reference the instruction file, not copy it.
