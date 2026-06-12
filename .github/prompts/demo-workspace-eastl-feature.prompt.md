---
description: Author the EASTL-based feature (lockless ring-buffer + fixed-string utility) used by Sessions 6–7 Spec-Kit demo. Implementation lands AFTER spec-kit /implement runs.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit", "search"]
inputs: []
outputs:
  - path: output/ea-cpp-games/specs/specs/lockless-ring-buffer.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/specs/specs/fixed-string.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/include/engine_demo/util/.gitkeep
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/src/util/.gitkeep
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/tests/util/.gitkeep
    kind: file
    overwrite: false
validation:
  - "test -f output/ea-cpp-games/specs/specs/lockless-ring-buffer.md"
  - "test -f output/ea-cpp-games/specs/specs/fixed-string.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Stage the **specs** and **empty implementation directories** for the EASTL-based feature
that Sessions 6 (Spec-Kit Pt 1) and 7 (Spec-Kit Pt 2) build to. The actual `.h`/`.cpp`/test
sources are produced **during the live session** by `/implement` invocations — that's the
demo. Pre-creating the dirs ensures `/implement` has a stable target.

## Context references

- `#file:../instructions/spec-kit-artifacts.instructions.md`
- `#file:../instructions/cpp-snippets.instructions.md`
- `#file:../../docs/engagement-charter.md`

## Pre-conditions

- `demo-workspace-scaffold.prompt.md` and `demo-workspace-engine-module.prompt.md` completed.
- spec-kit Constitution authored (will be done by `demo-workspace-spec-kit-init.prompt.md`).

## Steps

1. **`specs/specs/lockless-ring-buffer.md`** — feature spec following
   `spec-kit-artifacts.instructions.md` format:
   - Motivation: SPSC ring-buffer for telemetry events, allocator-aware, deterministic.
   - Public API sketch — header excerpt in `cpp` fence (must compile, no exceptions, no RTTI).
   - Invariants: capacity is power of two; `try_push`/`try_pop` are wait-free; no allocations
     after construction.
   - Test contract: list 6 named tests under `tests/util/lockless_ring_buffer_test.cpp`.
   - Risks: false sharing, ABA on size_t counters, allocator lifetime.
2. **`specs/specs/fixed-string.md`** — feature spec:
   - Motivation: small-string optimization with compile-time max length, no heap.
   - Public API: `template<size_t N> class fixed_string`.
   - Invariants: capacity is `N`; `push_back` past capacity is a logged error (no exception).
   - Test contract: list 5 named tests under `tests/util/fixed_string_test.cpp`.
   - Risks: alignment for SIMD-friendly access, char-encoding (ASCII only for v1).
3. Create empty `include/engine_demo/util/`, `src/util/`, `tests/util/` directories with
   `.gitkeep` so the path is stable for later `/implement` runs.

## Output contract

- Two spec files exist, each with the eight required spec sections.
- Three util/ subdirectories exist with `.gitkeep`.
- No production source files yet — those come from spec-kit `/implement`.

## Self-validation

```bash
grep -q "## Test contract" output/ea-cpp-games/specs/specs/lockless-ring-buffer.md
grep -q "## Test contract" output/ea-cpp-games/specs/specs/fixed-string.md
test -d output/ea-cpp-games/include/engine_demo/util
```

## Failure modes

- **Pre-implementing the feature**: do NOT generate `.h`/`.cpp` here — that defeats the
  Session 6/7 demo. The feature is born during the live `/implement`.
- **Spec without test contract**: every spec must name its tests; no exceptions.
