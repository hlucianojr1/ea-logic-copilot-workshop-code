---
description: Batch analysis-only triage sweep across a list of seeded logic bugs.
mode: agent
model: Claude Sonnet 4.6
tools: [read, search, execute, todo]
inputs:
  - name: bug_ids
    required: true
    description: Space- or comma-separated BUG-XXX identifiers to sweep (e.g., "BUG-002 BUG-006 BUG-010").
  - name: report_path
    required: false
    description: Where to write the triage report.
    default: sessions/03-logic-bugs/sweep-triage-report.md
outputs:
  - path: sessions/03-logic-bugs/sweep-triage-report.md
    kind: file
    overwrite: true
validation:
  - "git status --porcelain output/ea-cpp-games/src returns empty (sweep made no source edits)"
  - "report contains one triage row per requested BUG-XXX"
last_reviewed: 2026-06-19
reviewer: Insight Engagement Lead
---

## Objective

Run the OBSERVE and REPRODUCE phases of the logic-bug loop across a list of `BUG-XXX`
identifiers and emit a single triage table. This is an **analysis-only** sweep: it never
applies a fix.

## Context references

- #file:../../docs/session-03-logic-bugs-runbook.md
- #file:../../.github/skills/logic-bug-triage/SKILL.md
- #file:../../.github/skills/logic-bug-triage/bug-map.md
- #file:../../.github/instructions/cpp-snippets.instructions.md
- #file:../../output/ea-cpp-games/fixtures/seeded-bugs.md

## Pre-conditions

- The `output/ea-cpp-games/` workspace is built and `ctest --preset default-debug` is green.
- The `logic-bug-triage` skill is available in the current surface.
- The provided `bug_ids` all appear in `.github/skills/logic-bug-triage/bug-map.md`.

## Steps

1. Load the `logic-bug-triage` skill and parse `bug_ids` into an ordered list — this gives
   the workflow and per-bug paths once for the whole sweep.
2. For each bug, run **OBSERVE**: read its `fixtures/bug-reports/BUG-XXX.md` and source file,
   then record the symptom, suspected article, and a real-vs-FP verdict (check FP-001/002/003).
3. For each bug, run **REPRODUCE**: enable its `DISABLED_` test, run
   `ctest --preset <preset> --output-on-failure -R <test>`, and record red/green plus the
   failing assertion — then restore the `DISABLED_` prefix so the tree stays clean.
4. Write the triage table to `report_path` (see Output contract). Do not propose fixes.
   > **HITL gate:** Stop here. Fixes for physics (BUG-004) and replay (BUG-008/009) bugs
   > require human sign-off and must be done one at a time via the resolver agent, not in batch.

## Output contract

- Produces exactly one file at `report_path` (default
  `sessions/03-logic-bugs/sweep-triage-report.md`), overwriting any prior run.
- The file contains a Markdown table with one row per requested bug and these columns:
  `Bug | Symptom | Suspected article | Verdict (real/FP) | Reproduces? | Preset`.
- No source, header, or test file under `output/ea-cpp-games/` is modified.
- CHANGELOG entry expected: under `## [Unreleased] → ### Added`, note the generated sweep
  report only if it is committed; transient reports may be left uncommitted.

## Self-validation

- `git status --porcelain output/ea-cpp-games/src output/ea-cpp-games/tests` is empty.
- The report has one triage row for every id in `bug_ids` and no fix diffs are present.
- Re-running with the same `bug_ids` reproduces an identical table (idempotent).

## Failure modes

- **Test left enabled.** If a `DISABLED_` prefix was not restored, the tree is dirty —
  re-add the prefix before finishing.
- **FP mistaken for a bug.** FP-003 (`m_ready` already atomic) is the classic trap; verdict
  must cite the evidence from `bug-map.md`, not a linter warning.
- **Wrong preset.** BUG-007 needs `optimized` and BUG-009 needs `tsan`; under `default-debug`
  they appear green. Use the preset from `bug-map.md`, never assume `default-debug`.
- **Scope creep.** If asked to fix during the sweep, stop and hand off to
  `logic-bug-resolver-lite` or `logic-bug-planner` — this prompt never edits code.
