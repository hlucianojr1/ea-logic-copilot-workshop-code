# Session 01 — Code Comprehension at Scale (learner guide)

## Before you start

- VS Code with GitHub Copilot enabled (Business plan or above).
- This repo cloned; demo workspace at `output/ea-cpp-games/` accessible.
- 5 minutes to skim [`output/ea-cpp-games/specs/constitution.md`](../../output/ea-cpp-games/specs/constitution.md).

## Outcomes

After this session you will be able to:

1. Summarize an unfamiliar subsystem in under 90 seconds using Ask mode + a 3–5-file context belt.
2. Choose Ask mode vs. Edit mode vs. Agent mode deliberately based on the question type.
3. Build a context belt with the four canonical slots (Charter / Interface / Constitution / Mode anchor).

## Walk-through

### 1. Switch to Ask mode

Open Copilot Chat. The panel header shows three tabs: **Ask** / **Edit** / **Agent**. Select the **Ask** tab for all exploration work in this session.

> **Note:** our custom `planner.chatmode.md` is a _chat mode_ (a persona + tool-allowlist file), not the same thing as the Ask tab. Chat modes sit on top of any tab. We'll dig into that distinction in Session 05.

### 2. Ground a generic question with files

Type — exactly:

```text
#file:output/ea-cpp-games/include/engine_demo/ecs/SUBSYSTEM.md
#file:output/ea-cpp-games/include/engine_demo/ecs/world.h
Summarize the responsibilities of this specific ECS world in one paragraph. List the
public invariants. Identify any ambiguity that prevents you from being precise.
```

You should get back a paragraph that names `entity_handle.generation`, the slot pool, and
the `is_alive` invariant. If it stays generic, the `#file:` reference probably didn't
attach — re-paste with the file paths visible in the picker.

### 3. Build a four-slot context belt

For any new comprehension question, attach in this order:

1. **Charter** — `SUBSYSTEM.md` or equivalent design doc.
2. **Interface** — the public header.
3. **Constitution** — `output/ea-cpp-games/specs/constitution.md`.
4. **Mode anchor** — a chat-mode definition that frames Copilot's persona, e.g. `.github/chatmodes/cpp-architect.chatmode.md`.

A fifth slot is acceptable for the most-touched implementation file. Beyond five, return
diminishes; trim before you add.

## Try it yourself

### Exercise 1 — enumerate generation writes

**Goal:** find every code path in `engine_demo::ecs::world` that mutates `slot.generation`.
**Starter file:** `output/ea-cpp-games/src/engine_demo/ecs/world.cpp`.

Suggested prompt:

```text
#file:output/ea-cpp-games/src/engine_demo/ecs/world.cpp
List every code path that writes to slot.generation. Quote the line. One-sentence rationale per path.
```

**Acceptance:** your enumeration matches the file (verify by hand). If Copilot returns 0 sites or 2+ sites, re-grep the file yourself — the truth is one site (in `create_entity`).

<details>
<summary>Hint</summary>

There is exactly one mutation in the seeded code, and the _missing_ mutation is itself a
clue you'll use in Session 04.

</details>

### Exercise 2 — design a component-storage extension

**Goal:** sketch the public API for `engine_demo::ecs::component_storage<T>` without writing implementation.

Suggested prompt:

```text
#file:output/ea-cpp-games/include/engine_demo/ecs/SUBSYSTEM.md
#file:output/ea-cpp-games/include/engine_demo/ecs/world.h
#file:output/ea-cpp-games/specs/constitution.md
Plan only — do not write code. Sketch the public API for component_storage<T> that fits
the existing world. Cite the constitutional articles each design choice satisfies.
```

**Acceptance:** the sketch cites Articles 3 (EASTL-first) and 4 (allocator-aware). If those are missing, ask explicitly "which articles does this satisfy?".

## Troubleshooting

| Symptom                                         | Fix                                                                |
| ----------------------------------------------- | ------------------------------------------------------------------ |
| Ask tab missing                                 | Update the GitHub Copilot Chat extension to the latest version.    |
| `#file:` doesn't resolve                        | Check the path is workspace-relative; absolute paths fail.         |
| Output is generic / no constitutional citations | Re-attach the constitution; it's the lowest-hit file in belts.     |
| Exercise 2 returns implementation code          | Reread the prompt; the literal phrase "Plan only" must be present. |

## Going further

- Read [`docs/ea-context-belt.md`](../../docs/ea-context-belt.md) for nine pre-recipe belts (per session).
- Study the planner tool allowlist in [`.github/chatmodes/planner.chatmode.md`](../../.github/chatmodes/planner.chatmode.md) — this is a custom chat mode persona, separate from the Ask/Edit/Agent product tabs.

## Feedback

[`retro-survey.md`](retro-survey.md). 60 seconds. We read every response.
