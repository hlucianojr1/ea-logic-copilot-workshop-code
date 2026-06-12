---
description: Survey authoring rules for retro micro-surveys, mid-series checkpoint, end-of-series.
applyTo: "sessions/**/retro-survey.md,docs/feedback-toolkit.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

# Survey Authoring Rules

Surveys exist to feed two consumers: the per-session retrospective (delivered same-day) and
the series-level metrics report Megan agreed to provide EA. Every question must serve at
least one of those consumers.

## Per-session retro — hard limits

- **Maximum 5 questions.**
- **Maximum 60 seconds** to complete (test by reading aloud at conversational pace).
- **3 Likert (1–5) + 2 free-text** is the canonical shape.

### Required questions (every session)

1. (Likert 1–5) "How confident are you applying today's content tomorrow?"
2. (Likert 1–5) "How well did the demos work in real-time?"
3. (Likert 1–5) "How relevant was the content to your day job?"
4. (Free text, optional) "Biggest takeaway from this session?"
5. (Free text, optional) "Weakest part of this session — what should we change?"

### Forbidden

- More than 5 questions per retro.
- Open-ended "any other thoughts?" without a narrower frame — produces noise.
- Questions whose answers can be retrieved from GitHub Copilot analytics (don't ask people
  to self-report acceptance rate).

## Mid-series checkpoint (after Session 4)

- Up to 8 questions; 3-minute target.
- Includes a "what topic from the remaining sessions matters most to you?" ranking question.
- Captures attendance reasons for missed sessions.

## End-of-series survey (after Session 9)

- Up to 12 questions; 5-minute target.
- Net-Promoter-style question (0–10 "would you recommend this series to a teammate?").
- Free-text "what would have made this 10/10?".
- Three Likert ratings on **adoption confidence** (daily-driver use of Copilot), **org
  policy clarity**, and **manager support**.

## Series-level metrics (not surveyed; pulled from analytics)

Captured in `docs/feedback-toolkit.md` as queries:

- Active Copilot users (pre-engagement vs. post-engagement delta).
- Suggestion acceptance rate.
- Chat usage (per-user, per-week).
- Premium-request burn vs. budget.

## Hand-off

Survey responses land in `sessions/<n>/retro-results/` (gitignored — they may contain
unredacted free text). Aggregated, anonymized findings get written to
`docs/feedback-results.md` after each session.
