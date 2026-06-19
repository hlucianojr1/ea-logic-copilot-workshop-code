# Changelog

All notable changes to the EA × Insight Copilot Workshop build system are recorded here.

This file follows [Keep a Changelog](https://keepachangelog.com/en/1.1.0/) and this project
adheres to [Semantic Versioning](https://semver.org/).

## [Unreleased]

<!-- markdownlint-disable MD024 -->

### Removed

- **Scoped repository to Session 03 (Logic Bugs) only.** Deleted all content
  unrelated to the C++ logic-bug resolution workshop:
  - Session bundles `sessions/01-*` through `sessions/09-*` (except `03-logic-bugs`)
  - Ten other-session prompt files from `.github/prompts/` (sessions 01, 02,
    04–09, plus `demo-workspace-fixtures-crash-dumps` and `demo-workspace-spec-kit-init`)
  - `.github/instructions/spec-kit-artifacts.instructions.md`
  - `.github/chatmodes/squad-coordinator.chatmode.md`
  - `tools/new-session.mjs`
  Retained: `sessions/03-logic-bugs/` (all files), `output/ea-cpp-games/` (full
  C++ workspace with seeded bugs BUG-001–BUG-010), and all `.github/` files that
  remain relevant to Session 03 authoring and C++ snippet validation.

### Added

- **Session 03 (Logic Bugs): full-SDLC + QA dual-track upgrade.**
  - `sessions/03-logic-bugs/sdlc-walkthrough.md` — complete issue → branch →
    `@logic-bug-planner` fix → PR (constitutional review rubric, 8 articles) → CI →
    merge loop, plus worktree-mcp "ToT at scale" wiring and sandbox visual/headless
    trace repro evidence.
  - `sessions/03-logic-bugs/qa-track.md` — QA/SDET track: Copilot-assisted test-plan
    authoring, real-vs-false-positive triage rubric (calibrated on FP-001/002/003),
    four-gate sign-off template, and trace-diff regression metrics.
  - Four new exercises: `03-ub-and-the-optimizer.md` (BUG-007),
    `04-bitwise-vs-logical.md` (BUG-008), `05-atomic-but-not-ordered.md`
    (BUG-009 + FP-003), `06-sentinel-trap.md` (BUG-010, CoT-vs-ToT comparison).
  - New `.github/agents/logic-bug-planner.agent.md` four-phase resolver agent
    (OBSERVE → REPRODUCE → FIX → VERIFY with HITL gates).
  - Dual-track (developer + QA) facilitator markers in `facilitator-script.md`;
    two new slides in `slides.outline.md`.

- **Demo workspace: diagnostic CMake presets + BUG-009 made reproducible.**
  - New `optimized` preset (RelWithDebInfo) reproduces BUG-007's optimizer-elided
    overflow guard; new `tsan` preset (`-fsanitize=thread -g -O1`) reproduces
    BUG-009's relaxed-ordering data race. Documented in `output/ea-cpp-games/README.md`.
  - Rewrote `DISABLED_consumer_observes_complete_payload` in
    `tests/engine_demo/test_event_queue.cpp` from a single-threaded stand-in to a real
    cross-thread producer/consumer handoff that TSAN deterministically flags.
  - `event_slot::publish`/`try_consume` now copy the payload field-by-field: the
    whole-struct assignment lowered to compiler-emitted memcpy, which the
    AppleClang/arm64 TSAN runtime does not report races through (verified false
    negative); discrete accesses restore detection. Seeded defect (relaxed ordering)
    unchanged. All 11 suites green under `default-debug`, `optimized`, and `tsan`.

- **Session 03 (Logic Bugs): self-guided tutor agent + self-contained learner
  guide.** Added a pre-built `.github/agents/logic-bug-tutor.agent.md` that paces
  a learner through the session one bug at a time
  (observe → reproduce → fix → verify) with HITL gates. Rewrote
  `sessions/03-logic-bugs/learner-guide.md` to be fully self-contained
  (environment setup, green-baseline build/test commands, inline Ask/Edit
  prompts, and a "start the tutor" path). Synced
  `.github/prompts/session-03-logic-bugs.prompt.md` to regenerate the
  as-delivered nine-artifact set with corrected `fixtures/bug-reports/` paths,
  and added `docs/session-03-logic-bugs-runbook.md` (artifact catalog +
  gap-remediation log).

- **macOS arm64 (Apple Silicon) build verified.** `output/ea-cpp-games` now
  builds and all 7 CTest targets pass on macOS 14+ with AppleClang 21 /
  arm64-osx vcpkg triplet. Prerequisites: Xcode CLT, Homebrew (`ninja`,
  `pkg-config`), vcpkg cloned to `~/vcpkg`. Configure: `cmake --preset
  default-debug`; build: `cmake --build --preset default-debug`.

- **Training sessions 01–09: Copilot UI terminology updated** to match the
  current VS Code GitHub Copilot extension (three-tab model: **Ask**, **Edit**,
  **Agent**). All occurrences of the deprecated "Plan Mode" and "Edit Mode"
  labels replaced with "Ask tab" and "Edit tab" respectively.

- **Session 05 (Context Engineering): Agent mode + MCP demo content.**
  Facilitator script gains "Block 1.5 — VS Code Agent mode" (Ask/Edit/Agent
  comparison, VS Code Agent mode vs. GitHub Copilot Coding Agent distinction)
  and "Block 3.5 — MCP demo" (live `.vscode/mcp.json` walkthrough using the
  repo's existing `filesystem` + `github` servers). Learner guide gains
  matching orientation table and MCP tools reference section.

- **Session 06 (Spec-Kit Pt 1): Removed fictional `@github/spec-kit` CLI.**
  Facilitator script, learner guide, and pre-work email updated to clarify
  that the spec-kit flow uses structured Copilot Chat prompt patterns
  (`/specify`, `/plan`, `/tasks`, `/implement`) — no npm package exists.

- **Session 08 (Coding Agent): Two-agents orientation + setup config.**
  Facilitator script and learner guide add a comparison table distinguishing
  VS Code Agent mode (synchronous, in-editor) from GitHub Copilot Coding Agent
  (async, PR-opening, cloud sandbox) and a `copilot-setup-steps.yml` walkthrough
  showing how to configure MCP server access for the cloud agent.

- **Session 09 (Multi-Agent Squad): Horizon table** covering GitHub Models,
  Copilot Extensions, native agent coordination, and the emerging MCP server
  ecosystem added to Q&A / closing section.

### Fixed

- **Session 03 (Logic Bugs): training-doc verification — 9 documentation drift
  items reconciled + BUG-002 RED repro restored.** Audited
  `sessions/03-logic-bugs/logic-bug-workshop-training.md` against the live
  `output/ea-cpp-games/` workspace and corrected every divergence recorded in
  the new `docs/session-03-training-verification-checklist.md`:
  - **BUG-002 (timestep drift)** — reseeded the `DISABLED_long_run_does_not_drift`
    test in `tests/engine_demo/test_game_loop.cpp` so it reproduces RED exactly as
    the doc claims: a 10 ms (`1/100 s`) frame delta against the `1/60 s` fixed step
    over 3600 frames, comparing the seeded `float` accumulator's substep count to a
    `double` reference (`loop_total` 2159 vs `ref_total` 2160). Baseline stays
    11/11 green (test remains `DISABLED_`).
  - **Line-number / behavior corrections** — timer guard line `25`→`32`;
    interpolator sentinel line `52`→`50`; BUG-007 repro split into "FAILS under
    `optimized`, PASSES under `default-debug`"; `event_queue` quote updated to the
    field-by-field copy; test-inventory cell corrected to the float-vs-double
    substep mismatch.
  - **Planner phase label** Create→Review; **BUG-006** re-described as
    "passes as-seeded / non-reproducing hypothesis" (cannot be reseeded RED
    without breaking the enabled baseline) and marked doc-corrected.
  - Refreshed the checklist's per-section Result cells and drift-summary rows to
    past-tense "Applied". Generic float-mantissa pedagogy and the illustrative
    appendix figures were intentionally left unchanged.

- **Repo gate cleanup: all lint and snippet gates green.** Brought the full
  repository to a clean `npm run lint` + `npm run validate:snippets` +
  `npm run validate:prompts` state with mechanical, content-preserving fixes:
  - **`crash-fix-engineering.instructions.md`** — seven illustrative blocks
    (one file-tree diagram + six C++ anti-pattern snippets) relabeled from
    `cpp` to `text` so they are no longer extracted by the snippet compiler.
  - **`workshop-guide-advanced.md`** — resolved 42 markdownlint errors:
    demoted seven chapter `#` headings to `##` sections (single-H1 rule),
    disambiguated duplicate "Learning Objectives" headings per section,
    removed a trailing colon on a `### Prompt` heading (MD026), escaped
    ordered survey numbers `8.`–`11.` (MD029), and wrapped 28 prompt/response
    transcripts in four-backtick `text` fences so their inner code fences
    nest cleanly.
  - **Session 02 deliverables + post-mortem (10 fences)** — added explicit
    `text` language to bare fences (MD040) on workflow/sequence diagrams,
    file trees, and MCP-tool pseudo-commands across `crash-orchestrator`,
    `resolution-tracking`, `crash-dump-intake`, `resolution-brief`,
    `agentic-architecture`, and `2026-05-04-agentic-crash-dump-sdlc.md`.
  - **Six non-compiling illustrative C++ fragments** relabeled from `cpp` to
    `cpp no-compile` so they keep syntax highlighting but are skipped by the
    snippet compiler: five partial fragments in `workshop-guide-advanced.md`
    (release/acquire ordering fixes, `frame_budget::rolling_average`,
    `snapshot_equals`, integer-overflow guard) and the GTest scaffold in
    `regression-test-generation.prompt.md`.
  - **Prettier formatting** applied to twelve Session 02 / Session 03 files.
  Generator-prompt regeneration was intentionally out of scope; only the
  as-delivered files were touched. (`lychee` link check could not run — the
  binary is not installed in this environment — but no markdown links were
  altered by this cleanup.)

- **`apps/sandbox/app.cpp`: double-promotion warning on AppleClang.**
  `std::sin(time_f * 47.0)` / `std::cos(time_f * 53.0)` used `double`
  literals with a `float` argument, triggering `-Werror,-Wdouble-promotion`
  on macOS. Literals changed to `47.0F` / `53.0F`; redundant `static_cast`
  removed.

- **`tests/engine_demo/test_allocator.cpp`: stack buffer alignment on arm64.**
  `std::array<std::byte, 1024>` on the stack is only 8-byte aligned on
  arm64 macOS, causing `basic_allocation_returns_aligned_pointer` to fail.
  Buffer declaration updated to `alignas(16)`.

### Fixed

- **Sandbox and POC windows invisible on multi-monitor macOS (ultrawide
  secondary display).** On machines where the active monitor (e.g. a 3840×1600
  ultrawide) is not macOS's "main display" (the one carrying the menu bar),
  GLFW's `_glfwTransformYCocoa()` computes window coordinates using
  `CGDisplayBounds(CGMainDisplayID())`.  The resulting position lands outside
  the physical bounds of the active monitor, so the window is never visible
  on screen even though `IsWindowFocused()=1` and `IsWindowHidden()=0` — those
  flags mean "key window" and "not ordered out," not "physically on a monitor."
  Two-layer fix applied to both `apps/sandbox` and `apps/poc`:
  1. **C API layer** (`app.cpp` / `hello.c`): after `InitWindow`, call
     `GetCurrentMonitor()` + `GetMonitorWidth/Height/Position()` to compute the
     center of the target monitor, then `SetWindowPosition()` to override GLFW's
     placement; follow with `FLAG_WINDOW_TOPMOST` toggle to prompt the
     WindowServer compositor to re-evaluate layer order; then
     `SetWindowFocused()` + `PollInputEvents()`.
  2. **Obj-C layer** (`force_visible.m` in both `apps/sandbox` and `apps/poc`):
     `[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular]`,
     `[NSApp activateIgnoringOtherApps:YES]`,
     `[window setCollectionBehavior:CanJoinAllSpaces]`,
     `[window orderFrontRegardless]`, `[window center]`, `[window makeKeyWindow]`.
     This belt-and-suspenders Obj-C layer bypasses GLFW's coordinate system
     entirely and forces the window onto the current monitor/Space.
  CMake change: `apps/poc/CMakeLists.txt` and `apps/sandbox/CMakeLists.txt`
  both add `enable_language(OBJC)` + the new `force_visible.m` source under
  `if(APPLE)`.  The POC also gains `SetTargetFPS(60)` so 180 frames ≈ 3 s.
  Headless rope digest at seed 42 / 60 frames still `33a6319d856d4869`
  (fix is `#if defined(__APPLE__)` interactive-path only; headless is
  unaffected).

- **Sandbox black-window on Apple Silicon Retina — drop HUD `RenderTexture2D`
  cache; direct-draw HUD each frame.** After the dt fix landed (commit
  `ff662fc`), the interactive window came up fully black on M-series Macs
  even though telemetry showed physics evolving and `t_draw_world_us` non-
  zero. Root cause: the HUD was composed off-screen via `LoadRenderTexture` /
  `BeginTextureMode` / `DrawTextureRec`. The framebuffer-binding swap inside
  `BeginTextureMode` / `EndTextureMode` is fragile on raylib's OpenGL-on-
  Metal path — a transient mismatch discards the world's draws into a stale
  FBO and the final blit covers everything with the opaque-cleared HUD
  texture. The cache was originally added as an ANR mitigation against
  raylib's per-character `GetGlyphIndex` linear scan, but the actual ANR
  cause was `SetTargetFPS`'s busy-wait — already solved by the
  `sleep_for`-based frame limiter — so the cache is now unnecessary
  complexity. `output/ea-cpp-games/apps/sandbox/app.cpp` now direct-draws
  the HUD each frame; `LoadRenderTexture` / `UnloadRenderTexture` /
  `BeginTextureMode` / `EndTextureMode` / `DrawTextureRec` are gone from the
  renderer. Verified with a 60-frame screenshot capture at seed 42: gradient
  background, world grid, hanging rope, motion-trailed particles, and full
  HUD (BUG-002/004/006 lines, counts panel, frame-budget histogram) all
  render correctly. Headless rope digest at seed 42 / 60 frames still
  `33a6319d856d4869`.

### Added

- **Sandbox full-debug runtime telemetry.** New `apps/sandbox/telemetry.{h,cpp}`
  TU plus instrumented `app.cpp` main loop emit a JSON-Lines stream of
  per-frame frame-graph spans (`t_input_us`, `t_step_us`, `t_draw_world_us`,
  `t_draw_hud_us`, `t_swap_us`, `t_sleep_us`, `t_total_us`), per-frame physics
  state (`bodies`, `constraints`, `particles`, `state_digest`, `substeps`),
  render counters (HUD real-refreshes vs. blits/sec), and event records for
  window focus / minimize / resize transitions, scene switches, reseeds (with
  pre/post digest — BUG-004 visualizer), node grabs, particle bursts, and
  `dt` clamps. raylib's TraceLog is mirrored into the JSONL via
  `SetTraceLogCallback` so GL init, shader compile, FBO create, and driver
  warnings live in the same stream. An always-on stderr 1-line liveness
  tick fires every ~1 s with rolling `p50` / `p95` frame-time so the
  operator has zero-config visibility that the loop is healthy. CLI:
  `--debug` (frame level), `--telemetry-level {off,frame,verbose}`,
  `--telemetry-out PATH`, `--watchdog` (hang-detection thread that emits
  a `watchdog` event after 2 s of heartbeat stall — observe-only,
  never kills the process), `--no-crash-handlers` (skip
  `SIGSEGV/SIGBUS/SIGABRT/SIGFPE/SIGILL` install when running under a
  debugger). Crash path emits a JSONL `crash` record + `backtrace_symbols_fd`
  on stderr before re-raising. Hot path is zero-allocation `std::fprintf`.
  Headless rope digest at seed 42 / 60 frames still `33a6319d856d4869`
  (interactive-only instrumentation; CSV output untouched).

- **Sandbox showcase upgrade — four physics scenes, mouse interaction, polished
  HUD.** What was a single hanging-rope demo is now a cold-open-ready, multi-scene
  physics showcase aimed at AAA C++ engineers. The sandbox is the visible face
  of the whole workshop; this is the version we put on stage.
  - `output/ea-cpp-games/apps/sandbox/scene.{h,cpp}` — added `enum class
    scene_kind { rope, pendulum_tower, cloth, particle_storm }` plus four
    `build_*` builders. Hot-switchable at runtime via `switch_scene()`. The
    rope builder is preserved **byte-for-byte** to keep the existing CI
    determinism digest (`trace_digest=33a6319d856d4869` at seed 42 / 60 frames)
    untouched.
    - **rope**: original 24-node verlet chain + 32 free particles.
    - **pendulum tower**: four chains (lengths 16 / 12 / 18 / 10), anchored
      across the top at world x = -2.4 / -0.8 / 0.8 / 2.4, each tilted by a
      seeded RNG draw plus alternating ±0.4 rad bias so they swing into each
      other rather than in unison.
    - **cloth**: 12 × 8 grid pinned at the top row, structural h/v constraints
      plus a single alternating-direction shear diagonal per cell with a 4 %
      slack factor so the mesh actually drapes under gravity instead of
      locking up against an 8-iteration solver.
    - **particle storm**: 500 particles orbiting two gravity wells at
      world (-1.2, 0.4) and (1.2, -0.3) with 1/r² + 0.15 m softening, 0.999
      drag per frame, and toroidal wrap on a [-3.5, 3.5] × [-2.5, 2.5] box.
  - `output/ea-cpp-games/apps/sandbox/scene.{h,cpp}` — added per-particle
    motion trails (`kTrailLength = 10`) for the storm/burst visual, mouse
    drag (`grab_nearest_rope_node` / `drag_held_node` / `release_held_node`)
    that pins a node to the cursor while LMB is held and re-syncs the verlet
    `prev_*` on release so the released node carries the right pseudo-velocity,
    and a `spawn_particle_burst` for the right-mouse explosion. Trails and
    interactions are render-only — they never feed `state_digest`, so
    headless determinism is unaffected.
  - `output/ea-cpp-games/apps/sandbox/app.cpp` — full rewrite of the
    renderer:
    - vertical gradient background (#0B1020 → #020308) with a subtle world-grid
      overlay.
    - speed-tinted free particles with halo + core, alpha-ramp motion trails,
      gold anchor squares, cyan-glow dynamic nodes, magenta double-ring on
      the held node, and shadowed text.
    - five-line color-coded HUD: scene title (gold-bold), seed/substeps/speed,
      `wall/sim/drift` (yellow at 50 ms, red at 200 ms), `frame_avg/fps`
      (yellow at 16.67 ms, red at 33.33 ms), and `trace_digest` (magenta when
      the post-`R` digest diverges from the pre-`R` baseline — the visible
      tell for BUG-004).
    - top-right counts panel (`bodies / edges / particles`), bottom-left
      two-line controls hint, and a 240 × 88 frame-budget histogram bottom-right
      with 60 Hz / 30 Hz reference lines.
    - new keys: `1/2/3/4` switch scene, `H` toggles HUD, `T` toggles trails,
      `R` reseeds with same seed (BUG-004 visualization), LMB drag, RMB burst.
  - `output/ea-cpp-games/apps/sandbox/{app,headless,main}.{h,cpp}` —
    new `--scene rope|pendulum|cloth|storm` CLI flag plumbed through both
    interactive and headless modes; `--help` text expanded; headless output
    line now includes `scene=<name>` so digest tables are unambiguous.
  - `output/ea-cpp-games/apps/sandbox/README.md` — documents the four scenes,
    the new keys/flags, and the per-scene determinism digest matrix.
  - **Verified locally** (macOS / AppleClang 17): `--headless --seed 42
    --frames 60` digests for the four scenes are
    `33a6319d856d4869` (rope, **unchanged**),
    `b0b37e5a36eafa6a` (pendulum),
    `ef6340b55f1b9edc` (cloth),
    `968ce23fc350cfaf` (storm).
    All four screenshot captures (`--screenshot show{1..4}.png`) succeed.

- **`--screenshot PATH [--warmup N]` flag on `ea-sandbox`** — runs the
  visual pipeline for N frames (default 120), writes a PNG via raylib's
  `TakeScreenshot`, and exits cleanly. Used for demo capture, slide
  assets, and visual smoke tests. Screenshot mode forces a deterministic
  fixed-step advance (`scene::kFixedStepSeconds`) per rendered frame so
  the captured image always shows physics in motion regardless of how
  raylib's frame timer warms up.
- **Rope initial tilt (35° from vertical)** in `apps/sandbox/scene.cpp`
  so the demo immediately exhibits a visible swing arc — vertical
  initialization previously produced a static rope with no lateral
  perturbation.

### Fixed

- **Sandbox main-thread 100 % CPU spin eliminated — macOS ANR resolved.**
  raylib's `SetTargetFPS()` implements frame limiting as a tight busy-wait
  inside `EndDrawing()` that never yields to Cocoa's NSApplication run loop.
  Even with `FLAG_VSYNC_HINT`, Apple's Metal-over-OpenGL path does not
  actually block in `SwapBuffers` on M-series GPUs, so the busy-wait kept
  the main thread at 100 % CPU and the dock ANR watchdog fired. Fix: remove
  `SetTargetFPS` entirely and replace it with an explicit
  `std::this_thread::sleep_for` after `EndDrawing()` that yields for the
  remainder of the 16.67 ms frame budget. CPU drops from 100 % → ~12 %,
  process state moves from `R` → `S`, and the dock ANR badge no longer
  appears. Headless rope digest at seed 42 / 60 frames still
  `33a6319d856d4869`.

- **Sandbox interactive window flagged "Application Not Responding" on macOS
  even when the event loop was healthy.** The sandbox was a plain CLI binary
  that called `InitWindow` — without an Info.plist declaring
  `NSPrincipalClass=NSApplication`, macOS never promoted the process to a
  full GUI application and the dock ANR watchdog fired aggressively (the
  process showed up as state `RN` at ~100% CPU but the dock badge said
  "Not Responding"). Fix: build the executable as a real `.app` bundle
  on Apple via `MACOSX_BUNDLE TRUE` plus a templated `Info.plist.in`
  (`NSPrincipalClass`, `NSHighResolutionCapable`,
  `NSSupportsAutomaticGraphicsSwitching`, `LSApplicationCategoryType`).
  After the change the process correctly transitions to state `S` while
  blocked on the event loop / vsync — proof it is yielding to NSApp the way
  a real game would. Launch with `open build/apps/sandbox/ea-sandbox.app
  --args --seed 42`. CLI / headless / screenshot still work via
  `ea-sandbox.app/Contents/MacOS/ea-sandbox <flags>`. CI is Ubuntu/Windows
  and is unaffected (`if(APPLE)`-gated). Headless rope digest at seed 42 /
  frames 60 still `33a6319d856d4869`.

- **Sandbox interactive window unresponsive on macOS / dock "Application Not
  Responding".** The HUD ran ~13 `DrawText` calls per frame, and raylib's
  default-font `GetGlyphIndex` is a linear scan over 224 glyphs *per
  character*. In debug builds that dominated the frame, blew past the 16.6 ms
  budget, starved `glfwPollEvents`, and tripped the macOS dock ANR watchdog —
  clicks and keystrokes never serviced. Fix: render the HUD into a
  `RenderTexture2D` once every 6 frames (~10 Hz) and blit the cached texture
  every frame in `output/ea-cpp-games/apps/sandbox/app.cpp`. Verified via
  `sample(1)`: pre-fix top leaves were `GetGlyphIndex` (77 samples) plus
  `DrawText`/`DrawTextEx`/`DrawTextCodepoint` (~75 combined); post-fix all
  text functions are gone from the top hot leaves entirely. Headless rope
  digest at seed 42 / 60 frames still `33a6319d856d4869` (no scene/engine
  change).

- **Demo workspace first-real-build correctness pass.** R3 introduced the
  sandbox executable but configuring + compiling the workspace locally
  surfaced latent issues that R1/R2's CI claims had hidden because the
  pipeline never produced a binary. Verified end-to-end on macOS
  (AppleClang 17, vcpkg 2026.04.27, raylib 6.0):
  - `output/ea-cpp-games/vcpkg.json`: `builtin-baseline` replaced with the
    real `dc8d75cfc3281b8e2a4ed8ee4163c891190df932` (vcpkg tag
    `2026.04.27`); the prior SHA did not exist in the vcpkg history.
  - `output/ea-cpp-games/cmake/Dependencies.cmake`: link to `EASTL` (the
    target the vcpkg `eastl` port actually exports), not `EASTL::EASTL`.
  - `output/ea-cpp-games/include/engine_demo/sim/rng.h` +
    `src/engine_demo/sim/rng.cpp`: switched the engine type from the
    non-existent `eastl::mt19937` to `std::mt19937` and labeled it as a
    Constitution Article 3 interop boundary; BUG-005 (high-32-bit seed
    truncation) is preserved unchanged.
  - `output/ea-cpp-games/src/engine_demo/sim/rng.cpp`: `derive_subseed`
    is referenced only in a comment, so it now carries `[[maybe_unused]]`
    to satisfy `-Wunused-function -Werror`.
  - `output/ea-cpp-games/src/engine_demo/eastl_overrides.cpp`: both EASTL
    `operator new[]` overloads marked `noexcept` — required under
    `-fno-exceptions -Wnew-returns-null` because they may return
    `nullptr` from `posix_memalign` failure.
  - `output/ea-cpp-games/include/engine_demo/ecs/world.h`: `m_alloc`
    member is part of the constitutional allocator-aware contract but
    not used by the fixed-slot implementation; tagged `[[maybe_unused]]`
    to silence `-Wunused-private-field -Werror`.
  - `output/ea-cpp-games/apps/sandbox/app.cpp`: explicit `static_cast` on
    `GetRandomValue` result to silence `-Wsign-conversion`.
  - `output/ea-cpp-games/apps/sandbox/CMakeLists.txt`: macOS link path
    now finds `glfw3` (vcpkg-installed alongside raylib) and links
    Cocoa, IOKit, CoreVideo, CoreFoundation, CoreAudio, AudioToolbox,
    OpenGL frameworks — vcpkg's raylib config does not propagate these.
  - `output/ea-cpp-games/apps/sandbox/README.md`: documented the macOS
    framework block and the requirement that vcpkg be a full (not
    `--depth 1`) clone so the manifest baseline resolves.
  - **Smoke results:** `ea-sandbox --headless --seed 42 --frames 60`
    produces a 61-line CSV with stable digest `fe6723ce9a6c257a`;
    interactive mode opens a 1280×720 window and the rope animates.

### Added — initial sandbox

- **Playable sandbox demo (`apps/sandbox/ea-sandbox`):**
  - `output/ea-cpp-games/apps/sandbox/` — first executable in the demo workspace.
    A raylib-rendered 2D verlet rope plus free-particle scene driven by
    `engine_demo::physics::constraint_solver`, `engine_demo::sim::game_loop`,
    `engine_demo::sim::rng`, and `engine_demo::frame_budget`. Same binary
    supports `--headless --seed S --frames N --out PATH` for CI determinism
    traces. raylib usage is scoped to `apps/sandbox/app.cpp`, labeled interop
    boundary per cpp-snippets rules.
  - HUD surfaces seeded-bug anchors live: BUG-002 (game_loop wall/sim drift),
    BUG-004 (constraint_solver trace digest divergence on reseed),
    BUG-006 (frame_budget rolling-window average).
  - `apps/sandbox/README.md` — controls, flags, bug-visibility cheat sheet.
  - `output/ea-cpp-games/CMakeLists.txt` — new
    `option(ENGINE_DEMO_BUILD_SANDBOX ON)` and guarded `add_subdirectory(apps)`.
  - `output/ea-cpp-games/cmake/Dependencies.cmake` — `find_package(raylib …)`
    guarded by the same option.
  - `output/ea-cpp-games/vcpkg.json` — `raylib` added to dependencies.
  - `engine_demo::physics::constraint_solver::try_get_body(uint64_t)` — minimal
    read-only accessor needed by the renderer; preserves BUG-004 behavior.
  - `.github/workflows/ci-build-demo-workspace.yml` — Ubuntu step now installs
    raylib's X11/GL/asound system deps; new "Sandbox headless smoke" step
    runs `ea-sandbox --headless --seed 42 --frames 60` and asserts the CSV
    line count.
  - "Run the playable sandbox" section in `output/ea-cpp-games/README.md`.

- **R2 remediation (post-R1 adversarial review):**
  - Demo-state strategy section in `docs/delivery-runbook.md` documenting
    per-session branch workflow for incremental bug fixes.
  - T-15 model-availability checklist item in `docs/delivery-runbook.md`.

- **R1 critical remediation (post-rubber-stamp re-audit):**
  - `engine_demo::eastl_allocator_ref` adapter in
    `output/ea-cpp-games/include/engine_demo/allocator.h` — the EASTL-shaped
    reference type the cpp-snippets exemplar and demo-workspace prompts
    already mandated.
  - `output/ea-cpp-games/src/engine_demo/eastl_overrides.cpp` — required
    EASTL global `operator new[]` overrides; without these the demo workspace
    failed to link.
  - `.github/workflows/ci-build-demo-workspace.yml` — first CI job that
    actually configures + builds + tests `output/ea-cpp-games/` under
    Ubuntu and Windows.
  - `.github/workflows/copilot-coding-agent-bootstrap.yml` — the workflow
    Session 08's pre-work-email and facilitator-script reference.
  - `docs/reviews/2026-04-29-full-build-real.md` — honest adversarial review
    cataloguing four Critical findings (C-1..C-4) and nine Significant items
    (S-1..S-9). Replaces the two retracted self-applied reviews.

### Changed

- `.github/workflows/ci-build-demo-workspace.yml`: seeded-bug regression
  guard now uses `GTEST_ALSO_RUN_DISABLED_TESTS=1` env var (was incorrectly
  passing GTest flags as CTest args — guard was non-functional).
- `.github/workflows/ci-spec-kit-validate.yml`: glob corrected from
  `specs/specs/*.md` to `specs/*/spec.md` matching actual directory layout.
- `output/ea-cpp-games/include/engine_demo/frame_budget.h`: removed dead
  `<EASTL/vector.h>` include and misleading comment about allocator wiring.
- `output/ea-cpp-games/specs/constitution.md` Article 1: softened
  `eastl::expected` to "status enum (preferred) or `eastl::expected` where
  the EASTL revision supports it" — reflecting that no committed code uses it.
- `output/ea-cpp-games/CMakePresets.json`: switched from `Ninja Multi-Config`
  to single-config `Ninja` generator so `CMAKE_BUILD_TYPE` is respected.
- `engine_demo::constraint_solver` now stores `eastl_allocator_ref m_alloc`
  and constructs `m_bodies` / `m_constraints` with it, restoring Article 4
  compliance. BUG-004 (hash-map iteration non-determinism) is preserved
  unchanged.
- `output/ea-cpp-games/cmake/Dependencies.cmake` comment corrected to point
  at the real overrides translation unit.
- `docs/reviews/2026-04-29-full-build-pass-{1,2}.md` marked **RETRACTED**
  with pointer to the real review.

### Added — initial bootstrap (kept from prior entries)

- Initial repository bootstrap: `.gitignore`, `.gitattributes`, `.editorconfig`, markdownlint
  and prettier configs, `package.json`, `.vscode/{settings,extensions,mcp}.json`.
- Repo-wide Copilot customization: `.github/copilot-instructions.md`, scoped instruction
  files under `.github/instructions/`, chat modes under `.github/chatmodes/`.
- Full prompt catalog under `.github/prompts/` (Tiers 0–5).
- CI workflows: snippet validation, markdown lint, link check, spec-kit validate,
  coding-agent bootstrap.
- Engagement charter, delivery runbook, feedback toolkit, context belt, build graph,
  escalation paths under `docs/`.
- Session scaffolds under `sessions/{01..09}-*/` (content generated by Tier-3 prompts).
- Factory-overlay placeholders under `factory-overlay/`.
- Snippet-extraction tooling under `tools/`.
- **Demo workspace** under `output/ea-cpp-games/`: full CMake/vcpkg scaffold; `engine_demo`
  library (allocator, frame_budget, ECS world, deterministic RNG, fixed-step game loop,
  constraint solver) with six seeded bugs (BUG-001..006) and two false positives
  (FP-001, FP-002); GoogleTest suite with DISABLED_ regressions; constitution + spec
  skeletons for `lockless-ring-buffer` and `fixed-string`; crash-dump + bug-report
  fixtures.
- **Session bundles** for all nine sessions under `sessions/NN-*/`: facilitator scripts
  (60-min, time-marked, HITL-gated), learner guides, slide outlines, retro micro-surveys,
  pre-work emails, and two exercises per session.
- `.markdownlint.jsonc` MD028 disabled to permit blockquote idioms in facilitator scripts.
- Root `.gitignore` updated to allow committing `output/ea-cpp-games/` while keeping local
  build outputs ignored.
- Two-pass adversarial review of the full build under `docs/reviews/`:
  `2026-04-29-full-build-pass-1.md` (structural) and `2026-04-29-full-build-pass-2.md`
  (C++ + Spec-Kit). Zero Critical findings; Significant findings tracked with
  justifications or follow-up actions.

[Unreleased]: https://github.com/Insight-NA/ea_copilot_workshop
