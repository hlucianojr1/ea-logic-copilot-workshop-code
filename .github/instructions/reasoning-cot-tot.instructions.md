---
description: Chain-of-Thought + Tree-of-Thought reasoning strategy for the Agentic Logic Bug Resolver (the diagram's Reasoning Engine).
applyTo: ".github/agents/logic-bug-orchestrator.agent.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

# Reasoning Engine — Chain-of-Thought & Tree-of-Thought

This file is the **Reasoning Engine** box of the Agentic Logic Bug Resolver diagram. The
orchestrator links to it from its body and applies these strategies in the FIX phase, after
the `code-analysis` sub-agent has returned a data-flow trace and before any edit is made.
The Reasoning Engine is **not a separate agent** — it is a discipline the orchestrator runs.

## When to use which

- **Chain-of-Thought (CoT)** — the default for a _narrow_ defect with one obvious mechanism
  (an off-by-one, a missing warmup guard, a sign mistake). Reason in a single ordered chain:
  trace → mechanism → minimal fix → predicted test effect.
- **Tree-of-Thought (ToT)** — switch on when the symptom admits **two or more plausible
  mechanisms**, or when a candidate fix risks violating an article (determinism, allocator,
  EASTL). Branch the hypotheses, score each, prune, then commit to one.

## Chain-of-Thought template

```text
1. Restate the symptom in one sentence (from the Code Analysis Report).
2. Trace: <decl> → <mutation/cast> → <use>, citing file:line at each step.
3. Mechanism: the single sentence that explains WHY the symptom occurs.
4. Minimal fix: the smallest change that removes the mechanism (no refactor).
5. Predicted signal: which DISABLED_ test flips to green, under which preset.
```

## Tree-of-Thought template

Generate **2–3 hypotheses**, score each on three axes (1–5), keep the top one:

```text
### Hypotheses
H1: <mechanism>            evidence: <file:line>
H2: <mechanism>            evidence: <file:line>
H3: <mechanism>            evidence: <file:line>   (optional)

### Scoring  (Evidence fit · Minimal-diff · Article safety)
H1: E=_ M=_ A=_  → total _
H2: E=_ M=_ A=_  → total _
H3: E=_ M=_ A=_  → total _

### Decision
Chosen: H_   Why: <one line>   Pruned: <why the others lose>
```

Scoring axes:

- **Evidence fit** — how directly the data-flow trace supports this mechanism.
- **Minimal-diff** — how small and local the resulting change is (bigger = lower score).
- **Article safety** — likelihood the fix passes the constitution unchanged (a fix that
  would introduce `std::`, drop the allocator, or swap `double`→`float` in a sim path scores
  low here even if it would make the test green).

## Guardrails for the reasoning step

1. **Reason before editing.** No `edit` tool call until a CoT chain or a ToT decision exists
   in the response.
2. **Pin to evidence.** Every hypothesis cites a `file:line` from the Code Analysis Report.
   A hypothesis with no citation is dropped, not scored.
3. **False positives are hypotheses too.** If a branch matches FP-001/FP-002/FP-003, score it,
   then prune it explicitly with the reason — this is how learners see _why_ it is not a bug.
4. **Determinism is a first-class axis.** For any sim-path bug, the Article-safety score must
   explicitly mention seeding, accumulator type, or iteration order.
5. **Hand the chosen hypothesis to the constitution-checker before applying it**, not after.
   The reasoning engine proposes; the checker disposes; the orchestrator then edits.
