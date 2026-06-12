---
description: Run an adversarial 2-pass review against any deliverable; emit a review-report.md keyed by severity.
mode: agent
model: Claude Opus 4.6
tools: ["codebase", "search"]
inputs:
  - name: target_path
    description: Path to the deliverable under review (file or directory).
    required: true
  - name: pass_number
    description: 1 or 2.
    required: true
outputs:
  - path: docs/reviews/${target_slug}-pass${pass_number}.md
    kind: file
    overwrite: false
validation:
  - "test -d docs/reviews"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Produce an adversarial review report against the target. Severity rubric per
`reviewer.chatmode.md`: Critical, Significant, Minor, Nit. Pass 1 hunts for substantive
defects; Pass 2 (after author rebuttal/fixes) confirms closure or escalates.

## Steps

1. Read the target with read-only tools only.
2. Walk the deliverable's claims and verify each against:
   - The engagement charter.
   - The instruction files relevant to the file type.
   - For C++ snippets: compile via `tools/extract-snippets.mjs`.
   - For markdown: `npm run lint`.
3. Produce `docs/reviews/${target_slug}-pass${pass_number}.md` with sections:
   - **Subject** — file(s) reviewed.
   - **Summary verdict** — Ship / Ship with fixes / Block.
   - **Critical findings** — must-fix; cite line numbers.
   - **Significant findings** — should-fix; cite line numbers.
   - **Minor findings** — nice-to-fix.
   - **Nits** — style.
   - **Verification** — what tools/commands were run.
4. NEVER edit the target. Output goes to `docs/reviews/` only.

## Output contract

Single review file at the templated path.

## Failure modes

- **Editing the target**: hard rule. Reviewer mode is read-only.
- **Not categorizing severity**: every finding gets one of the four levels.
