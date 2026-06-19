I'll research the codebase to verify the training document's references before building a verification plan.  

Verify source files and bugs exist

Verify build setup and context files

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/output/ea-cpp-games/CMakePresets.json#1-1), lines 1 to 100

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/output/ea-cpp-games/fixtures/bug-reports)

Searched for files matching `**/.github/agents/*.agent.md`, 2 matches

Searched for files matching `**/.github/chatmodes/*.chatmode.md`, 6 matches

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/package.json)

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/output/ea-cpp-games/specs/constitution.md)

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/output/ea-cpp-games/fixtures/seeded-bugs.md)

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/sessions/03-logic-bugs/logic-bug-workshop-training.md#1-1), lines 1 to 100

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/output/ea-cpp-games/include/engine_demo)

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/output/ea-cpp-games/src/engine_demo)

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/output/ea-cpp-games/tests/engine_demo)

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/output/ea-cpp-games/CMakePresets.json#100-100), lines 100 to 110

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/output/ea-cpp-games)

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/output/ea-cpp-games/AGENTS.md#1-1), lines 1 to 50

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/output/ea-cpp-games/include/engine_demo/sim)

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/output/ea-cpp-games/include/engine_demo/physics)

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/output/ea-cpp-games/src/engine_demo/sim)

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/output/ea-cpp-games/src/engine_demo/physics)

Searched for text `m_accumulator_seconds` (`**/output/ea-cpp-games/include/engine_demo/sim/game_loop.h`), 1 result

Searched for regex `static_cast.*float` (`**/output/ea-cpp-games/src/engine_demo/sim/game_loop.cpp`), 2 results

Searched for regex `m_elapsed_ms.*\+.*delta_ms.*m_elapsed_ms` (`**/output/ea-cpp-games/src/engine_demo/sim/timer.cpp`), 2 results

Searched for text `m_elapsed_ms` (`**/output/ea-cpp-games/include/engine_demo/sim/timer.h`), 3 results

Searched for text `eastl::hash_map` (`**/output/ea-cpp-games/src/engine_demo/physics/constraint.cpp`), 1 result

Searched for text `memory_order_relaxed` (`**/output/ea-cpp-games/src/engine_demo/sim/event_queue.cpp`), 9 results

Searched for text `warmup` (`**/output/ea-cpp-games/src/engine_demo/frame_budget.cpp`), no results

Searched for text `memcmp` (`**/output/ea-cpp-games/src/engine_demo/sim/replay_state.cpp`), 5 results

Searched for text `m_current_index = -1` (`**/output/ea-cpp-games/src/engine_demo/sim/interpolator.cpp`), 1 result

Searched for text `DISABLED_` (`**/output/ea-cpp-games/tests/engine_demo/test_game_loop.cpp`), 1 result

Searched for text `DISABLED_` (`**/output/ea-cpp-games/tests/engine_demo/test_frame_budget.cpp`), 1 result

Searched for text `DISABLED_` (`**/output/ea-cpp-games/tests/engine_demo/test_constraint.cpp`), 1 result

Searched for text `DISABLED_` (`**/output/ea-cpp-games/tests/engine_demo/test_timer.cpp`), 1 result

Searched for text `DISABLED_` (`**/output/ea-cpp-games/tests/engine_demo/test_replay_state.cpp`), 1 result

Searched for text `DISABLED_` (`**/output/ea-cpp-games/tests/engine_demo/test_event_queue.cpp`), 1 result

Searched for text `DISABLED_` (`**/output/ea-cpp-games/tests/engine_demo/test_interpolator.cpp`), 1 result

Searched for text `warmup` (`**/output/ea-cpp-games/include/engine_demo/frame_budget.h`), no results

Searched for text `rolling` (`**/output/ea-cpp-games/include/engine_demo/frame_budget.h`), 2 results

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/output/ea-cpp-games/src/engine_demo/frame_budget.cpp#1-1), lines 1 to 40

All referenced files, tests, presets, and agents exist. Before I finalize the verification plan, a couple of scoping questions: 

Analyzing your answers...

Let me read the remaining portion of the training doc (Section 6d onward + appendix) that was truncated, to make the plan complete. 

Read [](file:///Users/hluciano/projects/ea-logic-copilot-workshop-code/sessions/03-logic-bugs/logic-bug-workshop-training.md#1290-1290), lines 1290 to 1700

I now have full context. Let me save the plan and present it. 

Created memory file [](file:///Users/hluciano/Library/Application%20Support/Code/User/workspaceStorage/32703c21876604bc7659e2cc4f328061/GitHub.copilot-chat/memory-tool/memories/MjJhMjllMWUtOTQ1Ni00NmU5LTk0ZjktYzY3NjJmMmU0NTg2/plan.md)

Here is the verification plan.

## Plan: Verify Session 03 Logic-Bug Training

A dry-run runbook for you (the instructor) to walk logic-bug-workshop-training.md end-to-end on this macOS machine, confirming every Copilot prompt produces the documented reasoning and every command/file reference still resolves. Discovery already confirmed **all files, tests, presets, and both agents exist** — so this plan focuses on *running* each prompt + the build/test loop, and flagging the handful of real risks below.

**What discovery already verified**
- All 7 source/header pairs carry the intended seeded bug; all 7 `DISABLED_` tests exist with the exact names cited.
- constitution.md = exactly 8 articles; seeded-bugs.md catalogs BUG-001..010; bug-reports/ has BUG-002..010.
- Presets `default-debug`, `default-release`, `optimized` (-O2), `tsan` all exist; agents `logic-bug-planner` + `logic-bug-tutor` exist.

**Risks to validate during the run**
- ⚠️ Section 4c tells you to *create* logic-bug-planner.agent.md, but it **already exists** → verify it matches the Section 4a listing; run the exercise as a diff/review, not a create.
- ⚠️ BUG-007's demo (Sec 1B + Sec 6c) only runs `default-debug`, where the guard "works by accident" and the test may **pass instead of reproducing** → reproduce it under the `optimized` preset.
- ⚠️ BUG-009 (data race) may not deterministically fail on Apple Silicon in a normal run → reproduce under the `tsan` preset.
- ⚠️ Pre-built `build/`, `build-optimized/`, `build-tsan/` may be stale CI artifacts → fresh-configure them.

**Steps**

**Phase 0 — Environment & baseline**
1. `npm install`; run `npm run lint` and `npm run links` to validate the doc's markdown/links.
2. In ea-cpp-games: fresh `cmake --preset default-debug` → `cmake --build --preset default-debug` → `ctest --preset default-debug --output-on-failure`. Confirm green and that all `DISABLED_` tests are skipped.
3. Pre-configure `cmake --preset optimized` and `cmake --preset tsan` (needed for BUG-007 / BUG-009).
4. In Copilot, confirm `@logic-bug-planner` is selectable (agent loads).

**Phase 1 — Section 1 live demo (BUG-002, BUG-007)**
5. BUG-002: run the 3 demo prompts (analyze → enable test → fix). Confirm Copilot cites Article 5 and names `float m_accumulator_seconds`. Run the per-bug test loop on `default-debug` (red → fix → green). `git restore` after.
6. BUG-007: run the analyze/fix prompts; reproduce the failing test under **`optimized`** (not default-debug). Verify the guard-elision explanation. `git restore` after.

**Phase 2 — Section 2 walkthrough**
7. Run the 2 info prompts (directory structure, `DISABLED_` pattern); spot-check the answers against the repo and the test-inventory table.

**Phase 3 — Section 3 context layering**
8. Run the BUG-009 three-version comparison (A: no context, B: source only, C: full context) and confirm quality escalates as documented (C cites Article 5 + 6 and disambiguates FP-003). Run the AGENTS.md-summary and EASTL-rationale prompts.

**Phase 4 — Section 4 custom agent**
9. Diff the existing logic-bug-planner.agent.md against the Section 4a listing; note any drift.
10. Run `@logic-bug-planner` on BUG-004, BUG-006, BUG-008; confirm the four-phase output format. Optionally apply + verify each fix via the test loop (`default-debug`), `git restore` between each.

**Phase 5 — Section 5 Tree-of-Thought**
11. Run BUG-004 three-expert prompt, BUG-010 CoT-vs-ToT pair, and the BUG-008 ToT exercise; confirm each converges on the documented root cause.

**Phase 6 — Section 6 HITL**
12. Run the 4-gate BUG-002 sequence, the 4-gate BUG-007 sequence, and the FP-003 false-positive drill on BUG-009 (run its test under `tsan`). Confirm gate verdicts match.

**Phase 7 — Section 7 appendix**
13. No prompts here — fact-check the worked math, struct-layout/offset tables, and EASTL comparison against the actual code.

**Phase 8 — Consolidate**
14. Record per-prompt pass / drift, any command corrections (esp. BUG-007 preset, Sec 4c "create"→"review"), and any expected-output blocks worth refreshing.

**Per-bug exercise loop (reusable)**
Remove `DISABLED_` from the test → `cmake --build --preset <p>` → `ctest --preset <p> -R <name>` (expect **RED**) → apply the documented fix → `ctest` (expect **GREEN**) → `git restore output/ea-cpp-games/`. Presets: BUG-002/004/006/008/010 = `default-debug`; BUG-007 = `optimized`; BUG-009 = `tsan`.

**Relevant files**
- logic-bug-workshop-training.md — the document under test.
- CMakePresets.json — preset names (`default-debug`, `optimized`, `tsan`).
- constitution.md, AGENTS.md — context files attached in prompts.
- logic-bug-planner.agent.md — verify vs Section 4a.
- Source/test pairs under `output/ea-cpp-games/src|include|tests/engine_demo/` — one per bug exercise.

**Verification**
1. `npm run lint` + `npm run links` pass on the training doc.
2. Baseline `ctest --preset default-debug` green with all `DISABLED_` tests skipped.
3. Each bug test flips RED→GREEN under its correct preset, then source restored clean (`git status` clean).
4. Each Copilot prompt yields the documented root cause / Article citation / FP disambiguation (reasoning match, not verbatim).
5. Final findings log lists any doc corrections needed (notably BUG-007 preset and the Sec 4c create-vs-review note).

**Further considerations**
1. Output capture: do you want me to draft a **fill-in results checklist** (one row per prompt with Pass/Drift/Notes) as part of execution, so you can record outcomes as you go? Recommended: yes.
2. If a prompt's expected-output block has clearly drifted from current models, should the follow-up be to (A) just log it, or (B) propose edits to the training doc? Recommend A during this pass, B as a separate follow-up.

This plan is saved to session memory. Want me to adjust scope/ordering, or add the results checklist before you hand off to execution?