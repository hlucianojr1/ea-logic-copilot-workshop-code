# Session 09 — Multi-Agent Pt 2: Squad Pattern (facilitator script)

> **Cross-references:** [`learner-guide.md`](learner-guide.md) · [`slides.outline.md`](slides.outline.md) · [`retro-survey.md`](retro-survey.md) · [exercises](exercises/)

## Session at a glance

- **Duration:** 60 min · **Level:** advanced · **Plan tier:** **Enterprise**
- **Demo target:** "lockless ring buffer with backpressure policy" (deferred from Session 07 stretch). Decomposed across `squad-coordinator`, `cpp-architect`, `cpp-developer`, `cpp-tester` chat modes. Working dir: `docs/plans/squad-ring-buffer-backpressure/`.
- **Outcomes:**
  1. Run a squad-pattern decomposition: coordinator delegates to 3 specialists.
  2. Observe file-based hand-offs (no in-memory state).
  3. End the workshop on a wide-angle "where do we go from here" beat.

## Pre-session checklist (T-15 min)

> **Do:** confirm `docs/plans/squad-ring-buffer-backpressure/` is empty (or contains only a kickoff stub).
> **Do:** open all four chat modes in tabs: `squad-coordinator.chatmode.md`, `cpp-architect.chatmode.md`, `cpp-developer.chatmode.md`, `cpp-tester.chatmode.md`.
> **Do:** confirm the backpressure spec from Session 07 is committed and final.
> **Watch for:** the squad pattern is an _orchestration pattern_, not a Copilot product — manage expectations at the open.

## Opening (0:00 – 0:05)

> **Say:** "Coding agent did one task. Today we coordinate three specialists on one feature, file-based, HITL-gated. This is a _pattern_, not a feature — you are the orchestrator."

## Block 1: Coordinator decomposition (0:05 – 0:20)

> **Do:** invoke `squad-coordinator.chatmode.md`.

```text
#file:output/ea-cpp-games/specs/lockless-ring-buffer/spec.md
Use the squad-coordinator chat mode. Decompose the backpressure-policy work into three
delegations: one for cpp-architect (API + types), one for cpp-developer (implementation),
one for cpp-tester (regression suite). Write the decomposition to
docs/plans/squad-ring-buffer-backpressure/decisions.md.
```

> **HITL gate:** read the decomposition. The decomposition is the artifact of this stage.

## Block 2: Architect → Developer hand-off (0:20 – 0:40)

> **Do:** invoke `cpp-architect.chatmode.md`.

```text
Use the cpp-architect chat mode. Read decisions.md. Produce
docs/plans/squad-ring-buffer-backpressure/api.md describing the backpressure_policy enum
and the try_push signature changes. Constitution articles 1, 2, 3, 5 must hold.
```

> **HITL gate:** read api.md aloud. Confirm signatures.

> **Do:** invoke `cpp-developer.chatmode.md`.

```text
Use the cpp-developer chat mode. Read api.md and decisions.md. Implement the changes in
include/engine_demo/ring_buffer.h and src/engine_demo/ring_buffer.cpp. Do NOT touch tests.
```

> **HITL gate:** review diff; ctest run (existing tests should still pass).

## Block 3: Tester finalization (0:40 – 0:55)

> **Do:** invoke `cpp-tester.chatmode.md`.

```text
Use the cpp-tester chat mode. Read decisions.md, api.md, and the diff produced by the
developer. Add tests in tests/engine_demo/test_ring_buffer.cpp covering: drop_oldest
preserves capacity, drop_newest rejects when full, spin_until_space respects timeout.
```

> **HITL gate:** ctest green; reviewer chat mode pass.

> **Say:** "Notice nothing here is magic. Each mode is constrained, each hand-off is a file, the orchestration is _us_."

## Q&A + closing (0:55 – 0:58)

> **Say:** "We've covered comprehension, debugging, hunting, context engineering, spec-kit, and multi-agent. The shape of your day-to-day Copilot use should now be: tighter belts, sharper specs, smaller HITL gates. The compounding wins start tomorrow."

- **Q: "Will Copilot ship a real squad orchestrator?"** → "Maybe. The pattern is durable regardless — file-based hand-offs compose well with whatever native orchestration ships."
- **Q: "What's coming next from GitHub?"** → Touch on the horizon areas below.

### Horizon: where the platform is heading

Use this as a 2-minute "what to watch" close. These are public GitHub announcements — no NDA required.

| Area                          | What it is                                                                                          | Why it matters for game engineers                                         |
| ----------------------------- | --------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------- |
| **GitHub Models**             | Marketplace at `github.com/marketplace/models` for trying and comparing LLMs in a playground        | Evaluate model fits (reasoning vs. code) without infrastructure overhead  |
| **Copilot Extensions**        | Published extensions in the GitHub Marketplace that add `@agent-name` participants to Copilot Chat  | Teams can publish internal tools as first-class chat participants         |
| **Native agent coordination** | GitHub is actively shipping improvements to the Coding Agent workflow and may add native multi-step | The squad _pattern_ you built today remains valid; tool glue may simplify |
| **MCP server ecosystem**      | Growing library of published MCP servers (Playwright, databases, CI systems)                        | Swap in EA-internal servers using the `.vscode/mcp.json` pattern from S05 |

> **Say:** "The throughline: everything we built — context belts, instruction files, HITL gates, squad hand-offs — is stable regardless of which new product feature ships next. The discipline travels."

## Retro micro-survey + end-of-series survey (0:58 – 1:00)

> **Do:** post [`retro-survey.md`](retro-survey.md) **and** the end-of-series survey link (5 min, 12 questions, includes NPS and adoption confidence — see `docs/feedback-toolkit.md`).

## Stretch goals

- Run the squad pattern on a feature in your day-job repo. Bring observations to a follow-up.

## Recovery script

If a specialist mode produces work that violates the constitution: do NOT fix in the next mode. Roll back to the offending mode with the constitutional citation and re-prompt. The pattern depends on each mode owning its layer.

## Post-session checklist

- Confirm all squad artifacts committed under `docs/plans/squad-ring-buffer-backpressure/`.
- Pull end-of-series survey responses; package for Bert per `docs/feedback-toolkit.md`.
- Trigger the workshop wrap-up: schedule the post-mortem with Megan within one week.
