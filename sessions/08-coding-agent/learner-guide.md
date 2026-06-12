# Session 08 — Coding Agent (learner guide)

## Before you start

- Enterprise plan access; coding-agent bootstrap workflow green.
- A Plan-B PR is pre-merged in the repo (the facilitator will surface it if needed).

## Outcomes

1. Distinguish VS Code Agent mode (in-editor, synchronous) from the GitHub Copilot Coding Agent (cloud, async, PR-based).
2. Dispatch a task to the Copilot Coding Agent and review the resulting PR.
3. Apply the scope rubric: deterministic / well-tested / single-PR-sized.
4. Understand how `copilot-setup-steps.yml` configures Coding Agent tool access.
5. Recover gracefully when the live agent is slow.

## Two agents

| Agent                           | Where it runs   | Invocation                        | Output       |
| ------------------------------- | --------------- | --------------------------------- | ------------ |
| **VS Code Agent mode**          | In-editor, sync | Agent tab in Copilot Chat         | Inline edits |
| **GitHub Copilot Coding Agent** | Cloud, async    | Assign GitHub issue to `@copilot` | Pull Request |

## Walk-through

### Scope rubric

| Criterion       | Question                                               |
| --------------- | ------------------------------------------------------ |
| Deterministic   | Can two humans agree on what "done" looks like?        |
| Well-tested     | Is there a green baseline ctest? An obvious assertion? |
| Single-PR-sized | Would you, as a reviewer, accept one PR for it?        |

### Dispatch

```text
@copilot Add a public method `reset()` to engine_demo::frame_budget that clears
m_samples, m_index, m_count. Add a passing regression test asserting that
rolling_average() returns 0.0 (or sample_count() == 0) after reset(). Honor articles 1, 2, 7.
```

### Review

Use the reviewer chat mode on the PR diff. Look for: API contract drift, test placement, constitutional violations.

### Iterate or merge

If issues: comment on the PR with a precise fix. The agent updates the same PR. If clean: merge.

### Configure agent tool access

`.github/copilot-setup-steps.yml` controls which tools and MCP servers the Coding Agent can call:

```yaml
pre-install:
  - run: npm install --prefix output/ea-cpp-games

mcp:
  servers:
    filesystem:
      command: npx
      args: ["-y", "@modelcontextprotocol/server-filesystem", "output/ea-cpp-games"]
      type: stdio
```

This mirrors `.vscode/mcp.json` — same servers, same read-only constraint, but for the cloud agent.

## Try it yourself

- [Exercise 01 — score three candidate tasks](exercises/01-score-tasks.md)
- [Exercise 02 — your own dispatch](exercises/02-dispatch.md)

## Troubleshooting

| Symptom                               | Fix                                                      |
| ------------------------------------- | -------------------------------------------------------- |
| Agent doesn't pick up issue           | Check the bootstrap workflow ran; check Enterprise plan. |
| PR fails CI                           | Comment with a specific fix; agent iterates on same PR.  |
| Agent ignores constitutional articles | Re-prompt with explicit citations.                       |
| Latency > 15 min                      | Pivot to the Plan-B PR. Don't wait the session out.      |

## Going further

- Session 09 layers a coordinator over multiple specialist chat modes for the same primitives.

## Feedback

[`retro-survey.md`](retro-survey.md).
