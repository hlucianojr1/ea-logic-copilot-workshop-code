# Exercise 01 — Build your first context belt

**Time:** 10 minutes · **Difficulty:** beginner

## Goal

Produce a four-slot context belt for `engine_demo::sim::game_loop` and use it to summarize
the subsystem in one paragraph.

## Steps

1. Open Copilot Chat in the **Ask** tab.
2. Identify the four slots:
   - **Charter:** there is no `SUBSYSTEM.md` for sim yet — note this gap.
   - **Interface:** `output/ea-cpp-games/include/engine_demo/sim/game_loop.h`
   - **Constitution:** `output/ea-cpp-games/specs/constitution.md`
   - **Mode anchor:** `.github/chatmodes/planner.chatmode.md`
3. Run:

```text
#file:output/ea-cpp-games/include/engine_demo/sim/game_loop.h
#file:output/ea-cpp-games/specs/constitution.md
#file:.github/chatmodes/planner.chatmode.md
Summarize the responsibilities of this game-loop module in one paragraph. List the public
invariants. Identify any ambiguity that prevents you from being precise.
```

## Acceptance

The summary names the fixed-step accumulator, references Article 5 (determinism) and
Article 6 (real-time budgets), and flags the **missing `SUBSYSTEM.md`** as ambiguity.

## Reflection

Copilot might also flag the `float` accumulator field as suspicious. **Do not act on it yet** — that's Session 03 material. The right Plan-Mode response is to note the suspicion in chat and move on.
