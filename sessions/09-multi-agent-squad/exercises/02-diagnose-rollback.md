# Exercise 02 — Diagnose a roll-back

**Time:** 15 min · **Difficulty:** advanced

## Goal

Deliberately introduce a constitutional violation in the architect's `api.md` (e.g., a `std::vector` parameter). Observe the cascade. Roll back to the architect; re-prompt with the constitutional citation; verify clean re-run.

## Steps

1. Edit `api.md` to swap the EASTL container for `std::vector`.
2. Run developer mode. Observe the violation propagating.
3. Stop. Roll back to architect mode with: "Article 3 forbids std:: containers. Re-issue api.md."
4. Re-run developer + tester.

## Acceptance

The final state has no `std::` containers; all four artifact files are in sync.

## Reflection

Roll-back protects the squad's value: each mode's output must be trustable by the next. The constitution is the trust contract.
