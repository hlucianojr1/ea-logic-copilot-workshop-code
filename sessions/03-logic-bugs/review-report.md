# Review report — Session 03 SDLC + QA dual-track upgrade

**Reviewer pass:** 1 of 2
**Reviewed at:** 2026-06-04T00:00:00Z
**Diff scope:** uncommitted working tree on `main` (to be moved to
`feat/session03-sdlc-upgrade`)
**Validators:** lint=PASS (touched files; repo-wide MD013 baseline pre-exists),
links=PASS (lychee unavailable locally; relative links verified by script, 0 broken),
snippets=PASS (0 compiled cpp blocks added), prompts=PASS

## Critical findings

1. **Wrong standard citation for signed-overflow UB** —
   `exercises/03-ub-and-the-optimizer.md:38`. The Ask prompt cited `[expr.add]`
   (pointer arithmetic) for signed-integer overflow; the C++20 clause is
   `[expr.pre]p4`. Would teach an EA engineer a wrong citation. **Required fix:**
   replace citation. **Status: FIXED in this pass.**

## Significant findings

None. Verified:

- All four new exercises follow the existing exercise shape (goal, steps, HITL
  gate callouts, acceptance, stretch).
- `facilitator-script.md` retains its required H2 structure and the 60-minute
  block timings are unchanged by the dual-track insertions.
- New agent files carry valid front-matter (`name`, `description`, `tools`).
- No EA-internal IP, no secrets; `sdlc-walkthrough.md` MCP snippet uses
  `${input:repo-root}`.
- `[atomics.order]`/`[intro.races]` citations (exercise 05) and CWE-195
  (exercise 06) verified correct.
- BUG-009 repro claim verified empirically: TSAN reports the race 3/3 with the
  seeded bug, 0/3 with the release/acquire fix; 11/11 suites green under
  `default-debug`, `optimized`, and `tsan` presets.

## Minor findings

1. **Repo-wide MD013 (line ≤ 80) baseline is red** — pre-existing (~1,650
   violations on HEAD, including untouched files); the markdownlint config does
   not match the documented ~100-column convention. Not introduced by this
   change; SHOULD be reconciled in a separate chore.
2. **`lychee` not installed locally** — `npm run links` cannot run; link
   integrity verified by script instead. CI should still run the real checker.

## Informational

- The AppleClang/arm64 TSAN compiler-emitted-`memcpy` false negative discovered
  while making BUG-009 reproducible is itself good teaching material; consider a
  future "trust but verify your sanitizer" segment.
