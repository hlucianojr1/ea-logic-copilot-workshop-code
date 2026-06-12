# Session 09 — Multi-Agent Squad Pattern (learner guide)

## Before you start

- Sessions 06–07 backpressure spec is committed and final.
- `docs/plans/squad-ring-buffer-backpressure/` is empty (or skeleton only).
- Skim all four chat modes: `squad-coordinator`, `cpp-architect`, `cpp-developer`, `cpp-tester`.

## Outcomes

1. Run a squad-pattern decomposition end-to-end.
2. Observe file-based hand-offs between modes.
3. Identify when to roll back vs. when to proceed.

## Walk-through

### Coordinator

```text
Use the squad-coordinator chat mode. Decompose the backpressure-policy work into three
delegations. Write the decomposition to docs/plans/squad-ring-buffer-backpressure/decisions.md.
```

### Architect → Developer

```text
Use the cpp-architect chat mode. Produce api.md.
```

```text
Use the cpp-developer chat mode. Implement against api.md. Do NOT touch tests.
```

### Tester

```text
Use the cpp-tester chat mode. Add the regression suite covering each backpressure policy.
```

## Try it yourself

- [Exercise 01 — squad on a different task](exercises/01-different-task.md)
- [Exercise 02 — diagnose a roll-back](exercises/02-diagnose-rollback.md)

## Troubleshooting

| Symptom                                    | Fix                                                           |
| ------------------------------------------ | ------------------------------------------------------------- |
| Specialist works outside its layer         | Stop. Re-invoke that mode with the layer constraint repeated. |
| Coordinator re-decomposes mid-stream       | Treat as roll-back; commit and re-coordinate.                 |
| Tests added without coverage of new policy | The tester mode missed a delegation — re-prompt with explicit |
|                                            | reference to the decomposition's tester scope.                |

## Going further

- The squad pattern is repo-agnostic. Apply it to a feature in your day-job code in the next two weeks; bring observations to office hours.

## Feedback

[`retro-survey.md`](retro-survey.md) **plus** the end-of-series survey (5 min, separate link in chat).
