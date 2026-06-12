# Session 04 — Proactive Hunting (learner guide)

## Before you start

- Sessions 02 and 03 fixes merged; ctest green; BUG-003, BUG-004, BUG-005 still seeded.
- Read [`factory-overlay/demo-patterns/proactive-issue-hunt.md`](../../factory-overlay/demo-patterns/proactive-issue-hunt.md).

## Outcomes

1. Enumerate candidate defects across a subsystem proactively.
2. Apply the 3-step rubric (Reproduce / Analyze / Decide).
3. Dismiss false positives with one-line code comments.

## Walk-through

### Phase 1 — logic enumeration (ECS)

```text
#file:output/ea-cpp-games/include/engine_demo/ecs/world.h
#file:output/ea-cpp-games/src/engine_demo/ecs/world.cpp
#file:output/ea-cpp-games/specs/constitution.md
Enumerate up to five candidate defects. For each: (a) one-line description, (b) the
constitutional article it most likely violates, (c) the smallest test that would demonstrate it.
```

Pick BUG-003 (missing generation bump). Apply the rubric. Fix-with-test in Edit Mode.

### Phase 2 — security enumeration (RNG)

```text
#file:output/ea-cpp-games/include/engine_demo/sim/rng.h
#file:output/ea-cpp-games/src/engine_demo/sim/rng.cpp
List candidate security-relevant defects (CWE-prefixed if applicable). For each, identify
the smallest input that demonstrates the issue.
```

Pick BUG-005 (CWE-197). Apply rubric. Fix.

### Phase 3 — false-positive triage

For FP-001 (the `derive_subseed` static_cast), use the bit-level walkthrough prompt and write a one-line dismissal comment.

## Try it yourself

- [Exercise 01 — find BUG-004 from cold](exercises/01-find-bug-004.md)
- [Exercise 02 — your own dismissal comment for FP-002](exercises/02-dismiss-fp-002.md)

## Troubleshooting

| Symptom                                  | Fix                                                                       |
| ---------------------------------------- | ------------------------------------------------------------------------- |
| Enumeration returns "no defects found"   | Belt is too narrow; add the constitution + a related implementation file. |
| Copilot doubles down on a false positive | Pivot the question: "what bits/values _actually_ influence the output?"   |
| Triage budget exceeded                   | Write the dismissal comment with current best understanding; move on.     |

## Going further

- Run the enumeration prompt on your day-job code in Plan Mode. Bring findings to office hours.

## Feedback

[`retro-survey.md`](retro-survey.md) **plus** the mid-series checkpoint (separate link in chat).
