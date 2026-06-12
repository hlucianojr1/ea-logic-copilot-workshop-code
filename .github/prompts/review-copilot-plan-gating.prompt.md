---
description: Verify the Copilot plan-tier matrix in the engagement charter matches the requirements declared in each session prompt and demo-pattern file.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "search"]
inputs: []
outputs:
  - path: docs/reviews/copilot-plan-gating.md
    kind: file
    overwrite: false
validation:
  - "test -f docs/engagement-charter.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Cross-check that every feature demoed in a session has a documented Copilot plan-tier
requirement, and that the requirements roll up consistently in the charter.

## Steps

1. Walk `sessions/**/facilitator-script.md`, `factory-overlay/demo-patterns/*.md`,
   `output/ea-cpp-games/.github/prompts/*.prompt.md`.
2. Extract any "Required Copilot plan tier" or equivalent claim.
3. Cross-check against `docs/engagement-charter.md` Section 4 (Curriculum) plan-tier column.
4. Emit `docs/reviews/copilot-plan-gating.md` listing:
   - Features keyed to plan tier (Free / Pro / Business / Enterprise).
   - Mismatches (charter says Business, session script claims Enterprise, etc.).
   - Features where the tier is unstated.

## Output contract

Report file exists; mismatches called out as Critical findings.

## Failure modes

- **Quiet inference**: never assume tier; if the session doesn't state it, it's a
  Significant finding to fix.
