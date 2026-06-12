# Session 05 — Context Engineering at Scale (facilitator script)

> **Cross-references:** [`learner-guide.md`](learner-guide.md) · [`slides.outline.md`](slides.outline.md) · [`retro-survey.md`](retro-survey.md) · [exercises](exercises/)

## Session at a glance

- **Duration:** 60 min · **Level:** advanced · **Plan tier:** Business
- **Outcomes:**
  1. Internalize the **context belt** taxonomy: signal/anchor/spec/exemplar/test.
  2. Use **scoped instruction files** (`applyTo`) to make context implicit.
  3. Apply **chat-mode tool allowlists** to constrain Copilot's blast radius.

## Pre-session checklist (T-15 min)

> **Do:** open `docs/context-belt.md` (canonical reference) in a side panel.
> **Do:** open one scoped instruction (`.github/instructions/cpp-snippets.instructions.md`) and one chat mode (`.github/chatmodes/builder.chatmode.md`).

## Opening (0:00 – 0:05)

> **Say:** "Sessions 1–4 used context belts intuitively. Today we name them, taxonomize them, and turn them into reusable artifacts. The unit of reuse is the instruction file."

## Block 1: The 5-part belt (0:05 – 0:20)

> **Say:** "Every effective Copilot prompt carries up to five context strands."

| Strand   | What it is                            | Example                                      |
| -------- | ------------------------------------- | -------------------------------------------- |
| Signal   | The symptom or trigger                | A failing test, a stack frame, a log line    |
| Anchor   | The single file most likely to change | The .cpp under suspicion                     |
| Spec     | The constraints any fix must honor    | `specs/constitution.md`, an instruction file |
| Exemplar | A neighboring file done correctly     | A passing test, an analogous module          |
| Test     | The acceptance criterion              | The DISABLED\_ regression, an existing GTEST |

> **Do:** live, build a 5-strand belt for a hypothetical "thread-pool starvation" symptom. Don't fix anything — just compose the belt.

## Block 1.5: VS Code Agent mode (0:18 – 0:20) — orientation

> **Say:** "Before we get into instruction files, a quick orientation on the third tab we haven't used yet: **Agent mode**."

| Tab       | What it does                                          | When to use it                                         |
| --------- | ----------------------------------------------------- | ------------------------------------------------------ |
| **Ask**   | Explores, answers, summarizes — no file edits         | Comprehension, enumeration, planning                   |
| **Edit**  | Applies diffs to one or more files with your approval | Targeted refactor, test authoring, single-feature work |
| **Agent** | Invokes tools (terminal, file I/O, MCP) autonomously  | Multi-step tasks, Coding Agent hand-offs, MCP demos    |

> **Say:** "Agent mode picks up instruction files from `.github/copilot-instructions.md` and from any scoped `*.instructions.md` that matches the current file — automatically, without a `#file:` reference. That's the payoff of what we build today."

> **Note for facilitator:** VS Code Agent mode (synchronous, in-editor) is distinct from the **GitHub Copilot Coding Agent** (async, opens a PR, runs in a cloud sandbox). We cover the cloud Coding Agent in Session 08.

## Block 2: Scoped instruction files (0:20 – 0:40)

> **Say:** "When a strand never changes, promote it to an instruction file with `applyTo`."

> **Do:** walk the existing `cpp-snippets.instructions.md`. Highlight: front-matter, `applyTo` glob, body sections.

> **Do:** in the **Edit** tab (draft in Ask first, then apply in Edit), draft a _new_ instruction file: `.github/instructions/test-authoring.instructions.md` scoped to `tests/**/*.cpp`. Single-author it together. Run `npm run validate:prompts` — must pass.

> **HITL gate:** before saving, the facilitator reads the front-matter aloud. Confirm `last_reviewed`, `applyTo`, `description`.

## Block 3: Chat-mode tool allowlists (0:40 – 0:55)

> **Say:** "The most dangerous strand is the one you forget to _exclude_. Chat modes solve this by enumerating allowed tools."

> **Do:** open `chat-mode-authoring.instructions.md`. Walk the matrix. Emphasize: planner = read-only; builder = HITL on `runCommands`; reviewer = read + read-only terminal.

> **Do:** demo invoking the `reviewer` chat mode on a recent diff and observe that it **cannot** edit. Try to coax it into editing — confirm it refuses (this is the artifact).

## Block 3.5: MCP demo — tools from chat (0:52 – 0:55)

> **Say:** "The last lever in context engineering is MCP — Model Context Protocol. It lets you wire in external read-only tools that Copilot can call live during a conversation, in Agent mode."

> **Do:** show `.vscode/mcp.json` (already in the repo):

```json
{
  "servers": {
    "filesystem": {
      "command": "npx",
      "args": [
        "-y",
        "@modelcontextprotocol/server-filesystem",
        "output/ea-cpp-games",
        "sessions",
        "docs"
      ],
      "type": "stdio"
    },
    "github": {
      "command": "npx",
      "args": ["-y", "@modelcontextprotocol/server-github"],
      "type": "stdio",
      "env": { "GITHUB_TOKEN": "${input:github_pat}" }
    }
  },
  "inputs": [
    {
      "id": "github_pat",
      "type": "promptString",
      "description": "GitHub PAT (read-only)",
      "password": true
    }
  ]
}
```

> **Say:** "Two public servers: `filesystem` scoped to three directories (read-only), and `github` that authenticates via a PAT you enter once — never embedded in the file."

> **Do:** in Agent mode, call the filesystem tool live:

```text
Use the filesystem tool to list all files under output/ea-cpp-games/specs/.
Then open specs/constitution.md and tell me how many articles it defines.
```

> **Watch for:** Copilot shows a tool-call badge (the gear icon) before responding. The response cites the actual file content, not training data.

> **Say:** "An EA team would swap these public servers for an internal symbol-search or change-attribution service, with the same read-only, no-secrets constraints we just saw. The `.vscode/mcp.json` file is the config contract."

## Q&A (0:55 – 0:58)

- **Q: "How do I migrate my team's existing 'best practices.md' to instruction files?"** → "One instruction file per scope. Don't try to compress everything into copilot-instructions.md."

## Retro micro-survey (0:58 – 1:00)

> **Do:** post [`retro-survey.md`](retro-survey.md).

## Stretch goals

- Author a chat mode for a niche your team needs (e.g., "shader-author") with a tool allowlist.

## Recovery script

If the new instruction file fails `validate:prompts`: walk the failure live; use it as a teaching moment about front-matter discipline.

## Post-session checklist

- Confirm the new `test-authoring.instructions.md` is committed.
- Update `docs/context-belt.md` with any new patterns surfaced.
