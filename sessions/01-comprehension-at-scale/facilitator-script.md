# Session 01 — Code Comprehension at Scale (facilitator script)

> **Cross-references:** [`learner-guide.md`](learner-guide.md) · [`slides.outline.md`](slides.outline.md) · [`retro-survey.md`](retro-survey.md) · [exercises](exercises/)

## Session at a glance

- **Duration:** 60 minutes
- **Level:** Advanced (assumes prior basic Copilot exposure)
- **Prerequisites:** VS Code + Copilot Chat enabled; demo workspace cloned at `output/ea-cpp-games/`; constitution read once.
- **Required Copilot plan:** Business
- **Demo workspace state:** clean checkout; `cmake --preset default-debug` configures.
- **Learner outcomes:**
  1. Use the **Ask mode** + `#file:` references to summarize an unfamiliar subsystem in under 90 seconds.
  2. Build a "context belt" of 3–5 anchor files for any subsystem.
  3. Distinguish when to use Ask mode vs. Edit mode vs. Agent mode for different question types.

## Pre-session checklist (T-15 min)

> **Do:** open `output/ea-cpp-games/include/engine_demo/ecs/world.h` and `SUBSYSTEM.md` in two side-by-side editor groups.
> **Do:** open `specs/constitution.md` in a third tab.
> **Do:** confirm Copilot Chat is in the **Ask** tab (VS Code Copilot Chat panel shows Ask / Edit / Agent across the top).
> **Do:** start the recording / transcript.
> **Watch for:** Copilot Chat may open in Edit or Agent tab after a fresh restart — switch to Ask before learners join.

## Opening (0:00 – 0:05)

> **Say:** "You all already know how to ask Copilot to write code. Today we focus on something subtler and higher-leverage: using Copilot to _understand_ code you didn't write — at the scale your real day-to-day codebases live at."

> **Say:** "By the end of the hour, you'll walk away with a repeatable recipe — what we call a 'context belt' — that you can apply to any unfamiliar subsystem in any of your studios' engines."

> **Do:** show the agenda slide. Three blocks: Ask/Edit/Agent mode primer (10 min), context belts (15 min), live comprehension demo on `engine_demo::ecs` (20 min).

## Block 1: Ask mode vs. Edit mode vs. Agent mode (0:05 – 0:15)

> **Say:** "Ask mode is the exploration tab. It won't edit your files unless you explicitly copy output into an Edit session. That makes it the right tool for comprehension — wide, exploratory questions with no drift risk."

> **Say:** "The three tabs are: **Ask** (exploration, chat), **Edit** (apply multi-file diffs with your approval), **Agent** (autonomous tool-calling, terminal access, multi-step tasks). We'll use Agent mode starting in Session 05. Today: Ask and Edit."

> **Note for facilitator:** our custom `planner.chatmode.md` and `builder.chatmode.md` are _custom chat modes_ we authored — they are not the same as these product tabs. The chat modes add constitution-aware personas and tool constraints on top of the product. We'll explain that distinction in Session 05.

> **Do:** open Copilot Chat in the **Ask** tab. With nothing else attached, type:

```text
Summarize the responsibilities of an entity-component-system world in a real-time game engine.
```

> **Watch for:** the response should be generic. That's the point — it's not grounded yet.

> **Do:** now attach the subsystem doc and the header:

```text
#file:output/ea-cpp-games/include/engine_demo/ecs/SUBSYSTEM.md
#file:output/ea-cpp-games/include/engine_demo/ecs/world.h
Summarize the responsibilities of this specific ECS world in one paragraph. List the
public invariants. Identify any ambiguity that prevents you from being precise.
```

> **Watch for:** the grounded response cites `entity_handle.generation`, the slot-based pool, and the `is_alive` invariant. If it doesn't, rerun once.

> **Say:** "Notice it didn't pretend to be confident about anything not in the files. That's Ask mode with a tight context belt — the constitution we'll talk about in Session 6 makes this repeatable at scale."

## Block 2: The context belt recipe (0:15 – 0:30)

> **Say:** "A context belt is the set of files Copilot needs _to be useful for one specific question_. Three to five files; never more than seven."

> **Do:** show the slide listing the four belt slots: **Charter**, **Interface**, **Constitution**, **Mode anchor**.

> **Do:** demo building a belt for a hypothetical "extend the ECS with a `component_storage<T>` template" question:

```text
#file:output/ea-cpp-games/include/engine_demo/ecs/SUBSYSTEM.md
#file:output/ea-cpp-games/include/engine_demo/ecs/world.h
#file:output/ea-cpp-games/specs/constitution.md
#file:.github/chatmodes/cpp-architect.chatmode.md
Plan only — do not write code. Sketch the public API for component_storage<T> that fits
the existing world. Cite the constitutional articles each design choice satisfies.
```

> **Watch for:** Copilot should cite Articles 3 (EASTL-first) and 4 (allocator-aware) at minimum. If it omits them, ask "which constitutional articles does this design satisfy?" and let it self-correct.

> **HITL gate:** before any participant moves to Edit Mode in their own copy of the workspace, they confirm the plan reads sensibly. Comprehension first, then edit.

## Block 3: Live comprehension demo (0:30 – 0:45)

> **Do:** open `src/engine_demo/ecs/world.cpp` in a fresh editor group.

> **Say:** "We're going to walk every code path that mutates `slot.generation`. There's a comprehension trick here: ask Copilot for an _exhaustive enumeration_, then verify against the file by hand."

```text
#file:output/ea-cpp-games/src/engine_demo/ecs/world.cpp
List every code path in this file that writes to slot.generation. Show me each one as a
quoted line plus a one-sentence rationale.
```

> **Watch for:** Copilot returns exactly one site (in `create_entity`, the zero-to-one initialization). That single result is the seam where Session 04 will diagnose BUG-003.

> **Say:** "If Copilot's enumeration disagrees with what you can verify by hand, **trust the file**. Copilot's job in Plan Mode is to accelerate your understanding, not to be the source of truth."

> **Do:** (optional, if time) repeat the exercise on `frame_budget.cpp`:

```text
#file:output/ea-cpp-games/src/engine_demo/frame_budget.cpp
Walk the lifecycle of a single sample from record_sample to rolling_average. Identify any
off-by-one risk.
```

> **Watch for:** Copilot is likely to flag the wrap-around as suspicious. Don't confirm or deny — that's Session 03 material.

## Q&A (0:45 – 0:55)

Anticipated questions + scripted answers:

- **Q: "How is this different from regular code search?"**
  > **Say:** "Search finds matches. Plan Mode synthesizes across them. The belt is what makes synthesis trustworthy."
- **Q: "Does this work on a 5-million-line codebase?"**
  > **Say:** "Yes — but only if your belt is tight. Five files. Not the whole module. The belt is the discipline."
- **Q: "What about generated code or third-party headers?"**
  > **Say:** "Exclude them from the belt unless the question is _specifically_ about how generated code is used. They burn context budget."

## Retro micro-survey (0:55 – 1:00)

> **Do:** post the link to [`retro-survey.md`](retro-survey.md) in chat.
> **Say:** "Three Likert questions, two free-text. 60 seconds. We read every response — your 'weakest part' answers shape Session 02 directly."

## Stretch goals (skip if behind)

- Live demo of "context belt for a 50-file subsystem" using `engine_demo::sim` + `engine_demo::physics` together.
- Side-by-side Ask mode vs. Agent mode comparison: same prompt, observe how Agent mode invokes file-read tools automatically vs. requiring explicit `#file:` references in Ask mode.

## Recovery script (if a demo fails)

If Copilot Chat returns generic / hallucinated output:

> **Do:** clear the chat, switch to a different model in the picker, re-attach the same `#file:` set, retry once.

If `cmake --preset default-debug` fails on a learner machine:

> **Say:** "We're not building today — comprehension only. Skip the configure; the headers and `.cpp` files are all you need open."

## Post-session checklist (T+15 min)

- Upload recording + transcript to the engagement drive.
- Export retro responses (5-min ETA via the form's CSV download).
- File any "weakest part" themes into the Session 02 prep doc.
- Confirm BUG-001 fixtures are present for next session.
