---
description: Scaffold the EA-facing demo workspace under output/ea-cpp-games/ — directory tree, CMake, vcpkg, lints, formatting, EASTL submodule.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit", "runCommands"]
inputs: []
outputs:
  - path: output/ea-cpp-games/.gitignore
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/.gitattributes
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/.editorconfig
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/.clang-format
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/.clang-tidy
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/CMakeLists.txt
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/CMakePresets.json
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/vcpkg.json
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/cmake/CompilerOptions.cmake
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/cmake/Dependencies.cmake
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/README.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/AGENTS.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/.github/copilot-instructions.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/third_party/.gitkeep
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/include/.gitkeep
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/src/.gitkeep
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/tests/.gitkeep
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/specs/.gitkeep
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/fixtures/.gitkeep
    kind: file
    overwrite: false
validation:
  - "test -d output/ea-cpp-games"
  - 'node -e "JSON.parse(require(''fs'').readFileSync(''output/ea-cpp-games/CMakePresets.json''))"'
  - 'node -e "JSON.parse(require(''fs'').readFileSync(''output/ea-cpp-games/vcpkg.json''))"'
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Lay down the bones of the EA-facing demo workspace. This is the artifact EA's engineers will
clone and follow along with during sessions. After this prompt completes, the next prompts
in Tier 2 fill in the engine module, EASTL feature, fixtures, and customization layer.

## Context references

- `#file:../../factory-overlay/stack-profiles/cpp-game-engine.md`
- `#file:../../factory-overlay/client-profiles/ea-games.yaml`
- `#file:../instructions/cpp-snippets.instructions.md`
- `#file:../../docs/engagement-charter.md`

## Pre-conditions

- Factory-overlay artifacts exist (Tier 1 completed).
- vcpkg is installed and `VCPKG_ROOT` is set, or vcpkg is bootstrapped via vcpkg.json.

## Steps

1. **Top-level layout**: create `include/`, `src/`, `tests/`, `cmake/`, `specs/`,
   `fixtures/`, `third_party/`, `.github/`. Each gets a `.gitkeep` for empty dirs.
2. **`.clang-format`** — Google base style, 4-space indent, ColumnLimit 100, AllowShortIfStatementsOnASingleLine `Never`,
   AllowShortFunctionsOnASingleLine `Inline`, BreakBeforeBraces `Attach`, IncludeBlocks `Regroup`,
   IncludeCategories tuned for `EASTL/` first, project headers second, system last.
3. **`.clang-tidy`** — checks: `-*,bugprone-*,cert-*,cppcoreguidelines-*,modernize-*,performance-*,portability-*,readability-*`
   with explicit disables for `cppcoreguidelines-pro-bounds-array-to-pointer-decay` (false-positive prone),
   `modernize-use-trailing-return-type` (style choice). WarningsAsErrors mirrors the check list.
4. **`CMakeLists.txt`** — top-level project `engine_demo`, C++20, `include(cmake/CompilerOptions.cmake)`,
   `include(cmake/Dependencies.cmake)`, `add_subdirectory(src)`, `enable_testing()`, `add_subdirectory(tests)`.
5. **`cmake/CompilerOptions.cmake`** — set `-fno-exceptions -fno-rtti` (GCC/Clang) / `/EHs-c- /GR-` (MSVC),
   `/W4 /WX` or `-Wall -Wextra -Werror`, `/permissive-`, IPO/LTO for Release. Function:
   `engine_demo_set_target_options(target)`.
6. **`cmake/Dependencies.cmake`** — `find_package(EASTL CONFIG REQUIRED)`,
   `find_package(GTest CONFIG REQUIRED)`. Declare INTERFACE library `engine_demo::eastl`
   that links `EASTL::EASTL` plus our custom-allocator override translation unit.
7. **`vcpkg.json`** — manifest with dependencies `eastl`, `gtest`, `nlohmann-json` (for fixture
   serialization), `fmt` (logging). builtin baseline pinned to a recent stable.
8. **`CMakePresets.json`** — presets `default-debug`, `default-release` for ninja-multi-config;
   set `VCPKG_TARGET_TRIPLET` per platform; add a `windows-msvc` preset and a `linux-gcc13` preset.
9. **`output/ea-cpp-games/.gitignore`** — local `build/`, `vcpkg_installed/`, `compile_commands.json`,
   `*.dmp.local`, `*.pdb.local`, `.vscode/*` (per workspace conventions).
10. **`output/ea-cpp-games/.gitattributes`** — `* text=auto eol=lf`, binary markers for `.dmp/.pdb`.
11. **`output/ea-cpp-games/.editorconfig`** — same conventions as the parent repo (4-space C++).
12. **`output/ea-cpp-games/README.md`** — learner-facing intro: what the demo workspace is,
    how to build, how to run tests, where to find each session's anchor files.
13. **`output/ea-cpp-games/AGENTS.md`** — agent rules **scoped to the demo workspace** (these
    are different from the build-system AGENTS.md). Forbids std::, exceptions, RTTI; requires
    EASTL allocator-aware code; references the constitution under `specs/constitution.md`.
14. **`output/ea-cpp-games/.github/copilot-instructions.md`** — workshop-focused Copilot
    instructions for the demo workspace (this is the file EA engineers learn FROM; see
    `demo-workspace-instructions-prompts-chatmodes.prompt.md` for the deeper customization).
    Stub here; that prompt fleshes it out.

> **HITL gate:** before adding `third_party/EASTL` as a submodule, the user confirms the
> EASTL revision to pin (default: tip-of-master at engagement start, recorded in
> `output/ea-cpp-games/third_party/EASTL.commit`).

## Output contract

All declared files exist; CMake configures cleanly:

```bash
cmake --preset default-debug
```

(should succeed on a machine with vcpkg + ninja; if vcpkg isn't available, this is a
documented warning, not a failure of this prompt).

## Self-validation

```bash
test -d output/ea-cpp-games/{include,src,tests,cmake,specs,fixtures,third_party,.github}
node -e "JSON.parse(require('fs').readFileSync('output/ea-cpp-games/CMakePresets.json'))"
node -e "JSON.parse(require('fs').readFileSync('output/ea-cpp-games/vcpkg.json'))"
grep -q "fno-exceptions" output/ea-cpp-games/cmake/CompilerOptions.cmake
grep -q "fno-rtti" output/ea-cpp-games/cmake/CompilerOptions.cmake
```

## Failure modes

- **Forgetting `-fno-exceptions` / `-fno-rtti`**: fail loudly. The whole engagement rests on
  these flags being on by default.
- **Pulling in std-only deps via vcpkg**: stick to EASTL + gtest + nlohmann-json + fmt. Any
  new dep requires a separate PR with rationale.
