---
description: Master prompt — runs the full build sequence end-to-end via the orchestration order in docs/build-graph.md. Use sparingly; prefer running individual prompts.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit", "runCommands"]
inputs: []
outputs: []
validation:
  - "npm run lint"
  - "npm run validate:prompts"
  - "npm run validate:snippets"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

End-to-end orchestration: invoke every prompt in order, gated by HITL between phases.

## Pre-conditions

- The user has staged source materials (Bert email, Mural priorities) in chat or as files.
- The user has confirmed they want a full bootstrap (this is destructive in the sense that it
  will create dozens of files).

## Steps

1. **Phase 0** — `docs-sources.prompt.md` then `engagement-charter.prompt.md`. **HITL gate.**
2. **Phase 1** — `bootstrap-repo` → `bootstrap-copilot-customization` → `bootstrap-ci` →
   `bootstrap-mcp`. Run validations after each. **HITL gate.**
3. **Phase 2** — factory-overlay prompts (5 in parallel where the agent allows). **HITL gate.**
4. **Phase 3** — demo-workspace prompts in dependency order: scaffold → engine-module →
   eastl-feature → fixtures-crash-dumps → fixtures-bug-reports → instructions-prompts-chatmodes
   → agents-md → spec-kit-init. **HITL gate** after engine-module (verify build green).
5. **Phase 4** — `slides-template`, `delivery-runbook`, `feedback-toolkit`, `context-belt`,
   `escalation-paths`, `build-graph`. **HITL gate.**
6. **Phase 5** — sessions 01–09 (parallelizable). **HITL gate** after all 9 complete.
7. **Phase 6** — review prompts (`review-adversarial` against the whole tree;
   `review-cpp-snippets`; `review-prompt-conformance`; `review-copilot-plan-gating`).
   **HITL gate** to triage findings.
8. **Final validation** — `npm run lint && npm run validate:prompts && npm run validate:snippets`.

## Output contract

A fully built repo. Review reports under `docs/reviews/`. CHANGELOG updated.

## Failure modes

- **Skipping HITL gates**: never. The whole point of phased orchestration is checkpointing.
- **Running this on a non-empty repo without auditing existing state**: ABORT if any of the
  declared outputs already exist with non-stub content; defer to per-phase prompts.
