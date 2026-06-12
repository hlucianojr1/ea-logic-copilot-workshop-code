---
description: Spec-Kit artifact authoring rules — Constitution, /specify, /plan, /tasks, /implement.
applyTo: "output/**/specs/**,sessions/06-*/**,sessions/07-*/**"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

# Spec-Kit Artifacts — Authoring Rules

Sessions 6 and 7 demonstrate the **GitHub `spec-kit`** flow end-to-end. This file pins the
conventions for the artifacts produced by that flow so the demo is reproducible and the
artifacts can serve as templates for EA's own engineering work.

## Tooling

- We use the upstream `github/spec-kit` CLI (latest stable at engagement start).
- The Constitution, specs, plans, and tasks live under
  `output/ea-cpp-games/specs/{constitution.md, specs/, plans/, tasks/}`.
- The CLI's slash-commands MUST be invoked in this order:
  1. `/constitution` — once, at workspace bootstrap.
  2. `/specify <feature>` — once per feature.
  3. `/plan` — once per feature, after `/specify`.
  4. `/tasks` — once per feature, after `/plan`.
  5. `/implement` — repeatedly, with HITL gate between stages.
- **Never** hand-author files under `tasks/`. They are derived; if they need to change, edit
  the spec or plan and re-run `/tasks`.

## EA Engineering Constitution — required articles

The committed `constitution.md` MUST encode at least these non-negotiables (each as a
numbered article with rationale):

1. **No exceptions / no RTTI** in shipping code paths.
2. **EASTL over std** for containers, strings, smart pointers.
3. **Allocator-aware** containers; no global allocator dependence.
4. **Determinism** in simulation paths; seeded RNG only.
5. **Real-time performance budgets** — frame budgets stated in ms; allocations in inner
   loops are forbidden.
6. **Test-first** for every feature touching simulation invariants.
7. **HITL gates** — `/implement` runs one stage at a time; no auto-progress without human
   approval.
8. **Security** — memory-safety lints (clang-tidy `cppcoreguidelines-*`) gate the merge.

## Spec format

Every `specs/<feature>.md` includes:

- Metadata block: feature id, owner, status, target session, target Copilot plan tier.
- Motivation, success criteria, non-goals.
- Public API sketch (header excerpt, in `cpp` fence — must compile).
- Invariants the implementation must preserve.
- Test contract: list of test files and what each verifies.
- Risk register: known unknowns, allocator concerns, perf concerns.

## Plan format

Stages, each with: name, deliverable, exit criteria, estimated complexity (S/M/L), required
HITL approvals. Stages are numbered and sequential.

## Tasks format

Generated only by `/tasks`. Do not edit by hand. If the file is wrong, edit the plan and
re-run.

## /implement sessions

Each `/implement <stage>` invocation in Session 7 MUST:

- Be invoked from the `builder.chatmode.md` chat mode.
- Pause at the documented HITL gate; the facilitator says "Now we approve…" and shows
  the diff.
- End with `npm run validate:snippets` (or the demo workspace's CMake build) succeeding.

## Forbidden

- Skipping `/constitution` for new features.
- Inlining the spec in chat instead of writing the file.
- Committing partial `tasks/` outputs.
- Auto-running `/implement` over multiple stages without HITL approval between them.
