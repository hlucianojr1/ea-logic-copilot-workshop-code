---
description: Initialize GitHub spec-kit in the demo workspace, author the EA Engineering Constitution, and stage the Session 6/7 feature for live /specify, /plan, /tasks demos.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit", "runCommands"]
inputs: []
outputs:
  - path: output/ea-cpp-games/specs/constitution.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/specs/plans/.gitkeep
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/specs/tasks/.gitkeep
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/specs/README.md
    kind: file
    overwrite: false
validation:
  - "test -f output/ea-cpp-games/specs/constitution.md"
  - "grep -q 'Article' output/ea-cpp-games/specs/constitution.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Bootstrap the spec-kit footprint in the demo workspace: author the **EA Engineering
Constitution** (the non-negotiables `/plan` and `/implement` will respect), and stage the
empty plan/tasks directories so the Session 6/7 live demo can run end-to-end.

## Context references

- `#file:../instructions/spec-kit-artifacts.instructions.md`
- `#file:../../factory-overlay/demo-patterns/spec-kit-flow.md`

## Pre-conditions

- Demo workspace scaffolded.
- spec-kit CLI installed (`npm i -g @github/spec-kit` or equivalent at engagement start).

## Steps

1. **`specs/constitution.md`** — articles:
   1. **No exceptions / no RTTI** — rationale + enforcement (compile flags + clang-tidy).
   2. **EASTL-first** — rationale + allowed std:: interop boundaries (filesystem APIs,
      threading primitives where EASTL has no equivalent).
   3. **Allocator-aware** — every container takes `engine_demo::allocator&`.
   4. **Determinism** — sim paths use seeded RNG; no `std::random_device` or wall-clock seed.
   5. **Real-time budgets** — frame budget ≤ 16.67 ms @ 60 FPS; allocations in inner loops
      forbidden; bounded recursion only.
   6. **Test-first** — every feature ships with tests covering invariants + boundaries.
   7. **HITL gates** — `/implement` runs one stage at a time; human approval between stages.
   8. **Security** — clang-tidy `cppcoreguidelines-*` and `bugprone-*` checks gate merges.
      Each article includes a "Verification" subsection naming the lint, test, or CI step that
      enforces it.
2. **`specs/README.md`** — a guide to the spec-kit workflow as it applies to this repo:
   how `/specify`, `/plan`, `/tasks`, `/implement` map to the directory layout; HITL gate
   convention; the two staged feature specs (`lockless-ring-buffer.md`, `fixed-string.md`)
   that Sessions 6 and 7 build.
3. **`specs/plans/.gitkeep`** and **`specs/tasks/.gitkeep`** — empty so `/plan` and `/tasks`
   have a target.

> **HITL gate:** the Constitution is reviewed by the engagement lead before commit; this is
> the artifact EA may adopt for their own repos and it carries weight.

## Output contract

- `constitution.md` exists with all 8 articles + verification subsections.
- `specs/README.md` walks through the spec-kit lifecycle.
- `plans/` and `tasks/` exist (empty).

## Self-validation

```bash
test -f output/ea-cpp-games/specs/constitution.md
for n in 1 2 3 4 5 6 7 8; do
  grep -q "## Article $n" output/ea-cpp-games/specs/constitution.md || exit 1
done
```

## Failure modes

- **Article without verification**: every article must say _how_ it is enforced.
- **Drift from the build-system's `cpp-snippets.instructions.md`**: the Constitution should
  _cite_ that file, not contradict it. Cross-link.
