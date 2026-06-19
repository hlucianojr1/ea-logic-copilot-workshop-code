---
name: logic-bug-triage
description: >-
  Observe → reproduce → fix → verify workflow for a single seeded logic bug in the
  engine_demo C++20 game-engine workspace under output/ea-cpp-games/. Use when resolving or
  triaging a BUG-XXX defect, enabling a DISABLED_ regression test, or checking a candidate
  against the constitution and the FP-001/FP-002/FP-003 false positives. Packages the rules,
  ctest preset commands, and per-bug file map so a lower-cost model can run the loop reliably.
---

# Logic Bug Triage

This skill carries the full logic-bug workflow so a lightweight agent (or a cheaper model)
can resolve a seeded `BUG-XXX` in `output/ea-cpp-games/` without re-deriving the rules each
time. Follow the four phases in order. Do not skip the reproduce step.

## Context to read first

- `output/ea-cpp-games/AGENTS.md` — workspace hard rules.
- `output/ea-cpp-games/specs/constitution.md` — the 8 non-negotiable articles.
- [`bug-map.md`](./bug-map.md) — per-bug source file, header, `DISABLED_` test, and ctest
  preset. Load it when you need the exact paths for a specific `BUG-XXX`.

## Hard constraints

1. **No std:: containers** in committed code — use EASTL equivalents.
2. **No exceptions, no RTTI** — the workspace compiles with `-fno-exceptions -fno-rtti`.
3. **Allocator-aware** — every container takes an explicit `engine_demo::allocator`.
4. **Test-first** — enable the `DISABLED_` regression test BEFORE proposing any fix.
5. **HITL gate** — pause for explicit human approval before editing any file.
6. **Minimal diffs** — change only what the fix requires; never refactor adjacent code.

## Four-phase workflow

### Phase 1: OBSERVE

- Read the bug report at `output/ea-cpp-games/fixtures/bug-reports/BUG-XXX.md` and the
  implicated source file plus its header (see [`bug-map.md`](./bug-map.md)).
- State the symptom in one sentence and name the constitutional article(s) at risk.
- Check the candidate against FP-001 (rng seed), FP-002 (constraint sentinel), and
  FP-003 (`m_ready` is already atomic) before declaring it a real bug.

### Phase 2: REPRODUCE

- Find the matching `DISABLED_` test in `output/ea-cpp-games/tests/engine_demo/` and remove
  the `DISABLED_` prefix.
- Run the test with the preset listed for that bug in [`bug-map.md`](./bug-map.md):
  `ctest --preset <preset> --output-on-failure -R <test_name>`.
- Report whether it fails and why. If it does not fail, stop — do not proceed to a fix.

### Phase 3: FIX (HITL gate — wait for approval)

- Propose the minimal fix and cite the satisfied constitutional articles, one by one.
- Wait for explicit human approval, then apply the fix.

### Phase 4: VERIFY

- Rerun the single test, then the full suite:
  `ctest --preset default-debug --output-on-failure`.
- Report any collateral failures. A fix that breaks another test is not done.

## Output format

For each phase, output exactly:

```text
## Phase N: <PHASE_NAME>
**Action:** <what you did>
**Result:** <what happened>
**Constitutional compliance:** <articles checked>
```
