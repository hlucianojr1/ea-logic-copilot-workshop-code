---
description: Implement the synthetic engine_demo module — game loop, ECS, allocator pool, frame budget — with seeded bugs keyed to Sessions 2–4.
mode: agent
model: Claude Opus 4.6
tools: ["codebase", "edit", "runCommands", "search"]
inputs: []
outputs:
  - path: output/ea-cpp-games/include/engine_demo/allocator.h
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/include/engine_demo/frame_budget.h
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/include/engine_demo/ecs/entity.h
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/include/engine_demo/ecs/component.h
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/include/engine_demo/ecs/world.h
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/include/engine_demo/sim/game_loop.h
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/include/engine_demo/sim/rng.h
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/include/engine_demo/physics/constraint_solver.h
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/src/CMakeLists.txt
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/src/allocator.cpp
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/src/frame_budget.cpp
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/src/ecs/world.cpp
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/src/sim/game_loop.cpp
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/src/sim/rng.cpp
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/src/physics/constraint_solver.cpp
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/tests/CMakeLists.txt
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/tests/allocator_test.cpp
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/tests/frame_budget_test.cpp
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/tests/ecs/world_test.cpp
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/tests/sim/game_loop_test.cpp
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/tests/physics/constraint_solver_test.cpp
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/fixtures/seeded-bugs.md
    kind: file
    overwrite: false
validation:
  - "cmake --preset default-debug -S output/ea-cpp-games"
  - "cmake --build --preset default-debug"
  - "ctest --preset default-debug --output-on-failure"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Implement a small but **realistic** synthetic game-engine module — `engine_demo` — that
serves as the focal demo for Sessions 1–4 (and is the implementation target for Sessions
6–7's Spec-Kit feature, plus Session 9's squad task). The module must compile, link, and
pass all unbugged tests. **Seeded bugs** (each tagged with a bug-id) are scattered across
specific files for Sessions 2–4 to demonstrate.

## Context references

- `#file:../instructions/cpp-snippets.instructions.md`
- `#file:../../factory-overlay/stack-profiles/cpp-game-engine.md`
- `#file:../../output/ea-cpp-games/AGENTS.md`
- `#file:../../output/ea-cpp-games/.github/copilot-instructions.md`

## Pre-conditions

- `demo-workspace-scaffold.prompt.md` completed.
- vcpkg installed with EASTL + GTest available.

## Module design

### Headers (in `include/engine_demo/`)

- **`allocator.h`** — abstract `class allocator { virtual void* allocate(size_t, size_t)=0; virtual void deallocate(void*, size_t)=0; };`
  plus a concrete `arena_allocator` and an `eastl_allocator_ref` adapter that satisfies
  EASTL's allocator concept. All methods `noexcept`. `[[nodiscard]]` on factory functions.
- **`frame_budget.h`** — class tracking frame-time samples (rolling window via
  `eastl::vector<double, eastl_allocator_ref>`); `try_reserve(double ms)` returns
  `[[nodiscard]] bool`.
- **`ecs/entity.h`** — strong typedef `struct entity_id { uint32_t value; };`, `==`, `<`,
  `hash` specialization for EASTL hash maps.
- **`ecs/component.h`** — concept `component` requiring trivially-relocatable + small.
- **`ecs/world.h`** — `class world` with allocator-aware storage; `entity_id create()`,
  `void destroy(entity_id)`, `template<component C> void add(entity_id, C)`,
  `template<component C> [[nodiscard]] C* get(entity_id) noexcept`.
- **`sim/rng.h`** — deterministic seedable RNG (Xoshiro256\*\*); `[[nodiscard]] uint64_t next() noexcept`.
- **`sim/game_loop.h`** — fixed-step integrator with accumulator pattern; `step(double dt)`,
  `[[nodiscard]] uint64_t frame_index() const noexcept`.
- **`physics/constraint_solver.h`** — sequential-impulse solver scaffold; one public
  `solve(entity_view view, double dt)` API. (Complete implementation comes from Session 9
  squad demo or Session 6–7 Spec-Kit demo, depending on which path the facilitator chose.)

### Sources

Implement each header with the contracts described, allocator-aware, no exceptions, no RTTI.
The constraint_solver.cpp ships with a deliberately incomplete implementation marked
`// TODO(session-7): complete via spec-kit /implement`.

### Tests

GoogleTest fixture per subsystem. At minimum:

- `allocator_test`: arena correctness, alignment, exhaustion behavior, reset behavior.
- `frame_budget_test`: rolling window math; `try_reserve` boundary; allocator interaction.
- `world_test`: entity creation/destruction stable IDs, component add/get, generational
  invalidation.
- `game_loop_test`: determinism (two runs with same seed produce identical frame_index/state).
- `constraint_solver_test`: basic positivity (test of behavior that survives the seeded bug;
  see below).

### Seeded bugs (CRITICAL — facilitators rely on these)

Each bug is documented in `fixtures/seeded-bugs.md` with: bug-id, file:line, symptom, root
cause, intended fix prompt, target session.

| bug-id  | file                                | symptom                                        | session   |
| ------- | ----------------------------------- | ---------------------------------------------- | --------- |
| BUG-001 | `src/allocator.cpp`                 | OOB write in arena `allocate` alignment fix-up | 2         |
| BUG-002 | `src/sim/game_loop.cpp`             | Accumulator drift at low frame rates           | 3         |
| BUG-003 | `src/ecs/world.cpp`                 | UAF when destroying entity mid-iteration       | 4 (sec)   |
| BUG-004 | `src/physics/constraint_solver.cpp` | Non-deterministic iteration order              | 4 (logic) |
| BUG-005 | `src/sim/rng.cpp`                   | Seed silently downcast to 32-bit               | 4 (sec)   |
| BUG-006 | `src/frame_budget.cpp`              | Off-by-one in rolling-window sum               | 3         |

Each bug must be:

- Reproducible by a deterministic test (the test itself is _not_ shipped — it's the
  exercise the learner writes; instead, ship a test that PASSES because the bug is
  shallow, plus a comment in the source file pointing the curious reader to a
  failing scenario described in `fixtures/seeded-bugs.md`).
- Crash-dumpable for BUG-001 and BUG-003 (Session 2 / Session 4 fixtures depend on this).

## Steps

1. Generate headers per the design.
2. Generate sources per the design, planting the six seeded bugs precisely.
3. Generate tests that pass with the bugs in place (the bugs are not directly exercised by
   the shipped tests; the _fixture_ is what triggers them).
4. Generate `fixtures/seeded-bugs.md` with the table above plus root-cause analyses.
5. Wire `src/CMakeLists.txt` and `tests/CMakeLists.txt` to register the library and tests.

> **HITL gate:** before committing, run the build and full test suite. The build MUST be
> green and ALL tests MUST pass — the bugs are latent, not active.

## Output contract

- All listed files exist and compile.
- `ctest` reports 100% pass.
- `fixtures/seeded-bugs.md` lists exactly the 6 bugs above with file:line precision.
- No `std::vector/string/unique_ptr/shared_ptr/map` in any committed source or header.
- No `try`/`catch`/`throw` anywhere; no `dynamic_cast`/`typeid` anywhere.

## Self-validation

```bash
cmake --preset default-debug -S output/ea-cpp-games
cmake --build --preset default-debug
ctest --preset default-debug --output-on-failure
grep -RE 'std::(vector|string|unique_ptr|shared_ptr|map|unordered_map)' output/ea-cpp-games/{include,src,tests} && exit 1 || true
grep -RE '\b(try|catch|throw|dynamic_cast|typeid)\b' output/ea-cpp-games/{include,src,tests} && exit 1 || true
```

## Failure modes

- **Bug too obvious**: BUG-002 must require Plan-Mode reasoning to find. If a test catches it
  outright, the bug isn't seeded correctly — soften the trigger condition.
- **Bug not reproducible**: BUG-001 and BUG-003 must be reproducible from the
  fixture-driven scenario described in `seeded-bugs.md`. Verify before commit.
- **Drifting from EASTL**: every container is EASTL with allocator-aware storage. No
  exceptions.
