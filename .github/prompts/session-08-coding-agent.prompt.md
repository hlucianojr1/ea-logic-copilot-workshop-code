---
description: Session 8 — "Multi-Agent pt 1 — Coding Agent". Full deliverable set.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: sessions/08-coding-agent/facilitator-script.md
    kind: file
    overwrite: false
  - path: sessions/08-coding-agent/learner-guide.md
    kind: file
    overwrite: false
  - path: sessions/08-coding-agent/slides.outline.md
    kind: file
    overwrite: false
  - path: sessions/08-coding-agent/exercises/01-file-issue-and-watch.md
    kind: file
    overwrite: false
  - path: sessions/08-coding-agent/exercises/02-review-the-pr.md
    kind: file
    overwrite: false
  - path: sessions/08-coding-agent/retro-survey.md
    kind: file
    overwrite: false
  - path: sessions/08-coding-agent/pre-work-email.md
    kind: file
    overwrite: false
validation:
  - "npm run lint"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Teach the **GitHub Copilot Coding Agent**: file an issue, watch it produce a draft PR,
review the PR, request changes, merge. The session uses a real issue against
`output/ea-cpp-games/` (e.g., "Add `entity_view` iterator to ECS").

## Context references

- `#file:../../.github/ISSUE_TEMPLATE/session-build.yml`
- `#file:../../.github/workflows/coding-agent-bootstrap.yml`
- `#file:../../AGENTS.md`
- `#file:../../output/ea-cpp-games/AGENTS.md`

## Pre-conditions

- Coding Agent enabled on the repo (Enterprise plan).
- `coding-agent-bootstrap.yml` provisions the CI environment.
- An issue is pre-staged for the demo (we don't author it cold during the session).

## Session shape (60 ±3 min)

| Block            | Time        | Activities                                                                    |
| ---------------- | ----------- | ----------------------------------------------------------------------------- |
| Recap + concept  | 00:00–10:00 | Async coding agent vs. interactive Copilot; AGENTS.md role.                   |
| Demo: file issue | 10:00–18:00 | Show the pre-staged issue; assign Copilot; explain why issue framing matters. |
| Wait + walkthru  | 18:00–35:00 | While agent works, walk AGENTS.md & coding-agent-bootstrap.yml.               |
| Demo: review PR  | 35:00–50:00 | PR is ready; walk the diff; request changes; second iteration; merge.         |
| Hands-on         | 50:00–55:00 | Exercises 01 + 02 (mostly take-home).                                         |
| Survey           | 55:00–60:00 | Retro.                                                                        |

## Steps

Generate the 7 files. Specific:

- The pre-staged issue is critical — we don't gamble on Coding Agent latency live.
- Exercise 01 ("file an issue and watch") is take-home and asynchronous.
- Exercise 02 is "review a PR I produced for you" — provides a fixed PR (committed to a
  branch ahead of the session) so all learners can complete it.
- Risk callout: Coding Agent may be unavailable; the script includes a Plan-B that walks the
  delivered PR statically.

## Output contract

7 files; Plan-B documented; AGENTS.md featured prominently.

## Failure modes

- **Live agent failure with no fallback**: always have the pre-merged demo PR ready.
- **Treating Coding Agent's output as final**: it's a draft. Review is mandatory.
