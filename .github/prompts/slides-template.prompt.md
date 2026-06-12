---
description: Generate docs/slides-template.md — the slide-outline template Sessions 1–9 conform to.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: docs/slides-template.md
    kind: file
    overwrite: false
validation:
  - "grep -q 'Slide 1' docs/slides-template.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Provide the canonical slide-outline shape every session's `slides.outline.md` follows so the
slide deck (PPTX or Marp) can be regenerated mechanically.

## Steps

Produce a 12-slide template:

1. Title + presenter.
2. Series-level recap (where we are, what's next).
3. Today's objective (1 sentence).
4. Why this matters for AAA C++ engineers.
5. Concept primer (split across 2 slides if needed).
   6–9. Demo storyboard (one slide per demo phase).
6. Hands-on framing.
7. Common pitfalls.
8. Wrap + survey.

For each slide: title, 3–5 bullet points max, optional speaker note.

## Output contract

Template exists with all 12 slides; each session's `slides.outline.md` instantiates this.

## Failure modes

- **Bullet bloat**: hard cap 5 bullets; if more, split slides.
