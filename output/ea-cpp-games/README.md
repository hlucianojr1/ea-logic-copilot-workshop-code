# engine_demo — EA × Insight Copilot Workshop demo workspace

> **Generated.** Do not edit by hand. Reproducible from prompts under
> `.github/prompts/demo-workspace-*.prompt.md` at the build-system repo root.

This is a synthetic C++20 game-engine workspace. It is the **demo target** for all nine
sessions. It is **not** production code — it is intentionally small, contains seeded bugs,
and is licensed under the same terms as the parent repository.

## What's here

```text
include/engine_demo/   # public headers
src/engine_demo/       # implementations
tests/engine_demo/     # GoogleTest binaries
cmake/                 # CompilerOptions.cmake, Dependencies.cmake
specs/                 # spec-kit constitution + per-feature specs
fixtures/              # bug reports, crash-dump capture scripts
third_party/           # vendored or submoduled deps (EASTL pinned)
.github/               # demo-workspace-scoped Copilot customization
```

## Build

Prerequisites: CMake 3.28+, Ninja, vcpkg (manifest mode), a recent C++20 compiler
(MSVC 19.38+ / GCC 13+ / Clang 17+).

```bash
cmake --preset default-debug
cmake --build --preset default-debug
ctest --preset default-debug --output-on-failure
```

The build is `-fno-exceptions -fno-rtti` everywhere. EASTL is the only allowed container
library in committed code.

### Diagnostic presets (Session 03)

Two additional presets exist specifically to make seeded bugs reproducible:

| Preset      | Flags                              | Purpose                                                                                  |
| ----------- | ---------------------------------- | ---------------------------------------------------------------------------------------- |
| `optimized` | `RelWithDebInfo` (`-O2 -DNDEBUG`)  | Reproduces **BUG-007** — the optimizer elides a UB-dependent overflow guard that "works" in Debug. |
| `tsan`      | `-fsanitize=thread -g -O1` (Debug) | Reproduces **BUG-009** — ThreadSanitizer reports the relaxed-ordering data race in `event_slot`. Not available on Windows. |

```bash
# BUG-007: enable the DISABLED_ regression test in tests/engine_demo/test_timer.cpp, then:
cmake --preset optimized && cmake --build --preset optimized
ctest --preset optimized -R timer

# BUG-009: enable the DISABLED_ regression test in tests/engine_demo/test_event_queue.cpp, then:
cmake --preset tsan && cmake --build --preset tsan
ctest --preset tsan -R event_queue
```

With the seeded bugs in place, the enabled tests FAIL under these presets (that is the
demo). After applying the canonical fixes they pass, and all 11 suites stay green under
`default-debug`, `optimized`, and `tsan`.

## Run the playable sandbox

The `apps/sandbox/ea-sandbox` binary is the visual entry point — a 2D verlet-rope-plus-
particles scene driven by `engine_demo::physics::constraint_solver`,
`engine_demo::sim::game_loop`, `engine_demo::sim::rng`, and `engine_demo::frame_budget`.
The HUD surfaces the seeded-bug anchors live (BUG-002 wall/sim drift,
BUG-004 trace-digest divergence on reseed, BUG-006 frame-time graph).

```bash
# Interactive (opens a window):
./build/apps/sandbox/ea-sandbox

# Headless determinism trace (used by CI):
./build/apps/sandbox/ea-sandbox --headless --seed 42 --frames 600 --out trace.csv
```

Controls: `Space` pause / resume · `S` single-step · `R` reseed · `+` / `-` speed ·
`F1` deliberate crash (Session 02 demo) · `Esc` quit.

To opt out of building the sandbox (e.g., on a runner without raylib system deps):

```bash
cmake --preset default-debug -DENGINE_DEMO_BUILD_SANDBOX=OFF
```

See [apps/sandbox/README.md](apps/sandbox/README.md) for the bug-visibility cheat sheet.

## Seeded bugs

The workspace ships with intentionally seeded defects used by Sessions 2, 3, and 4. See
`fixtures/seeded-bugs.md` for the catalog. Do not fix them — they are the demo material.

## Per-session anchor files

| Session | Anchor file(s)                                                                      |
| ------- | ----------------------------------------------------------------------------------- |
| 01      | `include/engine_demo/ecs/SUBSYSTEM.md`, `src/engine_demo/sim/game_loop.cpp`         |
| 02      | `fixtures/crash_dumps/BUG-001/`, `src/engine_demo/allocator.cpp`                    |
| 03      | `src/engine_demo/sim/game_loop.cpp`, `src/engine_demo/frame_budget.cpp`             |
| 04      | `src/engine_demo/ecs/world.cpp`, `src/engine_demo/sim/rng.cpp`                      |
| 05      | `include/engine_demo/ecs/SUBSYSTEM.md`, the chat-mode tool-allowlist matrix         |
| 06–07   | `specs/constitution.md`, `specs/lockless-ring-buffer/`, `specs/fixed-string/`       |
| 08      | the issue staged for the Coding Agent, plus the fallback PR                         |
| 09      | `.github/chatmodes/squad-coordinator.chatmode.md` (and the three specialist modes)  |

## Constitution

The non-negotiables for any code in this workspace are codified in
[`specs/constitution.md`](specs/constitution.md). Spec-Kit's `/implement` honors them; the
reviewer chat mode enforces them.
