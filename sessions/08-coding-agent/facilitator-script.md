# Session 08 — Multi-Agent Pt 1: Coding Agent (facilitator script)

> **Cross-references:** [`learner-guide.md`](learner-guide.md) · [`slides.outline.md`](slides.outline.md) · [`retro-survey.md`](retro-survey.md) · [exercises](exercises/)

## Session at a glance

- **Duration:** 60 min · **Level:** advanced · **Plan tier:** **Enterprise**
- **Demo target:** delegate a small, well-scoped task ("add an `engine_demo::frame_budget::reset()` method with a regression test") to the GitHub Copilot Coding Agent. Watch the PR.
- **Outcomes:**
  1. Run an end-to-end coding-agent task: dispatch → poll → review → merge.
  2. Apply the **scope rubric** (deterministic / well-tested / single-PR-sized).
  3. Use the pre-merged Plan-B PR as a fallback when the live agent is slow.

## Two-agents orientation (before opening)

Before the session starts, put this table on the slide:

| Agent                                     | Where it runs          | Invocation                           | Output       | Best for                         |
| ----------------------------------------- | ---------------------- | ------------------------------------ | ------------ | -------------------------------- |
| **VS Code Agent mode** (Edit → Agent tab) | In-editor, synchronous | Click Agent tab in Copilot Chat      | Inline edits | Multi-step tasks, MCP tool calls |
| **GitHub Copilot Coding Agent**           | Cloud sandbox, async   | Assign issue to `@copilot` on GitHub | Pull Request | Delegated tasks; well-scoped PRs |

> **Say:** "We've been using VS Code Agent mode since Session 05 — that's the Agent tab in Copilot Chat, running in your editor. Today's new thing is the _other_ agent: the GitHub Copilot Coding Agent. It runs in a cloud sandbox, operates asynchronously, and hands you back a pull request to review."

## Pre-session checklist (T-15 min)

> **Do:** confirm the repo's coding-agent bootstrap is green: `.github/workflows/copilot-coding-agent-bootstrap.yml` last run successful.
> **Do:** confirm a Plan-B PR is open and ready (pre-merged equivalent of the live demo task) so we can pivot if agent latency spikes.
> **Do:** open `output/ea-cpp-games/include/engine_demo/frame_budget.h` and the test file in two panes.
> **Watch for:** agent queue depth — if > 5 jobs, take Plan-B from the start.

## Opening (0:00 – 0:05)

> **Say:** "We've made every choice ourselves. Today we delegate one — to an agent that runs asynchronously, opens a PR, and waits for our review. The skill we're building is choosing what's safe to delegate."

## Block 1: Scope rubric (0:05 – 0:15)

> **Say:** "Three criteria: deterministic, well-tested, single-PR-sized. If any are missing, the agent is the wrong tool."

> **Do:** walk three candidate tasks; rank against the rubric:
>
> 1. "Add a `reset()` method to frame_budget" — passes.
> 2. "Refactor the constraint solver to be deterministic" — fails (not single-PR-sized; coupling risk).
> 3. "Update CMake presets to add a sanitizer build" — passes (deterministic, easy to roll back).

## Block 2: Dispatch + observe (0:15 – 0:40)

> **Do:** assign the agent in GitHub:

```text
@copilot Add a public method `reset()` to engine_demo::frame_budget that clears
m_samples, m_index, m_count. Add a passing regression test in tests/engine_demo/
test_frame_budget.cpp asserting that rolling_average() returns 0.0 after reset(). Honor
constitutional articles 1, 2, 7. Open a PR against this branch.
```

> **Watch for:** the agent picks up the issue, opens a PR, runs CI. While waiting:

> **Say:** "Let's talk about what _not_ to delegate."

> **Do:** discuss the three failure modes — silent broken contracts, incorrect test placement, scope creep — using anecdotes from prior sessions.

> **HITL gate:** when the PR opens, switch to the reviewer chat mode:

```text
Use the reviewer chat mode. Severity-rate the agent's PR diff.
```

> **Watch for:** zero Critical findings. If Plan-B is needed, pivot now.

## Block 3: Merge or recover (0:40 – 0:55)

> **Do:** if green, merge the PR. If not, demonstrate iteration:

```text
@copilot The PR's regression test asserts rolling_average() == 0.0 but the implementation
returns 0.0/0 (NaN) when m_count == 0. Fix the test to assert sample_count() == 0 instead,
or update the implementation to early-return 0.0.
```

> **Watch for:** clean iteration. Demonstrate that the agent updates the same PR.

## Block 3.5: Configuring the Coding Agent (0:52 – 0:55)

> **Say:** "You can configure what tools and MCP servers the Coding Agent has access to, via a `copilot-setup-steps.yml` file in `.github/`."

> **Do:** show the concept (no live edit needed; walk the shape):

```yaml
# .github/copilot-setup-steps.yml
# Controls tools available to the GitHub Copilot Coding Agent in this repo.
# See: https://docs.github.com/en/copilot/how-tos/agents/copilot-coding-agent/customizing-copilot-coding-agent-with-mcp

pre-install:
  - run: npm install --prefix output/ea-cpp-games # install any build deps

mcp:
  servers:
    filesystem:
      command: npx
      args: ["-y", "@modelcontextprotocol/server-filesystem", "output/ea-cpp-games"]
      type: stdio
```

> **Say:** "The `mcp.servers` block mirrors what's in `.vscode/mcp.json` — same servers, same read-only constraint. This is how you give the cloud agent context about your codebase without granting write access to arbitrary paths."

> **Note for facilitator:** as of 2025, `copilot-setup-steps.yml` is the approved configuration mechanism. The GitHub docs link in the YAML comment is the canonical reference. Check for updates before each cohort.

## Q&A (0:55 – 0:58)

- **Q: "What about flaky tests?"** → "The agent will not fix a flake; it'll surface it as a comment. Treat that as a separate human task."
- **Q: "Coding agent vs. squad pattern?"** → "Session 09 — same primitives, different orchestration."

## Retro micro-survey (0:58 – 1:00)

> **Do:** post [`retro-survey.md`](retro-survey.md).

## Stretch goals

- Open a second issue with deliberately ambiguous scope. Watch the agent ask clarifying questions in the PR description.

## Recovery script — Plan-B PR

If the live agent is slow:

> **Do:** open the pre-merged Plan-B PR. Walk its diff, review markup, and CI run as if it were live. Acknowledge the substitution.

## Post-session checklist

- Note the PR number for the live (or Plan-B) demo in the session retrospective.
- Capture any agent latency observations for delivery runbook updates.
