# Exercise 02 — Find a third logic bug

**Time:** 15 min · **Difficulty:** advanced

## Goal

Without consulting the seeded-bugs catalog, have Copilot surface candidate logic defects in
`engine_demo::physics::constraint_solver`, then triage them: find the **real** bug (BUG-004,
non-determinism) and dismiss the **false positive** (FP-002, sentinel iteration).

> 🔧 **Setup** — start from a clean baseline. Paste into the **Agent** panel:

```text
@logic-bug-planner
Confirm output/ea-cpp-games/ is clean for the constraint solver: ctest --preset default-debug
is green and solve_is_deterministic_across_construction_orders is still DISABLED_.
Run ./reset_workshop.sh if not. Do not fix anything.
```

## Concept — surfacing vs. triaging

An AI can _list_ suspicious code all day; the engineering skill is **triage** — separating a
real defect from a benign pattern. A real bug needs a **failing test**; a false positive needs
a **one-line justification** for dismissal. You will produce both artifacts here.

## Steps

1. **Ask** tab — surface candidates:

   ```text
   #file:output/ea-cpp-games/include/engine_demo/physics/constraint.h
   #file:output/ea-cpp-games/src/engine_demo/physics/constraint.cpp
   #file:output/ea-cpp-games/specs/constitution.md
   List up to five candidate logic defects in this file. For each: (a) reproduce in <5 lines,
   (b) trace data flow, (c) cite the constitutional article it violates.
   ```

2. Triage each candidate against this rubric:

   | Verdict        | Evidence required                                          |
   | -------------- | ---------------------------------------------------------- |
   | Real bug       | A minimal failing test (or a re-enabled `DISABLED_` test)  |
   | False positive | A one-line code comment explaining why the pattern is safe |

3. Confirm the real bug by enabling its test:

   ```bash
   cd output/ea-cpp-games
   cmake --build --preset default-debug
   ctest --preset default-debug --output-on-failure -R constraint
   ```

   `solve_is_deterministic_across_construction_orders` fails — hash-map traversal order
   leaks into the result (BUG-004, Article 5).

4. Dismiss the false positive in writing: FP-002's constraint loop **looks** like it reads
   past the end, but it iterates to a sentinel and never dereferences the buffer.

## What good looks like

- Copilot's list includes the non-determinism (BUG-004) with a constitution-article citation.
- You produced a **failing test** for BUG-004 and a **one-sentence dismissal** for FP-002 —
  two different artifacts for two different verdicts.

## Common pitfalls

- **Treating every flagged line as a bug.** The list is hypotheses, not verdicts.
- **Dismissing without evidence.** "Looks fine" is not a dismissal; name _why_ the sentinel
  iteration is safe.
- **Wrong `-R` filter.** Use the binary name (`-R constraint`), not a GTest case substring.

## Acceptance

You identify BUG-004 (non-determinism via hash-map order) **and** correctly dismiss FP-002
(the sentinel-iteration false alarm), each with the right artifact.

## Reflection

Triage — real bug vs. false positive — is the core skill Session 04 builds on. You are
previewing it deliberately.
