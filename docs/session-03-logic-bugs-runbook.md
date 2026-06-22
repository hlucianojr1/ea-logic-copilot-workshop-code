# Session 03 — Logic Bugs: Delivery Runbook

Artifact catalog and gap-remediation log for the Session 03 bundle. This is the single
index a facilitator or maintainer consults to know what exists, where it lives, and what
state it is in.

## Artifact catalog

### Training documents (`sessions/03-logic-bugs/`)

| Artifact                                                                                   | Purpose                                                         |
| ------------------------------------------------------------------------------------------ | --------------------------------------------------------------- |
| [facilitator-script.md](../sessions/03-logic-bugs/facilitator-script.md)                   | Live 60-min delivery script (BUG-002, BUG-006)                  |
| [learner-guide.md](../sessions/03-logic-bugs/learner-guide.md)                             | Self-paced companion; tutor path + manual path                  |
| [logic-bug-workshop-training.md](../sessions/03-logic-bugs/logic-bug-workshop-training.md) | 150–180 min deep-dive: CoT/ToT/HITL, context layers, all bugs   |
| [sdlc-walkthrough.md](../sessions/03-logic-bugs/sdlc-walkthrough.md)                       | End-to-end AI SDLC loop: issue → agent fix → PR → CI → merge    |
| [qa-track.md](../sessions/03-logic-bugs/qa-track.md)                                       | QA-engineer track: test plans, triage rubric, sign-off, metrics |
| [slides.outline.md](../sessions/03-logic-bugs/slides.outline.md)                           | 13-slide outline                                                |
| [pre-work-email.md](../sessions/03-logic-bugs/pre-work-email.md)                           | T−2 day learner prep                                            |
| [retro-survey.md](../sessions/03-logic-bugs/retro-survey.md)                               | End-of-session micro-survey                                     |
| [fallback-screenshots/](../sessions/03-logic-bugs/fallback-screenshots/README.md)          | Demo-failure recovery captures + checklist                      |

### Exercises (`sessions/03-logic-bugs/exercises/`)

| Exercise                                                                                         | Bug(s)           | Theme                                   |
| ------------------------------------------------------------------------------------------------ | ---------------- | --------------------------------------- |
| [01-test-before-fix.md](../sessions/03-logic-bugs/exercises/01-test-before-fix.md)               | BUG-002          | Test-first discipline                   |
| [02-find-a-third.md](../sessions/03-logic-bugs/exercises/02-find-a-third.md)                     | BUG-004 / FP-002 | Candidate triage                        |
| [03-ub-and-the-optimizer.md](../sessions/03-logic-bugs/exercises/03-ub-and-the-optimizer.md)     | BUG-007          | UB + Debug-vs-Release + HITL gates      |
| [04-bitwise-vs-logical.md](../sessions/03-logic-bugs/exercises/04-bitwise-vs-logical.md)         | BUG-008          | memcmp padding, Tree of Thought         |
| [05-atomic-but-not-ordered.md](../sessions/03-logic-bugs/exercises/05-atomic-but-not-ordered.md) | BUG-009 / FP-003 | Memory ordering + false-positive triage |
| [06-sentinel-trap.md](../sessions/03-logic-bugs/exercises/06-sentinel-trap.md)                   | BUG-010          | CoT vs ToT comparison                   |

### Agents (`.github/agents/`)

The resolver is an **agentic mesh**: an orchestrator entry point delegates to three
single-responsibility sub-agents and reasons with shared CoT/ToT instructions. The
reasoning engine is shared via
[reasoning-cot-tot.instructions.md](../.github/instructions/reasoning-cot-tot.instructions.md),
auto-applied to the orchestrator.

| Agent                                                                                  | Role                                                                                                      |
| -------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------- |
| [logic-bug-orchestrator.agent.md](../.github/agents/logic-bug-orchestrator.agent.md)   | **Entry point** — drives the mesh; delegates to the three sub-agents across four HITL gates (live + SDLC) |
| [code-analysis.agent.md](../.github/agents/code-analysis.agent.md)                     | Read-only OBSERVE-phase data-flow tracer (sub-agent)                                                      |
| [test-runner.agent.md](../.github/agents/test-runner.agent.md)                         | REPRODUCE / VERIFY — enables the `DISABLED_` test, runs the ctest preset twice (sub-agent)                |
| [constitution-checker.agent.md](../.github/agents/constitution-checker.agent.md)       | Read-only FIX-phase 8-article quality gate (sub-agent)                                                    |
| [logic-bug-resolver-lite.agent.md](../.github/agents/logic-bug-resolver-lite.agent.md) | Haiku-tier minimized analyst — routine triage / baseline "confirm clean" checks                           |
| [logic-bug-planner.agent.md](../.github/agents/logic-bug-planner.agent.md)             | Consolidated single-agent sample (no delegation) — one-file contrast, not the mesh                        |
| [logic-bug-tutor.agent.md](../.github/agents/logic-bug-tutor.agent.md)                 | Hint-based self-paced tutor (learner-guide path)                                                          |

### Demo workspace (`output/ea-cpp-games/`)

| Asset                         | Notes                                                                         |
| ----------------------------- | ----------------------------------------------------------------------------- |
| Seeded bugs BUG-001…BUG-010   | Cataloged in `fixtures/seeded-bugs.md`; every bug has a `DISABLED_` test      |
| False positives FP-001…FP-003 | Marked inline in `rng.cpp`, `constraint.cpp`, `event_queue.{h,cpp}`           |
| CMake presets                 | `default-debug`, `optimized` (BUG-007 repro), `tsan` (BUG-009 repro)          |
| `apps/sandbox`                | Visual bug manifestation (rope drift = BUG-002, cloth oscillation = BUG-004)  |
| `tools/worktree-mcp`          | Parallel fix-branch orchestration — used in the SDLC walkthrough ToT-at-scale |

## Gap-remediation log

| Date       | Gap                                                                  | Remediation                                                                                                                                                                                                                    |
| ---------- | -------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| 2026-06-12 | `workshop-guide-advanced.md` referenced but missing                  | Links repointed at `logic-bug-workshop-training.md`                                                                                                                                                                            |
| 2026-06-12 | `logic-bug-tutor` agent referenced by learner guide but absent       | Created `.github/agents/logic-bug-tutor.agent.md`                                                                                                                                                                              |
| 2026-06-12 | `logic-bug-planner` only described inline in training Section 4a     | Created `.github/agents/logic-bug-planner.agent.md`                                                                                                                                                                            |
| 2026-06-12 | `fallback-screenshots/` referenced by facilitator script but missing | Created folder + capture checklist README                                                                                                                                                                                      |
| 2026-06-12 | BUG-007 guard elision not reproducible (Debug-only test preset)      | Added `optimized` (RelWithDebInfo, -O2) configure/build/test presets                                                                                                                                                           |
| 2026-06-12 | BUG-009 data race not demonstrable                                   | Added `tsan` (ThreadSanitizer) configure/build/test presets                                                                                                                                                                    |
| 2026-06-12 | BUG-007/008/009/010 had no hands-on exercises                        | Added exercises 03–06                                                                                                                                                                                                          |
| 2026-06-12 | No end-to-end AI SDLC loop; worktree-mcp and sandbox unused          | Added `sdlc-walkthrough.md` (issue → PR → CI), wired both assets                                                                                                                                                               |
| 2026-06-12 | No QA-engineer track                                                 | Added `qa-track.md` + dual-track markers in facilitator script                                                                                                                                                                 |
| 2026-06-13 | Resolver was a single `logic-bug-planner` agent (no true delegation) | Built the agentic mesh: `logic-bug-orchestrator` + `code-analysis` / `test-runner` / `constitution-checker` sub-agents + `reasoning-cot-tot.instructions.md`; reframed `logic-bug-planner` as the single-agent contrast sample |
