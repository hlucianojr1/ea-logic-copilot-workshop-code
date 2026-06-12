---
description: One-shot bootstrap of the build-system skeleton (configs, tooling, top-level layout). Idempotent — safe to re-run.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit", "runCommands"]
inputs: []
outputs:
  - path: .gitignore
    kind: file
    overwrite: false
  - path: .gitattributes
    kind: file
    overwrite: false
  - path: .editorconfig
    kind: file
    overwrite: false
  - path: .markdownlint.jsonc
    kind: file
    overwrite: false
  - path: .prettierrc.json
    kind: file
    overwrite: false
  - path: .prettierignore
    kind: file
    overwrite: false
  - path: package.json
    kind: file
    overwrite: false
  - path: .env.example
    kind: file
    overwrite: false
  - path: README.md
    kind: file
    overwrite: false
  - path: CHANGELOG.md
    kind: file
    overwrite: false
  - path: AGENTS.md
    kind: file
    overwrite: false
  - path: LICENSE
    kind: file
    overwrite: false
  - path: output/.gitkeep
    kind: file
    overwrite: false
validation:
  - "npm install --ignore-scripts"
  - "npm run lint"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Produce the foundation files every contributor (and Coding Agent) depends on, in a single
deterministic pass. Re-running this prompt on an already-bootstrapped repo must be a no-op
(no overwrites; report which files already exist).

## Context references

- `#file:../instructions/prompt-authoring.instructions.md`
- `#file:../copilot-instructions.md`
- `#file:../../docs/engagement-charter.md`

## Pre-conditions

- Empty repo OR a repo missing one or more of the declared output files.
- Node 20+ installed; `npm` available.

## Steps

1. For each output path, check if the file already exists. If yes, skip and log; if no,
   create it with the canonical contents described in the next steps.
2. **`.gitignore`** — covers OS junk, IDE caches, Node, Python, C++/CMake/Ninja/vcpkg,
   coverage artifacts, generated `output/**` (with whitelist for `.gitkeep`), local crash-dump
   working copies (`*.dmp.local`, `*.pdb.local`), `.env*` (whitelist `.env.example`), `secrets/`,
   third-party build trees. Whitelist `.vscode/{settings,extensions,mcp,launch,tasks}.json`.
3. **`.gitattributes`** — `* text=auto eol=lf`; markdown/cpp diff drivers; binary markers for
   `*.dmp`, `*.pdb`, image formats; linguist hints for `third_party/**` and `output/**`.
4. **`.editorconfig`** — UTF-8, LF, 2-space indent default, 4-space C++; `[Makefile] indent_style=tab`;
   `[*.md] trim_trailing_whitespace=false`.
5. **`.markdownlint.jsonc`** — `MD013` off, `MD033` off, `MD024 siblings_only`, `MD041` off,
   `MD034` off, `MD003 atx`, `MD004 dash`, `MD040` on, `MD029 one`.
6. **`.prettierrc.json`** — printWidth 100, 2-space, double-quote, trailing-comma all,
   endOfLine lf, proseWrap preserve.
7. **`.prettierignore`** — `node_modules`, `build`, `out`, `output` (with `.gitkeep` whitelist),
   `third_party`, `*.min.*`, `CHANGELOG.md`.
8. **`package.json`** — name `ea-copilot-workshop`, private, type module, engines node ≥20,
   scripts: `lint`, `lint:md`, `lint:format`, `format`, `links`, `validate:snippets`,
   `validate:prompts`, `scaffold:session`. devDependencies: markdownlint-cli2, prettier
   (latest stable at engagement start).
9. **`.env.example`** — comment block + `GITHUB_PERSONAL_ACCESS_TOKEN=` placeholder + optional
   `COPILOT_MODEL=`.
10. **`README.md`** — sections per `## How to build (humans)`, `## How to validate`,
    `## How to deliver`, `## Configuration / secrets`, `## Repository layout`, `## License`.
11. **`CHANGELOG.md`** — Keep-a-Changelog format with `[Unreleased]` section.
12. **`AGENTS.md`** — content per the body of the same name in the canonical plan; in
    particular Mission, Non-negotiables, Build commands, File-authoring conventions,
    Hand-off conventions, Safety boundaries.
13. **`LICENSE`** — Insight internal, all rights reserved, redistribution prohibited.
14. **`output/.gitkeep`** — empty file so the directory exists.

> **HITL gate:** before any overwrite of an existing file, stop and ask the user.

## Output contract

Every output path listed in the front-matter exists with content matching the steps above.
No file in the working tree was modified outside `outputs[]`.

## Self-validation

```bash
test -f .gitignore && test -f .gitattributes && test -f .editorconfig
test -f package.json && test -f README.md && test -f AGENTS.md
node -e "JSON.parse(require('fs').readFileSync('package.json'))"
node -e "JSON.parse(require('fs').readFileSync('.prettierrc.json'))"
npm install --ignore-scripts
npm run lint
```

## Failure modes

- **Overwriting handcrafted README**: never. If the README has more than the template
  contents, stop and ask.
- **Inventing dependencies**: only `markdownlint-cli2` and `prettier` go into `devDependencies`.
  Other deps go through `bootstrap-ci.prompt.md`.
- **Missing CHANGELOG entry**: add an entry under `[Unreleased] / Added`.
