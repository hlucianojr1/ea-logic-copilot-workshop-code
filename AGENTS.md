# AGENTS.md — EA × Insight Copilot Workshop Build

> **Audience:** every coding agent (Copilot Chat, Copilot Coding Agent, Claude Code, Cursor,
> any IDE-integrated assistant) operating in this repository, plus humans pairing with them.
> This file is the durable, IDE-agnostic complement to `.github/copilot-instructions.md`.

## Project mission

This repository builds — but does **not** contain — the Insight × EA GitHub Copilot workshop
deliverables. Treat the repo as a **build system**: prompt files in `.github/prompts/` are the
source code, and outputs land in [`sessions/`](sessions/) and [`output/ea-cpp-games/`](output/).

## Non-negotiables

1. **No EA-internal IP** in any committed file. Reference only the public
   `github.com/electronicarts` org. If you find yourself pasting code that looks proprietary,
   stop and escalate.
2. **No secrets.** Tokens, PATs, signing keys, and customer email contents (beyond what is
   already committed in `docs/engagement-charter.md`) never enter the working tree. Use
   `${input:...}` in `mcp.json` and environment variables elsewhere.
3. **Every C++ snippet must compile.** If you author a fenced ` ```cpp ` block in a session
   doc, it WILL be extracted and built by `npm run validate:snippets`. Do not commit
   pseudocode in cpp fences — use `text` or `pseudo` instead.
4. **Front-matter is required** on every `*.instructions.md`, `*.chatmode.md`, `*.prompt.md`.
   See [`.github/instructions/prompt-authoring.instructions.md`](.github/instructions/prompt-authoring.instructions.md).
5. **CHANGELOG.md must be updated** for any non-trivial change to a session script, demo
   workspace, instruction file, or chat mode.
6. **Branches and PRs**, never direct commits to `main`. Use `feat/sessionNN-…`,
   `fix/…`, `chore/…` naming.
7. **Reviewer chat mode** (`reviewer.chatmode.md`) must be invoked on any new session bundle
   before opening a PR. The Critical/Significant findings gate the merge.

## Build & validation commands (memorize these)

```bash
npm install
npm run lint                 # markdownlint + prettier check
npm run format               # prettier write
npm run links                # lychee link checker
npm run validate:snippets    # extract fenced C++ → CMake build → GTest
npm run validate:prompts     # prompt-conformance check
npm run scaffold:session     # bootstrap a new sessions/NN-* folder from template
```

CI runs the same commands on every PR (see `.github/workflows/`). If something fails locally,
fix it locally before pushing.

## File-authoring conventions

- **Markdown**: ATX headings, dash bullets, fenced code with explicit language tag, soft wrap
  ~100 columns, relative links only, never link to absolute file paths on a contributor's
  machine.
- **YAML**: 2-space indent, no tabs, double-quoted strings when in doubt.
- **Filename casing**: kebab-case for all docs and prompt files. Do not invent new naming
  schemes.
- **Front-matter**: YAML, sandwiched between `---` markers, at the very top of the file.

## Hand-off conventions between chat modes

The repo defines four orchestration modes plus three specialist modes. They communicate via
**files**, never via in-memory state:

| Producer mode                   | Output location                        | Consumer mode                        |
| ------------------------------- | -------------------------------------- | ------------------------------------ |
| `planner.chatmode.md`           | `docs/plans/<slug>.md`                 | `builder.chatmode.md`                |
| `builder.chatmode.md`           | session/demo-workspace files           | `reviewer.chatmode.md`               |
| `reviewer.chatmode.md`          | `sessions/<n>/review-report.md`        | `builder.chatmode.md` (fix)          |
| `squad-coordinator.chatmode.md` | `docs/plans/squad-<task>/decisions.md` | `cpp-architect`/`developer`/`tester` |

Specialist modes write under `docs/plans/squad-<task>/` and never touch the canonical
session files directly — the coordinator merges their outputs.

## Safety boundaries

- **Tool approvals**: `runCommands` is granted only to `builder` and the three `cpp-*`
  specialists, and only with HITL approval per command. `planner` and `reviewer` are
  read-only.
- **Network access**: only the `github` MCP server may make outbound requests, and only with
  a PAT the user supplies at session start.
- **Destructive actions**: agents must never `rm -rf`, force-push, rewrite history, or
  delete the `output/` tree without an explicit human instruction. Use `git restore` for
  reverts, never `git reset --hard`.

## Where to look first

- The plan: [`docs/engagement-charter.md`](docs/engagement-charter.md).
- The build DAG: [`docs/build-graph.md`](docs/build-graph.md).
- The escalation rules: [`docs/escalation-paths.md`](docs/escalation-paths.md).
- The C++ rule of law: [`.github/instructions/cpp-snippets.instructions.md`](.github/instructions/cpp-snippets.instructions.md).
