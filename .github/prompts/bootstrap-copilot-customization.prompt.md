---
description: Generate the Copilot customization layer — copilot-instructions.md, scoped instructions, chat modes — in one pass.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: .github/copilot-instructions.md
    kind: file
    overwrite: false
  - path: .github/instructions/cpp-snippets.instructions.md
    kind: file
    overwrite: false
  - path: .github/instructions/facilitator-script.instructions.md
    kind: file
    overwrite: false
  - path: .github/instructions/learner-guide.instructions.md
    kind: file
    overwrite: false
  - path: .github/instructions/spec-kit-artifacts.instructions.md
    kind: file
    overwrite: false
  - path: .github/instructions/chat-mode-authoring.instructions.md
    kind: file
    overwrite: false
  - path: .github/instructions/prompt-authoring.instructions.md
    kind: file
    overwrite: false
  - path: .github/instructions/survey-template.instructions.md
    kind: file
    overwrite: false
  - path: .github/chatmodes/planner.chatmode.md
    kind: file
    overwrite: false
  - path: .github/chatmodes/builder.chatmode.md
    kind: file
    overwrite: false
  - path: .github/chatmodes/reviewer.chatmode.md
    kind: file
    overwrite: false
  - path: .github/chatmodes/squad-coordinator.chatmode.md
    kind: file
    overwrite: false
  - path: .github/chatmodes/cpp-architect.chatmode.md
    kind: file
    overwrite: false
  - path: .github/chatmodes/cpp-developer.chatmode.md
    kind: file
    overwrite: false
  - path: .github/chatmodes/cpp-tester.chatmode.md
    kind: file
    overwrite: false
validation:
  - "npm run validate:prompts"
  - "npm run lint"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Generate the entire Copilot customization layer (repo-wide instructions + 7 scoped
instruction files + 7 chat modes) in one deterministic pass. Each file follows the schema
defined in [`.github/instructions/prompt-authoring.instructions.md`](../instructions/prompt-authoring.instructions.md)
and [`chat-mode-authoring.instructions.md`](../instructions/chat-mode-authoring.instructions.md).

## Context references

- `#file:../copilot-instructions.md`
- `#file:../instructions/prompt-authoring.instructions.md`
- `#file:../instructions/chat-mode-authoring.instructions.md`
- `#file:../../docs/engagement-charter.md`

## Pre-conditions

- `bootstrap-repo.prompt.md` has run.
- `engagement-charter.prompt.md` has run.

## Steps

1. **Repo-wide `.github/copilot-instructions.md`** — sections: Mission, Precedence (4-tier
   chain ending with the user message), House style, C++ snippet rules (C++20, EASTL-first,
   no exceptions, no RTTI, allocator-aware, `[[nodiscard]]`, `noexcept`), Do NOT, Always,
   Self-test, Off-the-rails recovery. Include `last_reviewed` + `reviewer`.
2. **`cpp-snippets.instructions.md`** — `applyTo: "**/*.{h,hpp,cpp,cc,cxx,inl},**/*.md"`.
   Hard rules + idiom hot-list (forbidden patterns Copilot frequently emits) + an example
   skeleton class showing nodiscard, noexcept move, allocator-aware EASTL container.
3. **`facilitator-script.instructions.md`** — `applyTo: "sessions/**/facilitator-script.md"`.
   Required H2 sections, time-marker rule, callout vocabulary (`Facilitator note`, `Say:`,
   `Do:`, `Watch for:`, `HITL gate:`), prompt-fence-tag rule (`text` not `cpp`),
   forbidden patterns.
4. **`learner-guide.instructions.md`** — `applyTo: "sessions/**/learner-guide.md"`. Required
   sections, copy-pasteability rule, voice (2nd person, present tense), forbidden patterns.
5. **`spec-kit-artifacts.instructions.md`** — `applyTo: "output/**/specs/**,sessions/06-*/**,sessions/07-*/**"`.
   GitHub `spec-kit` flow ordering (`/constitution` → `/specify` → `/plan` → `/tasks` →
   `/implement`), required Constitution articles, spec/plan/tasks formats, HITL between
   `/implement` stages.
6. **`chat-mode-authoring.instructions.md`** — `applyTo: ".github/chatmodes/**/*.chatmode.md"`.
   Front-matter schema, body sections, tool allowlist matrix.
7. **`prompt-authoring.instructions.md`** — `applyTo: ".github/prompts/**/*.prompt.md"`.
   Full schema (description/mode/model/tools/inputs/outputs/validation/last_reviewed/reviewer)
   and 7-section body contract.
8. **`survey-template.instructions.md`** — `applyTo: "sessions/**/retro-survey.md,docs/feedback-toolkit.md"`.
   Per-session retro hard limits (5 questions, 60s); 5 canonical questions; mid-series and
   end-of-series formats; series-level metrics queries reference.
9. **Chat modes** — produce all 7 with the body templates from
   `chat-mode-authoring.instructions.md`. Tool allowlists per the matrix in that file.

> **HITL gate:** if any of the 15 files already exists, stop and ask before overwriting.

## Output contract

All 15 files exist with valid YAML front-matter. Each file has the required body sections.
`last_reviewed` is today; `reviewer` is "Insight Engagement Lead" unless the user overrides.

## Self-validation

```bash
npm run validate:prompts
npm run lint
for f in .github/instructions/*.instructions.md .github/chatmodes/*.chatmode.md; do
  head -1 "$f" | grep -q '^---$' || { echo "Missing front-matter: $f"; exit 1; }
done
```

## Failure modes

- **Front-matter drift**: every file must use the canonical schema. If you find yourself
  inventing a new field, stop and update the authoring instructions first.
- **Overlapping `applyTo`**: each scoped file must have a non-overlapping primary
  responsibility. Resolve overlaps in the global `copilot-instructions.md` precedence rules.
