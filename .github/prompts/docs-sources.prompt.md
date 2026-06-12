---
description: Generate docs/sources/bert-email-2026-04-28.md and docs/sources/mural-priorities-2026-04-29.md from user-provided raw text.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs:
  - name: bert_email_text
    description: Raw text of Bert Sandie's email (paste in chat).
    required: true
  - name: mural_priorities_text
    description: Raw text or screenshot transcription of the Mural board.
    required: true
outputs:
  - path: docs/sources/bert-email-2026-04-28.md
    kind: file
    overwrite: false
  - path: docs/sources/mural-priorities-2026-04-29.md
    kind: file
    overwrite: false
validation:
  - "test -f docs/sources/bert-email-2026-04-28.md"
  - "test -f docs/sources/mural-priorities-2026-04-29.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Persist the source-of-truth materials as committed files so every downstream prompt can
cite them. Run this BEFORE `engagement-charter.prompt.md`.

## Steps

1. Take `bert_email_text` and write it verbatim to `docs/sources/bert-email-2026-04-28.md`,
   wrapped in front-matter with `received: 2026-04-28`, `sender: "Bert Sandie"`, `recipients`,
   `redacted: false`.
2. Take `mural_priorities_text` and write it to `docs/sources/mural-priorities-2026-04-29.md`,
   front-matter with `captured: 2026-04-29`, `participants`, `mural_url`.
3. Confirm with the user whether redactions are needed (PII, EA-internal references). If yes,
   apply redactions inline marked `[redacted]`.

> **HITL gate:** before commit, the user reviews each source file for confidentiality.

## Output contract

Both files exist; front-matter present; verbatim or redacted text follows.

## Failure modes

- **Committing unredacted internal references**: never. Default to redaction; ask if unsure.
