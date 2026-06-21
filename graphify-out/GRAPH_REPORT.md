# Graph Report - .  (2026-06-21)

## Corpus Check
- 178 files · ~88,112 words
- Verdict: corpus is large enough that graph structure adds value.

## Summary
- 742 nodes · 921 edges · 81 communities (65 shown, 16 thin omitted)
- Extraction: 94% EXTRACTED · 6% INFERRED · 0% AMBIGUOUS · INFERRED: 56 edges (avg confidence: 0.82)
- Token cost: 0 input · 0 output

## Community Hubs (Navigation)
- [[_COMMUNITY_Windows Render & App Loop|Windows Render & App Loop]]
- [[_COMMUNITY_Session 03 Bugs & Constitution|Session 03 Bugs & Constitution]]
- [[_COMMUNITY_Game Loop & RNG Tests|Game Loop & RNG Tests]]
- [[_COMMUNITY_Workshop Factory & Concepts|Workshop Factory & Concepts]]
- [[_COMMUNITY_Physics Scene Builders|Physics Scene Builders]]
- [[_COMMUNITY_Sandbox CLI Options|Sandbox CLI Options]]
- [[_COMMUNITY_Crash-Dump MCP Server|Crash-Dump MCP Server]]
- [[_COMMUNITY_Telemetry Event Emission|Telemetry Event Emission]]
- [[_COMMUNITY_Session 03 Facilitation|Session 03 Facilitation]]
- [[_COMMUNITY_Chat Modes & Authoring Rules|Chat Modes & Authoring Rules]]
- [[_COMMUNITY_Root Build Tooling|Root Build Tooling]]
- [[_COMMUNITY_Worktree MCP Package|Worktree MCP Package]]
- [[_COMMUNITY_Crash-Dump MCP Package|Crash-Dump MCP Package]]
- [[_COMMUNITY_Delivery Runbook & Changelog|Delivery Runbook & Changelog]]
- [[_COMMUNITY_Telemetry Header API|Telemetry Header API]]
- [[_COMMUNITY_Review Report & Bug Taxonomy|Review Report & Bug Taxonomy]]
- [[_COMMUNITY_Replay Snapshot Tests|Replay Snapshot Tests]]
- [[_COMMUNITY_MCP TS Config|MCP TS Config]]
- [[_COMMUNITY_Snippet Extractor Tool|Snippet Extractor Tool]]
- [[_COMMUNITY_Worktree TS Config|Worktree TS Config]]
- [[_COMMUNITY_AGENTS & Constitution Rules|AGENTS & Constitution Rules]]
- [[_COMMUNITY_Sandbox Render Tests|Sandbox Render Tests]]
- [[_COMMUNITY_ECS World Lifecycle Tests|ECS World Lifecycle Tests]]
- [[_COMMUNITY_Constraint Solver Bodies|Constraint Solver Bodies]]
- [[_COMMUNITY_Logic-Bug Agents & Workflow|Logic-Bug Agents & Workflow]]
- [[_COMMUNITY_Bug Map & False Positives|Bug Map & False Positives]]
- [[_COMMUNITY_Event Queue Tests|Event Queue Tests]]
- [[_COMMUNITY_Demo App Screenshots|Demo App Screenshots]]
- [[_COMMUNITY_Keyframe Interpolator Tests|Keyframe Interpolator Tests]]
- [[_COMMUNITY_Elapsed Timer Tests|Elapsed Timer Tests]]
- [[_COMMUNITY_Worktree MCP Server|Worktree MCP Server]]
- [[_COMMUNITY_Prompt Conformance Validator|Prompt Conformance Validator]]
- [[_COMMUNITY_QA Track & HITL Gates|QA Track & HITL Gates]]
- [[_COMMUNITY_Frame Budget Tests|Frame Budget Tests]]
- [[_COMMUNITY_Allocator Arena Tests|Allocator Arena Tests]]
- [[_COMMUNITY_Workshop Reset Script|Workshop Reset Script]]
- [[_COMMUNITY_vcpkg Manifest|vcpkg Manifest]]
- [[_COMMUNITY_Allocator Implementation|Allocator Implementation]]
- [[_COMMUNITY_Frame Budget Implementation|Frame Budget Implementation]]
- [[_COMMUNITY_Headless Run Mode|Headless Run Mode]]
- [[_COMMUNITY_Keyframe Interpolator Impl|Keyframe Interpolator Impl]]
- [[_COMMUNITY_Training Verification Log|Training Verification Log]]
- [[_COMMUNITY_Constraint Determinism Test|Constraint Determinism Test]]
- [[_COMMUNITY_World Header|World Header]]
- [[_COMMUNITY_Event Queue Impl|Event Queue Impl]]
- [[_COMMUNITY_engine_demo Build Targets|engine_demo Build Targets]]
- [[_COMMUNITY_Workshop Training Concepts|Workshop Training Concepts]]
- [[_COMMUNITY_Trainer Dry-Run Fixes|Trainer Dry-Run Fixes]]
- [[_COMMUNITY_Allocator Header|Allocator Header]]
- [[_COMMUNITY_EASTL New Overrides|EASTL New Overrides]]
- [[_COMMUNITY_Frame Budget Header|Frame Budget Header]]
- [[_COMMUNITY_Timer Implementation|Timer Implementation]]
- [[_COMMUNITY_Sandbox App Header|Sandbox App Header]]
- [[_COMMUNITY_Sandbox Headless Header|Sandbox Headless Header]]
- [[_COMMUNITY_Win Diag Header|Win Diag Header]]
- [[_COMMUNITY_Event Queue Header|Event Queue Header]]
- [[_COMMUNITY_Game Loop Header|Game Loop Header]]
- [[_COMMUNITY_Interpolator Header|Interpolator Header]]
- [[_COMMUNITY_RNG Header|RNG Header]]
- [[_COMMUNITY_Timer Header|Timer Header]]
- [[_COMMUNITY_Capture Shell Script|Capture Shell Script]]
- [[_COMMUNITY_HITL Facilitator Gate|HITL Facilitator Gate]]
- [[_COMMUNITY_Debug Build Preset|Debug Build Preset]]

## God Nodes (most connected - your core abstractions)
1. `run_interactive()` - 22 edges
2. `cli_options` - 20 edges
3. `Orchestrate Full Build Prompt` - 15 edges
4. `README.md (workshop build system)` - 13 edges
5. `BUG-002 (game-loop accumulator float drift)` - 13 edges
6. `Seeded bugs — engine_demo` - 12 edges
7. `C++ Game Logic Bug Taxonomy` - 12 edges
8. `TEST()` - 11 edges
9. `compilerOptions` - 11 edges
10. `compilerOptions` - 11 edges

## Surprising Connections (you probably didn't know these)
- `Session 03 Training Verification Checklist` --semantically_similar_to--> `Bug Map (engine_demo seeded logic bugs)`  [INFERRED] [semantically similar]
  docs/session-03-training-verification-checklist.md → .github/skills/logic-bug-triage/bug-map.md
- `Hard Constraints (EASTL, no exceptions/RTTI, allocator-aware, HITL)` --semantically_similar_to--> `Workspace Hard Rules (EASTL, no exceptions/RTTI, determinism)`  [INFERRED] [semantically similar]
  .github/skills/logic-bug-triage/SKILL.md → output/ea-cpp-games/AGENTS.md
- `Preset optimized (-O2, BUG-007 repro)` --conceptually_related_to--> `BUG-002 (game-loop accumulator float drift)`  [INFERRED]
  .github/skills/logic-bug-triage/bug-map.md → output/ea-cpp-games/fixtures/bug-reports/BUG-002.md
- `FP-002 (constraint sentinel iteration)` --conceptually_related_to--> `BUG-004 (constraint solver hash-map order non-determinism)`  [INFERRED]
  .github/skills/logic-bug-triage/bug-map.md → output/ea-cpp-games/fixtures/bug-reports/BUG-004.md
- `Analysis Training (verification research log)` --references--> `BUG-002 (game-loop accumulator float drift)`  [INFERRED]
  Analysis_training.md → output/ea-cpp-games/fixtures/bug-reports/BUG-002.md

## Import Cycles
- None detected.

## Hyperedges (group relationships)
- **Squad Specialist Pipeline (architect to developer to tester)** — chatmodes_cpp_architect, chatmodes_cpp_developer, chatmodes_cpp_tester [EXTRACTED 0.90]
- **Planner to Builder to Reviewer Handoff Flow** — chatmodes_planner, chatmodes_builder, chatmodes_reviewer [EXTRACTED 0.90]
- **Logic Bug Resolution Loop shared by three agents** — agents_logic_bug_planner, agents_logic_bug_resolver_lite, agents_logic_bug_tutor, agents_logic_bug_planner_four_phase_workflow [EXTRACTED 0.85]
- **Copilot Workshop Factory Overlay Profile Set** — factory_client_profile_ea_games, factory_domain_profile_games, factory_stack_profile_cpp_game_engine, factory_demo_patterns [EXTRACTED 0.85]
- **Adversarial Review Gating Suite** — review_adversarial, review_cpp_snippets, review_prompt_conformance, review_copilot_plan_gating [EXTRACTED 0.85]
- **Demo Workspace Build Chain (Phase 3)** — demo_workspace_scaffold, demo_workspace_engine_module, demo_workspace_eastl_feature, demo_workspace_fixtures_bug_reports, demo_workspace_instructions_prompts_chatmodes, demo_workspace_agents_md [EXTRACTED 0.85]
- **Session 03 logic-bug resolution loop** — logic_bug_triage_skill, logic_bug_triage_bug_map, logic_bug_triage_four_phase_workflow, ea_cpp_games_constitution [INFERRED 0.85]
- **Security-relevant seeded bugs (CWE)** — bug_003, bug_005, cwe_416_use_after_free, cwe_197_numeric_truncation [INFERRED 0.85]
- **False-positive triage set** — logic_bug_triage_bug_map_fp_001, logic_bug_triage_bug_map_fp_002, logic_bug_triage_bug_map_fp_003 [EXTRACTED 0.75]
- **Eight constitutional articles bind spec-kit flow** — constitution_article_1_no_exceptions, constitution_article_2_no_rtti, constitution_article_3_eastl_first, constitution_article_5_determinism, constitution_article_7_test_first [EXTRACTED 1.00]
- **Session 03 sim-subsystem logic bugs** — bug_reports_bug_007, bug_reports_bug_008, bug_reports_bug_009, bug_reports_bug_010, seeded_bugs [EXTRACTED 1.00]
- **Session 03 exercises map to seeded bugs** — exercises_03_ub_and_the_optimizer, exercises_04_bitwise_vs_logical, exercises_05_atomic_but_not_ordered, exercises_06_sentinel_trap [INFERRED 0.85]
- **Logic-bug resolution loop (observe → reproduce → fix → verify with HITL gates)** — 03_logic_bugs_facilitator_script_observe_reproduce_bisect, 03_logic_bugs_sdlc_walkthrough_logic_bug_planner, 03_logic_bugs_qa_track_four_hitl_gates, 03_logic_bugs_sdlc_walkthrough_sdlc_loop [INFERRED 0.85]
- **C++ game logic bug taxonomy set** — bug_002, bug_004, bug_005, bug_006, bug_007, bug_008, bug_009, bug_010 [EXTRACTED 0.75]
- **False-positive triage targets** — fp_001, fp_002, fp_003 [EXTRACTED 0.75]

## Communities (81 total, 16 thin omitted)

### Community 0 - "Windows Render & App Loop"
Cohesion: 0.05
Nodes (55): Color, HWND, LPARAM, LRESULT, frame_budget, scene_kind, uint64_t, namespace (+47 more)

### Community 1 - "Session 03 Bugs & Constitution"
Cohesion: 0.06
Nodes (43): elapsed_timer (sim/timer.cpp), Signed integer overflow is UB (CWE-190), memcmp on uninitialized padding (CWE-188), replay_snapshot / snapshot_equals (sim/replay_state.cpp), event_slot (sim/event_queue.cpp), memory_order_relaxed insufficient for SPSC sync (CWE-362), keyframe_interpolator (sim/interpolator.cpp), Signed -1 to size_t becomes SIZE_MAX (CWE-195) (+35 more)

### Community 2 - "Game Loop & RNG Tests"
Cohesion: 0.06
Nodes (25): DISABLED_distinct_high_words_yield_distinct_streams, DISABLED_long_run_does_not_drift, engine_demo, TEST(), TEST(), game_loop, game_loop_config, no_steps_below_period (+17 more)

### Community 3 - "Workshop Factory & Concepts"
Cohesion: 0.10
Nodes (34): Bert Sandie EA Source Email, engine_demo Constitution (specs/constitution.md), Copilot Plan-Tier Matrix, EASTL (EA Standard Template Library), engine_demo Synthetic Game Engine, extract-snippets.mjs C++ Snippet Compiler, Copilot Workshop Factory Overlay, Observe/Reproduce/Fix Logic-Bug Loop (+26 more)

### Community 4 - "Physics Scene Builders"
Cohesion: 0.13
Nodes (28): roll_trails(), scene_kind, size_t, uint32_t, uint64_t, add_dynamic_body(), add_edge(), add_pinned_body() (+20 more)

### Community 5 - "Sandbox CLI Options"
Cohesion: 0.11
Nodes (27): scene_kind, telemetry_level, uint32_t, uint64_t, run_mode, cli_options, debug, frames (+19 more)

### Community 6 - "Crash-Dump MCP Server"
Cohesion: 0.12
Nodes (13): server, CdbRunner, extractBetween(), parseAnalyzeOutput(), parseCallStack(), CrashAnalysis, ExceptionRecord, MemoryRegion (+5 more)

### Community 7 - "Telemetry Event Emission"
Cohesion: 0.13
Nodes (21): duration, frame_record, int64_t, uint64_t, physics_record, render_record, crash_signal_handler(), emit_event() (+13 more)

### Community 8 - "Session 03 Facilitation"
Cohesion: 0.17
Nodes (22): Session 03 Facilitator Script — Logic Bugs, Observe → Reproduce → Bisect pattern, Fallback Screenshots README — Session 03, Demo recovery via pre-captured screenshots, Session 03 Learner Guide — Logic Bugs, Green baseline (DISABLED_ seeded regressions), logic-bug-tutor agent (self-guided), Session 03 Pre-work Email (+14 more)

### Community 9 - "Chat Modes & Authoring Rules"
Cohesion: 0.17
Nodes (21): EASTL-First No-std No-exceptions No-RTTI Constraints, Builder Chat Mode, C++ Architect Chat Mode, C++ Developer Chat Mode, C++ Tester Chat Mode, Planner Chat Mode, Reviewer Chat Mode, Critical/Significant/Minor/Informational Severity Rubric (+13 more)

### Community 10 - "Root Build Tooling"
Cohesion: 0.10
Nodes (19): description, devDependencies, markdownlint-cli2, prettier, engines, node, name, private (+11 more)

### Community 11 - "Worktree MCP Package"
Cohesion: 0.11
Nodes (17): dependencies, @modelcontextprotocol/sdk, description, devDependencies, tsx, @types/node, typescript, engines (+9 more)

### Community 12 - "Crash-Dump MCP Package"
Cohesion: 0.11
Nodes (17): dependencies, @modelcontextprotocol/sdk, description, devDependencies, tsx, @types/node, typescript, engines (+9 more)

### Community 13 - "Delivery Runbook & Changelog"
Cohesion: 0.12
Nodes (15): ctest -R substring-match fix, Repo scoped to Session 03 only, Working-directory (cd output/ea-cpp-games) fix, Session 03 Delivery Runbook, Artifact Catalog, apps/CMakeLists (adds sandbox), apps/poc CMakeLists (raylib diagnostic POC), ea-sandbox CMakeLists target (+7 more)

### Community 14 - "Telemetry Header API"
Cohesion: 0.16
Nodes (7): clock, class, telemetry_level, m_level(), now(), scoped_span(), telemetry()

### Community 15 - "Review Report & Bug Taxonomy"
Cohesion: 0.18
Nodes (13): C++ Game Logic Bug Taxonomy, Session 03 Review Report — SDLC + QA dual-track upgrade, Minor finding — repo-wide MD013 baseline red (pre-existing), Critical finding — wrong standard citation for signed-overflow UB, BUG-007 — signed integer overflow UB (CWE-190), BUG-008 — uninitialized padding in memcmp (CWE-188), BUG-009 — insufficient memory ordering (CWE-362), BUG-010 — signed-to-unsigned implicit promotion (CWE-195) (+5 more)

### Community 16 - "Replay Snapshot Tests"
Cohesion: 0.18
Nodes (11): CopiedSnapshotEquals, DifferentValuesNotEqual, DISABLED_padding_does_not_affect_comparison, TEST(), IdenticalSnapshotsSameObject, uint32_t, replay_snapshot, ReplayState (+3 more)

### Community 17 - "MCP TS Config"
Cohesion: 0.15
Nodes (12): compilerOptions, declaration, esModuleInterop, module, moduleResolution, outDir, resolveJsonModule, rootDir (+4 more)

### Community 18 - "Snippet Extractor Tool"
Cohesion: 0.17
Nodes (10): args, BUILD_DIR, EXCLUDE, extractFromContent(), extractOnly, gatherBlocks(), ROOT, SNIPPETS_DIR (+2 more)

### Community 19 - "Worktree TS Config"
Cohesion: 0.15
Nodes (12): compilerOptions, declaration, esModuleInterop, module, moduleResolution, outDir, resolveJsonModule, rootDir (+4 more)

### Community 20 - "AGENTS & Constitution Rules"
Cohesion: 0.20
Nodes (12): AGENTS.md (repo build-system rules), Chat-Mode File Hand-off Convention, Build-System Non-Negotiables, Determinism (Constitution Article 5), engine_demo AGENTS.md (workspace hard rules), Workspace Hard Rules (EASTL, no exceptions/RTTI, determinism), specs/constitution.md (8 articles), engine_demo copilot-instructions (graphify usage) (+4 more)

### Community 21 - "Sandbox Render Tests"
Cohesion: 0.18
Nodes (11): app_cpp_enables_vsync, cmake_links_dwmapi_and_embeds_manifest_on_win32, file_contains(), TEST(), fallback_1280x720_equals_nominal_viewport, nominal_viewport_maps_world_centre_to_screen_centre, nominal_viewport_world_corners_are_distinct_and_on_screen, sandbox_render (+3 more)

### Community 22 - "ECS World Lifecycle Tests"
Cohesion: 0.21
Nodes (10): create_then_destroy_drops_live_count, DISABLED_stale_handle_does_not_revive_after_recycle, create_entity(), destroy_entity(), is_alive(), TEST(), entity_handle, allocator (+2 more)

### Community 23 - "Constraint Solver Bodies"
Cohesion: 0.20
Nodes (10): body, distance_constraint, allocator, uint32_t, uint64_t, add_body(), add_constraint(), constraint_solver() (+2 more)

### Community 24 - "Logic-Bug Agents & Workflow"
Cohesion: 0.31
Nodes (10): Logic Bug Planner Agent, EA Engineering Constitution (8 articles), False Positives FP-001/FP-002/FP-003, Observe-Reproduce-Fix-Verify Four-Phase Workflow, HITL Approval Gate, Test-First Discipline (enable DISABLED_ test before fix), Logic Bug Resolver (Lite) Agent, logic-bug-triage Skill (+2 more)

### Community 25 - "Bug Map & False Positives"
Cohesion: 0.25
Nodes (9): BUG-003 (ECS handle reuse UAF / CWE-416), BUG-004 (constraint solver hash-map order non-determinism), BUG-005 (RNG seed downcast / CWE-197), CWE-197 Numeric Truncation, CWE-416 Use-After-Free, Bug Map (engine_demo seeded logic bugs), FP-001 (rng seed XOR widening, not truncation), FP-002 (constraint sentinel iteration) (+1 more)

### Community 26 - "Event Queue Tests"
Cohesion: 0.25
Nodes (7): ConsumeOnlyOnce, ConsumeWithoutPublishReturnsFalse, DISABLED_consumer_observes_complete_payload, TEST(), EventSlot, PublishAndConsumeSingleThread, ResetClearsSlot

### Community 27 - "Demo App Screenshots"
Cohesion: 0.32
Nodes (8): Seeded bug markers BUG-002 BUG-004 BUG-006, Keyboard/mouse control legend, ENGINE_DEMO physics showcase application, Frame budget graph 16.67ms avg (60Hz), HUD telemetry overlay (seed, substeps, timing, trace_digest), ENGINE_DEMO rope showcase screenshot, Rope verlet constraint scene, Sim stats bodies=24 edges=23 particles=32

### Community 28 - "Keyframe Interpolator Tests"
Cohesion: 0.29
Nodes (6): AddAndStartPlayback, AdvanceThroughKeyframes, CapacityLimit, DISABLED_unstarted_does_not_read_oob, TEST(), KeyframeInterpolator

### Community 29 - "Elapsed Timer Tests"
Cohesion: 0.29
Nodes (6): DISABLED_overflow_guard_not_elided, ElapsedTimer, TEST(), MultipleLargeTicks, ResetClearsAccumulator, TickAccumulatesTime

### Community 30 - "Worktree MCP Server"
Cohesion: 0.29
Nodes (5): server, BuildResult, exec, TestResult, WorktreeInfo

### Community 31 - "Prompt Conformance Validator"
Cohesion: 0.29
Nodes (4): findings, ROOT, TARGETS, wantJson

### Community 32 - "QA Track & HITL Gates"
Cohesion: 0.33
Nodes (6): Dual-track session (Developer + QA), Session 03 QA Track — Verifying Logic-Bug Fixes, Four HITL gates (QA sign-off authority), Headless trace comparison (quantitative regression metric), Triage rubric — real bug vs false positive, FP-001 — seed function false positive (narrow-widen via XOR)

### Community 33 - "Frame Budget Tests"
Cohesion: 0.40
Nodes (5): average_over_two_samples, DISABLED_first_sample_is_not_double_counted_on_warmup, TEST(), frame_budget, single_sample_returns_that_sample

### Community 34 - "Allocator Arena Tests"
Cohesion: 0.40
Nodes (5): basic_allocation_returns_aligned_pointer, DISABLED_third_aligned_alloc_does_not_overrun_arena, TEST(), exhaustion_returns_null, allocator

### Community 35 - "Workshop Reset Script"
Cohesion: 0.60
Nodes (5): fail(), ok(), step(), warn(), reset_workshop.sh script

### Community 36 - "vcpkg Manifest"
Cohesion: 0.33
Nodes (5): builtin-baseline, dependencies, description, name, version-string

### Community 37 - "Allocator Implementation"
Cohesion: 0.60
Nodes (5): align_up(), allocate(), allocator(), deallocate(), size_t

### Community 38 - "Frame Budget Implementation"
Cohesion: 0.33
Nodes (3): frame_budget(), allocator, size_t

### Community 39 - "Headless Run Mode"
Cohesion: 0.40
Nodes (5): headless_result, scene_kind, uint32_t, uint64_t, run_headless()

### Community 41 - "Training Verification Log"
Cohesion: 0.40
Nodes (5): Analysis Training (verification research log), Per-Bug Preset & Reproduction Map, Session 03 Training Verification Checklist, Preset optimized (-O2, BUG-007 repro), Preset tsan (ThreadSanitizer, BUG-009 repro)

### Community 42 - "Constraint Determinism Test"
Cohesion: 0.40
Nodes (4): constraint_solver, DISABLED_solve_is_deterministic_across_construction_orders, TEST(), two_body_distance_constraint_converges

### Community 43 - "World Header"
Cohesion: 0.40
Nodes (4): engine_demo(), class, world(), namespace

### Community 44 - "Event Queue Impl"
Cohesion: 0.50
Nodes (3): event_payload, publish(), try_consume()

### Community 45 - "engine_demo Build Targets"
Cohesion: 0.40
Nodes (5): engine_demo source tree CMakeLists, engine_demo library target, engine_demo tests CMakeLists, engine_demo test targets (GTest), third_party — vendored dependencies (EASTL pin)

### Community 46 - "Workshop Training Concepts"
Cohesion: 0.67
Nodes (3): Logic Bug Workshop Training — instructor deep-dive, Human-in-the-Loop (HITL), Tree of Thought (ToT)

### Community 47 - "Trainer Dry-Run Fixes"
Cohesion: 0.67
Nodes (3): BUG-006 test strengthened (3-sample), BUG-008 test rewritten for Apple Silicon (sret), Session 03 Trainer Dry-Run Fixes

## Knowledge Gaps
- **264 isolated node(s):** `va_list`, `frame_budget`, `trigger_time`, `duration`, `trigger_time` (+259 more)
  These have ≤1 connection - possible missing edges or undocumented components.
- **16 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `C++ Game Logic Bug Taxonomy` connect `Review Report & Bug Taxonomy` to `QA Track & HITL Gates`, `Session 03 Bugs & Constitution`, `Session 03 Facilitation`, `Workshop Training Concepts`, `Bug Map & False Positives`?**
  _High betweenness centrality (0.016) - this node is a cross-community bridge._
- **Why does `FP-003 — m_ready is atomic; ordering is the real bug` connect `Session 03 Bugs & Constitution` to `Review Report & Bug Taxonomy`?**
  _High betweenness centrality (0.014) - this node is a cross-community bridge._
- **Are the 10 inferred relationships involving `run_interactive()` (e.g. with `platform_dwm_flush()` and `platform_win_diag_frame()`) actually correct?**
  _`run_interactive()` has 10 INFERRED edges - model-reasoned connections that need verification._
- **Are the 4 inferred relationships involving `BUG-002 (game-loop accumulator float drift)` (e.g. with `Analysis Training (verification research log)` and `BUG-004 (constraint solver hash-map order non-determinism)`) actually correct?**
  _`BUG-002 (game-loop accumulator float drift)` has 4 INFERRED edges - model-reasoned connections that need verification._
- **What connects `va_list`, `frame_budget`, `trigger_time` to the rest of the system?**
  _276 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Windows Render & App Loop` be split into smaller, more focused modules?**
  _Cohesion score 0.052403846153846155 - nodes in this community are weakly interconnected._
- **Should `Session 03 Bugs & Constitution` be split into smaller, more focused modules?**
  _Cohesion score 0.06201550387596899 - nodes in this community are weakly interconnected._