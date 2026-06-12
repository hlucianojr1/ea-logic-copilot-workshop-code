# Session 06 — Spec-Kit Mastery, Part 1 (learner guide)

## Before you start

- The spec-kit flow uses Copilot Chat prompt patterns (`/specify`, `/plan`, `/tasks`, `/implement`). No npm install required — `@github/spec-kit` is **not** a published package.
- `output/ea-cpp-games/specs/lockless-ring-buffer/` is at the README-only skeleton state.
- Re-skim `output/ea-cpp-games/specs/constitution.md` articles 1, 2, 3, 4, 5, 7.

## Outcomes

1. Drive a feature through `/constitution → /specify → /plan → /tasks → /implement`.
2. Insert a HITL gate at every stage transition.
3. Refer to the constitution as a binding contract, not a guideline.

## Walk-through

### `/specify`

```text
/specify A single-producer / single-consumer lockless ring buffer in engine_demo,
allocator-aware, capacity fixed at construction, supporting try_push and try_pop with
non-blocking semantics. The container must satisfy constitutional articles 1, 2, 3, 4.
```

Read the produced `spec.md`. **Edit it before continuing** if anything is unclear.

### `/plan`

```text
/plan
```

Validate the plan against the constitution. Atomic operations are fine; `std::` containers are not.

### `/tasks` + first `/implement`

```text
/tasks
/implement
```

After each `/implement` step: read the diff, run `ctest --preset default-debug --output-on-failure`, and only then approve.

## Try it yourself

- [Exercise 01 — rewrite an acceptance criterion](exercises/01-rewrite-acceptance.md)
- [Exercise 02 — drive your own /tasks split](exercises/02-tasks-split.md)

## Troubleshooting

| Symptom                        | Fix                                                     |
| ------------------------------ | ------------------------------------------------------- |
| `/specify` produces gibberish  | Re-prompt with explicit constitutional citations.       |
| `/plan` proposes `std::vector` | Narrow: "constitutional Article 3 — EASTL only".        |
| `/implement` task is too large | Reject; ask `/tasks` to split.                          |
| ctest red after `/implement`   | Roll back the diff (`git restore`); rerun `/implement`. |

## Going further

- Session 07 finishes this feature and adds a second one. Bring the workspace state from this session.

## Feedback

[`retro-survey.md`](retro-survey.md).
