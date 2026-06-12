# Session 06 — Spec-Kit Mastery, Part 1 (facilitator script)

> **Cross-references:** [`learner-guide.md`](learner-guide.md) · [`slides.outline.md`](slides.outline.md) · [`retro-survey.md`](retro-survey.md) · [exercises](exercises/)

## Session at a glance

- **Duration:** 60 min · **Level:** advanced · **Plan tier:** Business
- **Demo target:** `output/ea-cpp-games/specs/lockless-ring-buffer/` — driven end-to-end with the spec-kit prompt workflow in Copilot Chat: `/constitution → /specify → /plan → /tasks → /implement`.
- **Outcomes:**
  1. Internalize the 5-stage spec-kit flow.
  2. Insert a HITL gate between every `/implement` task.
  3. Trust the constitution as the binding contract.

## Pre-session checklist (T-15 min)

> **Do:** open `output/ea-cpp-games/specs/constitution.md` and `output/ea-cpp-games/specs/lockless-ring-buffer/README.md`.
> **Do:** verify `output/ea-cpp-games/specs/lockless-ring-buffer/` contains only the README skeleton — no `spec.md`, no `plan.md`, no `tasks.md`.
> **Note:** the spec-kit flow uses structured Copilot Chat prompt patterns (`/specify`, `/plan`, `/tasks`, `/implement`). There is **no `npx @github/spec-kit` CLI** — it is not a published npm package. Facilitators type these prompts directly in the Copilot Chat panel.
> **Watch for:** if anyone has run the spec-kit prompts locally, ask them to reset to the skeleton state.

## Opening (0:00 – 0:05)

> **Say:** "Spec-kit is the discipline of saying _what_ before _how_. Today we drive a non-trivial feature — a lockless ring buffer with a published API — through five stages. The constitution we wrote in week one is going to do real work."

## Block 1: /constitution + /specify (0:05 – 0:20)

> **Say:** "We already have `/constitution`. Let's read it as the binding contract before we ask spec-kit to produce a spec."

> **Do:** open `specs/constitution.md`. Read aloud articles 1, 2, 5, 7. These will gate the upcoming `/plan`.

> **Do:** in chat:

```text
/specify A single-producer / single-consumer lockless ring buffer in engine_demo,
allocator-aware, capacity fixed at construction, supporting try_push and try_pop with
non-blocking semantics. The container must satisfy constitutional articles 1, 2, 3, 4.
```

> **Watch for:** Copilot produces `specs/lockless-ring-buffer/spec.md` with a clear API surface and acceptance criteria. If acceptance criteria are vague, ask: "what are the concrete invariants try_push and try_pop must preserve under contention?"

> **HITL gate:** facilitator reads the spec aloud. Confirms: API surface, invariants, observable behavior. If anything is wrong, edit the spec **before** moving on. Spec-kit downstream stages will compound errors.

## Block 2: /plan (0:20 – 0:35)

> **Do:**

```text
/plan
```

> **Watch for:** the plan must cite C++20, EASTL, allocator-awareness, GoogleTest. If it suggests std::atomic without justification, narrow: "atomic ops are fine; std:: containers are not — confirm."

> **HITL gate:** plan reviewed for constitutional fit before tasks are generated.

## Block 3: /tasks + first /implement (0:35 – 0:55)

> **Do:**

```text
/tasks
```

> **Watch for:** tasks are well-sized (~1 PR each). The first task should be the type declaration + skeleton, not a full implementation.

> **Do:** approve the task list, then:

```text
/implement
```

> **HITL gate (the demonstrated practice):** every `/implement` step pauses; we read the diff, run ctest, and **only then** approve. This is the heart of the session.

> **Do:** complete the _first_ task live. Stop there. Sessions 07 finishes the feature.

## Q&A (0:55 – 0:58)

- **Q: "What if the spec is wrong after `/plan`?"** → "Roll back to `/specify`. Spec-kit is idempotent on inputs."
- **Q: "Can I skip the constitution?"** → "You can. You shouldn't. The HITL gates get harder without it."

## Retro micro-survey (0:58 – 1:00)

> **Do:** post [`retro-survey.md`](retro-survey.md).

## Stretch goals

- Manually rewrite one acceptance criterion before `/plan` and observe how the plan changes.

## Recovery script

If `/specify` produces gibberish: re-read the prompt; the most common cause is missing constitutional citation. Re-prompt with an explicit "must satisfy articles X, Y, Z".

## Post-session checklist

- Confirm `specs/lockless-ring-buffer/{spec,plan,tasks}.md` are committed.
- Session 07 begins from the state at end of task 1.
