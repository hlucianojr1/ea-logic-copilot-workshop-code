---
description: Generate docs/engagement-charter.md from the EA email + Mural priorities. Run this FIRST after repo bootstrap.
mode: agent
model: Claude Opus 4.6
tools: ["codebase", "edit", "search", "fetch"]
inputs:
  - name: source_email_path
    required: true
    description: Path to the markdown rendering of Bert Sandie's April 2026 email (under docs/sources/).
    default: docs/sources/bert-email-2026-04-28.md
  - name: source_mural_path
    required: true
    description: Path to the markdown rendering of the Mural board priorities.
    default: docs/sources/mural-priorities-2026-04-29.md
outputs:
  - path: docs/engagement-charter.md
    kind: file
    overwrite: false
validation:
  - "test -f docs/engagement-charter.md"
  - "npm run lint"
  - "npm run links"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Produce the canonical, single-source-of-truth charter for the EA × Insight engagement.
Every other prompt and every committed customization file must be able to cite this charter
to justify its rules.

## Context references

- `#file:../../README.md`
- `#file:../../AGENTS.md`
- `#file:../../docs/sources/bert-email-2026-04-28.md`
- `#file:../../docs/sources/mural-priorities-2026-04-29.md`
- `#file:../instructions/prompt-authoring.instructions.md`

## Pre-conditions

- Source documents present under `docs/sources/`. If missing, stop and ask the user to
  commit them first (verbatim email + Mural transcript, redacted of PII).
- Repo has been bootstrapped (`README.md`, `AGENTS.md`, `.github/copilot-instructions.md`
  exist).

## Steps

1. Read both source documents in full.
2. Synthesize into the following canonical sections:
   1. **Engagement summary** — client (EA), Insight team, audience (C++ game/engine/tools
      engineers), expected attendees, time zones.
   2. **Goals** — three sentences max, derived from the email's stated outcomes.
   3. **In-scope topics** — five tracks (Code Comprehension at Scale; Bug & Defect Fixing;
      Context Engineering at Scale; Spec-Kit Mastery; Multi-Agent Orchestration), nine
      sessions total.
   4. **Out-of-scope** — what we explicitly will not cover (non-C++ stacks, EA-internal IP
      codebases, foundational Copilot intro).
   5. **Constraints** — million-line context, no-exceptions / no-RTTI / EASTL conventions,
      Enterprise plan tier where required.
   6. **Format & cadence** — 9 × 60-min, hybrid recording + zone Q&A.
   7. **Demo workspace strategy** — `Cnc_Red_Alert` (scale) + `EASTL` (modern) + synthetic
      `engine_demo` (focused).
   8. **Success metrics** — per-session and series-level (Megan's ask).
   9. **Decision log** — initial decisions; future amendments append-only.
   10. **Open questions** — items pending the EA call-back.
3. Cite every rule back to a source bullet (line link to `docs/sources/...`).
4. Add `last_reviewed` and `reviewer` fields at the top.
5. Update `CHANGELOG.md`: "Added: docs/engagement-charter.md (canonical scope)."

> **HITL gate:** Before committing, the engagement lead reviews and signs off in `docs/engagement-charter.md` itself (sign-off block at the bottom).

## Output contract

- `docs/engagement-charter.md` exists, with all 10 sections above as H2 headings.
- Every in-scope track maps to exactly one or two of the 9 sessions in the curriculum table.
- A "Decision log" section is initialized with at least the format-decision (9 × 60-min) and
  the demo-workspace-strategy decision.
- `CHANGELOG.md` updated under `[Unreleased] / Added`.

## Self-validation

```bash
npm run lint
npm run links
grep -q "## Engagement summary" docs/engagement-charter.md
grep -q "## Decision log" docs/engagement-charter.md
```

## Failure modes

- **Inventing facts**: if a source document is missing, do not fabricate. Stop and request it.
- **Re-stating Bert's email verbatim**: synthesize, don't transcribe; the charter is shorter
  than the email by design.
- **Ambiguous scope**: any item without a clear in/out scope decision goes into "Open
  questions" with a recommended default — never silently dropped.
