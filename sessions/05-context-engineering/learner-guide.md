# Session 05 — Context Engineering at Scale (learner guide)

## Before you start

- Sessions 02–04 fixes merged.
- Skim [`docs/context-belt.md`](../../docs/context-belt.md) and [`.github/instructions/cpp-snippets.instructions.md`](../../.github/instructions/cpp-snippets.instructions.md).

## Outcomes

1. Use the 5-strand belt taxonomy (signal/anchor/spec/exemplar/test) consciously.
2. Promote stable strands to scoped `applyTo` instruction files.
3. Choose the right chat mode for the right job; understand tool allowlists.
4. Explain the difference between Ask, Edit, and Agent mode and know when to use each.
5. Call an MCP tool from Agent mode using the workshop's `.vscode/mcp.json`.

## VS Code Copilot Chat tab orientation

| Tab       | What it does                                         | When to use it                                         |
| --------- | ---------------------------------------------------- | ------------------------------------------------------ |
| **Ask**   | Explores, answers, summarizes — no file edits        | Comprehension, enumeration, planning                   |
| **Edit**  | Applies diffs to files with your approval            | Targeted refactor, test authoring, single-feature work |
| **Agent** | Invokes tools (terminal, file I/O, MCP) autonomously | Multi-step tasks, Coding Agent hand-offs, MCP demos    |

> **Note:** `planner.chatmode.md` and `builder.chatmode.md` are _custom chat modes_ (personas + tool allowlists we authored). They are not the same as the Ask/Edit/Agent product tabs — they layer on top of any tab.

## Walk-through

### The 5 strands

| Strand   | Example                               |
| -------- | ------------------------------------- |
| Signal   | failing test, stack frame, log line   |
| Anchor   | the .cpp under suspicion              |
| Spec     | constitution, instruction file        |
| Exemplar | analogous passing module              |
| Test     | DISABLED\_ regression, existing GTEST |

### Promote to instruction file

Front-matter required: `description`, `applyTo`, `last_reviewed`, `reviewer`. See [`.github/instructions/prompt-authoring.instructions.md`](../../.github/instructions/prompt-authoring.instructions.md) for the schema.

### Pick a chat mode

| Need                                | Mode                |
| ----------------------------------- | ------------------- |
| Read-only exploration / plan only   | `planner`           |
| Apply edits with HITL on commands   | `builder`           |
| Adversarial review                  | `reviewer`          |
| Multi-agent orchestration (S08–S09) | `squad-coordinator` |

### MCP tools in Agent mode

The workshop ships with `.vscode/mcp.json` wiring two read-only MCP servers:

- **filesystem** — scoped to `output/ea-cpp-games/`, `sessions/`, `docs/`.
- **github** — public GitHub API; PAT prompted on first use (never stored in the file).

In Agent mode, ask Copilot to use a tool explicitly:

```text
Use the filesystem tool to list all files under output/ea-cpp-games/specs/.
Then open specs/constitution.md and tell me how many articles it defines.
```

Copilot shows a tool-call badge (gear icon) and cites live file content, not training data.

> **EA parallel:** an EA-internal symbol-search or change-attribution service would follow the same pattern — read-only stdio server, PAT via `${input:...}`, no secrets in the file.

## Try it yourself

- [Exercise 01 — author a scoped instruction file](exercises/01-author-instructions.md)
- [Exercise 02 — pick the right chat mode](exercises/02-pick-the-mode.md)

## Troubleshooting

| Symptom                                    | Fix                                                         |
| ------------------------------------------ | ----------------------------------------------------------- |
| `validate:prompts` rejects my front-matter | Compare to schema; check `last_reviewed` < 90 days.         |
| `applyTo` matches too much / too little    | Test with `git ls-files \| grep -E '<glob>'` mentally.      |
| Reviewer mode appears to edit              | It can't. Re-read the answer; "edits" are suggestions only. |

## Going further

- Build a private instruction file for your team's lint rules and circulate it.

## Feedback

[`retro-survey.md`](retro-survey.md).
