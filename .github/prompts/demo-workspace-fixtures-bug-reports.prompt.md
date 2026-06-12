---
description: Generate Markdown bug reports keyed to seeded bugs — used as Copilot context in Sessions 3–4.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: output/ea-cpp-games/fixtures/bug_reports/BUG-002-accumulator-drift.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/fixtures/bug_reports/BUG-003-world-uaf.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/fixtures/bug_reports/BUG-004-nondeterministic-solve.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/fixtures/bug_reports/BUG-005-rng-downcast.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/fixtures/bug_reports/BUG-006-rolling-window-off-by-one.md
    kind: file
    overwrite: false
validation:
  - "ls output/ea-cpp-games/fixtures/bug_reports/*.md | wc -l | grep -q 5"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Produce realistic-shaped bug reports — the kind a QA team or producer would file — that
Sessions 3 and 4 hand to Copilot as context for root-cause analysis and fix proposals.

## Context references

- `#file:../../output/ea-cpp-games/fixtures/seeded-bugs.md`

## Steps

For each report:

1. **Title** — short, action-oriented.
2. **Severity** — High / Medium / Low (calibrated per bug).
3. **Reporter** — placeholder ("QA #4271").
4. **Build / rev** — the demo workspace's commit hash placeholder.
5. **Repro steps** — numbered, terse.
6. **Expected behavior** — one sentence.
7. **Actual behavior** — one sentence.
8. **Logs / minidump** — link to `fixtures/crash_dumps/expected/` for BUG-003 only;
   the others document what observable signal made it visible.
9. **Suspected area** — pointer to the source file (but not the bug line — that's the
   exercise).

## Output contract

Five reports exist; each is realistic, short, and points at the right area without giving
the answer.

## Self-validation

```bash
for b in 002 003 004 005 006; do
  test -f output/ea-cpp-games/fixtures/bug_reports/BUG-$b-*.md || exit 1
done
```

## Failure modes

- **Giving away the bug location**: the Suspected area should be the directory or class,
  not the exact line. Sessions are about _Copilot_ finding the bug.
- **Inconsistent severity**: BUG-003 (UAF) is High; BUG-006 (off-by-one in rolling window)
  is Low; calibrate.
