---
description: Generate CI workflows + snippet-extraction tooling + issue/PR templates + CODEOWNERS + dependabot.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit", "runCommands"]
inputs: []
outputs:
  - path: .github/workflows/ci-validate-snippets.yml
    kind: file
    overwrite: false
  - path: .github/workflows/ci-lint-markdown.yml
    kind: file
    overwrite: false
  - path: .github/workflows/ci-link-check.yml
    kind: file
    overwrite: false
  - path: .github/workflows/ci-spec-kit-validate.yml
    kind: file
    overwrite: false
  - path: .github/workflows/coding-agent-bootstrap.yml
    kind: file
    overwrite: false
  - path: .github/ISSUE_TEMPLATE/session-build.yml
    kind: file
    overwrite: false
  - path: .github/ISSUE_TEMPLATE/content-bug.yml
    kind: file
    overwrite: false
  - path: .github/PULL_REQUEST_TEMPLATE.md
    kind: file
    overwrite: false
  - path: .github/CODEOWNERS
    kind: file
    overwrite: false
  - path: .github/dependabot.yml
    kind: file
    overwrite: false
  - path: tools/extract-snippets.mjs
    kind: file
    overwrite: false
  - path: tools/validate-prompts.mjs
    kind: file
    overwrite: false
  - path: tools/new-session.mjs
    kind: file
    overwrite: false
  - path: tools/snippet-cmake-template/CMakeLists.txt
    kind: file
    overwrite: false
  - path: tools/snippet-cmake-template/main.cpp.in
    kind: file
    overwrite: false
validation:
  - "node tools/validate-prompts.mjs"
  - "yamllint .github/workflows || true"
  - "npm run lint"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Stand up the CI pipeline and supporting tooling so every PR is automatically validated and
the Copilot Coding Agent has a known-good environment.

## Context references

- `#file:../instructions/cpp-snippets.instructions.md`
- `#file:../instructions/prompt-authoring.instructions.md`
- `#file:../../docs/engagement-charter.md`
- `#file:../../package.json`

## Pre-conditions

- `bootstrap-repo.prompt.md` and `bootstrap-copilot-customization.prompt.md` have run.
- Repo's GitHub remote is `Insight-NA/ea_copilot_workshop`.

## Steps

1. **`tools/extract-snippets.mjs`** — Node 20 ESM script that:
   - Walks `**/*.md` (excluding `node_modules`, `output`, `third_party`).
   - Extracts every fenced ` ```cpp ` block.
   - Emits each block as `tools/snippet-cmake-template/snippets/<file-hash>.cpp` wrapped via
     `main.cpp.in`.
   - Configures and builds via CMake + Ninja.
   - Exits non-zero if any block fails to compile.
   - Prints a summary table.
2. **`tools/snippet-cmake-template/`** — minimal CMake project with `-fno-exceptions`,
   `-fno-rtti`, C++20, vcpkg-EASTL dependency, GoogleTest.
3. **`tools/validate-prompts.mjs`** — Node script that walks `.github/prompts/**/*.prompt.md`
   and `.github/instructions/**/*.instructions.md` and `.github/chatmodes/**/*.chatmode.md`,
   verifies front-matter schema (per `prompt-authoring.instructions.md` and
   `chat-mode-authoring.instructions.md`), checks `last_reviewed` is within 90 days, checks
   declared `outputs[]` paths look reasonable. Exits non-zero on any violation.
4. **`tools/new-session.mjs`** — copies a session template into `sessions/NN-slug/` based on
   the next free index; never overwrites.
5. **`.github/workflows/ci-validate-snippets.yml`** — on PR to main: ubuntu + windows
   matrix, install Node 20, vcpkg, run `npm run validate:snippets`. Cache vcpkg.
6. **`ci-lint-markdown.yml`** — on PR: install Node 20, `npm ci`, `npm run lint:md`,
   `npm run lint:format`.
7. **`ci-link-check.yml`** — uses `lycheeverse/lychee-action`; treat external 4xx as
   warnings, internal as errors.
8. **`ci-spec-kit-validate.yml`** — runs only when `output/**/specs/**` changes; checks
   constitution + spec + plan are present and `tasks/` is non-empty when `plan.md` is non-empty.
9. **`coding-agent-bootstrap.yml`** — Coding-Agent setup workflow: provisions Node, vcpkg,
   CMake, Ninja, GitHub CLI; `npm ci`. Documents the toolchain so the Coding Agent's first
   command succeeds.
10. **Issue templates**:
    - `session-build.yml` — form-style issue capturing session number, demo files needed,
      acceptance criteria, target Copilot plan tier; this is the issue shape we hand to the
      Coding Agent.
    - `content-bug.yml` — for facilitator-discovered defects in committed materials.
11. **`PULL_REQUEST_TEMPLATE.md`** — checklist: lint, snippets, links, prompts, CHANGELOG,
    reviewer-mode pass attached, no secrets, no EA-internal IP.
12. **`CODEOWNERS`** — `* @Insight-NA/copilot-workshop-leads` initially; refine after intake.
13. **`dependabot.yml`** — npm + github-actions, weekly cadence, group security updates.

> **HITL gate:** before opening a PR with this scaffolding, the user runs the workflows
> locally with `act` or pushes a draft branch and confirms green.

## Output contract

All 15 files exist. Workflows pass `actionlint` if available. `node tools/validate-prompts.mjs`
exits 0 against the existing customization layer.

## Self-validation

```bash
node -e "import('./tools/extract-snippets.mjs').then(()=>console.log('ok'))"
node tools/validate-prompts.mjs
npm run lint
```

## Failure modes

- **CI matrix that's too broad**: keep ubuntu-latest + windows-latest; do not add macOS until
  a facilitator requests it. Macs are not used for snippet validation per the engagement.
- **Hardcoded secrets in workflows**: never. Use `secrets.GITHUB_TOKEN` only.
- **Slow lychee runs**: cache by content-hash; treat external links as warnings only.
