# Session 04 — Bug & Defect Fixing: Proactive Hunting (facilitator script)

> **Cross-references:** [`learner-guide.md`](learner-guide.md) · [`slides.outline.md`](slides.outline.md) · [`retro-survey.md`](retro-survey.md) · [exercises](exercises/)

## Session at a glance

- **Duration:** 60 min · **Level:** advanced · **Plan tier:** Business
- **Demo state:** Sessions 02–03 fixes merged; BUG-003, BUG-004, BUG-005 + FP-001, FP-002 still in tree.
- **Outcomes:**
  1. Use Copilot to **enumerate candidate defects** across a subsystem proactively.
  2. Apply the 3-step triage rubric: **Reproduce / Analyze / Decide**.
  3. Confidently dismiss false positives with a one-line code comment.

## Pre-session checklist (T-15 min)

> **Do:** open `src/engine_demo/ecs/world.cpp`, `src/engine_demo/sim/rng.cpp`, and `src/engine_demo/physics/constraint.cpp`.
> **Do:** load `factory-overlay/demo-patterns/proactive-issue-hunt.md` as facilitator reference.
> **Do:** confirm the candidate-enumeration prompt produces **at least one** false positive — if Copilot only surfaces real bugs, we lose the FP-triage moment.

## Opening (0:00 – 0:05)

> **Say:** "Reactive bug fixing is table stakes. Proactive hunting — where you go _looking_ for defects before customers do — is where Copilot becomes a force multiplier. The cost is false positives. The skill is dismissing them quickly."

> **Do:** show agenda. Phase 1: logic-bug enumeration (15 min). Phase 2: security-bug enumeration (15 min). Phase 3: false-positive triage (20 min). 5 min Q&A.

## Block 1: Logic-bug enumeration on the ECS (0:05 – 0:20)

> **Do:** **Ask** tab:

```text
#file:output/ea-cpp-games/include/engine_demo/ecs/world.h
#file:output/ea-cpp-games/src/engine_demo/ecs/world.cpp
#file:output/ea-cpp-games/specs/constitution.md
Enumerate up to five candidate defects in this file. For each: (a) one-line description,
(b) the constitutional article it most likely violates, (c) the smallest test that would
demonstrate it.
```

> **Watch for:** BUG-003 (missing generation bump on destroy) appears in the top three. If Copilot misses it, narrow with: "Examine destroy_entity. What invariant on slot.generation must hold for is_alive to be sound?"

> **Do:** triage live with the rubric:
>
> 1. **Reproduce** — write the failing test (`DISABLED_stale_handle_does_not_revive_after_recycle` already exists; just enable it).
> 2. **Analyze** — read the data flow: `destroy_entity → slot.alive=false → create_entity reuses slot at same generation → stale handle validates`.
> 3. **Decide** — real bug. Fix-with-test using the **Edit** tab.

```text
#file:output/ea-cpp-games/src/engine_demo/ecs/world.cpp
#file:output/ea-cpp-games/tests/engine_demo/test_world.cpp
Fix BUG-003: destroy_entity must increment slot.generation. Re-enable
DISABLED_stale_handle_does_not_revive_after_recycle. Constitutional articles 1, 2 must hold.
```

> **HITL gate:** ctest green; reviewer chat mode pass.

## Block 2: Security-bug enumeration on RNG + constraint solver (0:20 – 0:35)

> **Say:** "Security bugs are a category of logic bug with sharper consequences. We use the same enumeration prompt, but pivot the article it violates."

> **Do:** **Ask** tab:

```text
#file:output/ea-cpp-games/include/engine_demo/sim/rng.h
#file:output/ea-cpp-games/src/engine_demo/sim/rng.cpp
List candidate security-relevant defects (CWE-prefixed if applicable). For each, identify
the smallest input that demonstrates the issue.
```

> **Watch for:** BUG-005 (CWE-197 seed downcast) surfaces. Copilot may _also_ flag `derive_subseed` as suspicious — that's our FP-001.

> **Do:** apply rubric to BUG-005: real → fix-with-test:

```text
#file:output/ea-cpp-games/src/engine_demo/sim/rng.cpp
Fix BUG-005: route the uint64 seed through derive_subseed to preserve full-width entropy
under engine seeding. Re-enable DISABLED_distinct_high_words_yield_distinct_streams.
```

## Block 3: False-positive triage (0:35 – 0:55)

> **Say:** "Now the high-leverage skill: dismissing FP-001."

> **Do:** **Ask** tab, focused belt:

```text
#file:output/ea-cpp-games/src/engine_demo/sim/rng.cpp
The static_cast<uint32_t> in derive_subseed looks like truncation. Walk the bit-level
math: what is the value of the result for seed=0xDEADBEEFCAFEBABE? Is information lost?
```

> **Watch for:** Copilot reasons through the XOR-fold and concludes "no information lost in the sense the caller cares about". If it doubles down on FP-001, ask "what bits of seed influence the output?" and let it self-correct.

> **Do:** **Edit** tab:

```text
#file:output/ea-cpp-games/src/engine_demo/sim/rng.cpp
Append a one-line comment immediately above derive_subseed's static_cast explaining why
it is NOT a truncation defect (it XOR-folds the high half before passing). Cite the
analysis above.
```

> **HITL gate:** the comment is the artifact. Review before commit.

> **Do:** repeat for FP-002 (sentinel iteration in constraint_solver) — same shape, abbreviated.

## Q&A (0:55 – 0:58)

- **Q: "How do I keep this from becoming a flood of FPs?"** → "Triage budget: 15 minutes per candidate, max. If undecidable in 15, write the dismissal comment and move on."

## Retro micro-survey (0:58 – 1:00) + mid-series checkpoint

> **Do:** post [`retro-survey.md`](retro-survey.md). Note: Session 04 also opens the **mid-series checkpoint** survey (3 min, captured in `docs/feedback-toolkit.md`). Read both links aloud.

## Stretch goals

- Run the enumeration prompt on the constraint solver, surface BUG-004, fix it.

## Recovery script

If Copilot won't surface BUG-003: feed `git diff` of recent commits + the test file. Sometimes Copilot needs a nudge toward "what changed recently?".

## Post-session checklist

- Confirm BUG-003 and BUG-005 fixes merged.
- Pull mid-series checkpoint responses; flag for Megan.
