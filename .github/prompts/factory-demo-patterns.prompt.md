---
description: Generate the four demo-pattern files (crash-dump triage, proactive issue hunt, spec-kit flow, multi-agent squad) for the factory overlay.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: factory-overlay/demo-patterns/crash-dump-triage.md
    kind: file
    overwrite: false
  - path: factory-overlay/demo-patterns/proactive-issue-hunt.md
    kind: file
    overwrite: false
  - path: factory-overlay/demo-patterns/spec-kit-flow.md
    kind: file
    overwrite: false
  - path: factory-overlay/demo-patterns/multi-agent-squad.md
    kind: file
    overwrite: false
validation:
  - "ls factory-overlay/demo-patterns/*.md | wc -l | grep -q 4"
  - "npm run lint"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Produce the four reusable demo-pattern files that drive Sessions 2, 4, 6–7, and 9.

## Context references

- Reference (existing factory): `/Users/rrehman/Documents/projects/copilot-workshop-factory/knowledge-base/demo-patterns/spec-driven-dev.md`
  (shape only).
- `#file:../../docs/engagement-charter.md`
- `#file:../instructions/spec-kit-artifacts.instructions.md`

## Pre-conditions

- Stack profile and domain profile prompts already executed.

## Steps

For each file, produce these uniform sections: **Identity**, **Learning objective**,
**Setup**, **Facilitation script (Phase 1/2/3)**, **Common pitfalls**, **Recovery script**,
**Stretch goals**, **Required Copilot plan tier**.

1. **`crash-dump-triage.md`** — feed minidump + PDB to Copilot; pinpoint faulting frame;
   propose root cause; produce fix; re-run failing test. Include the exact prompt strings to
   use; document the requirement that PDB + source rev be matched (CI verifies this for the
   demo workspace).
2. **`proactive-issue-hunt.md`** — split into **logic-bug** prompts and **security-bug**
   prompts. Include the **false-positive triage protocol** (3-step rubric: reproduce, analyze
   data flow, decide). Reference CWE categories (CWE-787 OOB write, CWE-416 UAF, CWE-476
   null deref) for the security side.
3. **`spec-kit-flow.md`** — `/constitution` → `/specify` → `/plan` → `/tasks` → `/implement`
   demo, with HITL gate annotations. Embeds the EA Engineering Constitution articles as a
   reusable starter.
4. **`multi-agent-squad.md`** — coordinator + cpp-architect + cpp-developer + cpp-tester
   delegation pattern. Includes the brief-template for each delegation step and the
   decisions-log template.

## Output contract

All four files exist with the eight required sections each.

## Self-validation

```bash
for f in crash-dump-triage proactive-issue-hunt spec-kit-flow multi-agent-squad; do
  test -f "factory-overlay/demo-patterns/$f.md" || exit 1
  grep -q "## Facilitation script" "factory-overlay/demo-patterns/$f.md" || exit 1
done
npm run lint
```

## Failure modes

- **Vague prompts**: every facilitation script must include the verbatim prompt strings the
  facilitator will type. No "explain how to use Copilot here".
- **Missing HITL gates** in spec-kit-flow.md or multi-agent-squad.md: gates are non-negotiable.
