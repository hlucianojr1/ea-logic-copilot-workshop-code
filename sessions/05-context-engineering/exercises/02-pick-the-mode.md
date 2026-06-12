# Exercise 02 — Pick the right chat mode

**Time:** 10 min · **Difficulty:** beginner

## Goal

For each scenario below, name the correct chat mode and the single most-load-bearing element of its tool allowlist.

## Scenarios

1. You suspect BUG-007 in a new subsystem and want to enumerate candidates. **Mode?**
2. You have a green diff and want adversarial review before PR. **Mode?**
3. You are kicking off a multi-agent decomposition for a ring-buffer feature. **Mode?**
4. You need to apply a 4-line fix and rerun ctest. **Mode?**
5. You are designing a new API surface but not yet writing it. **Mode?**

## Acceptance

Answers: `planner`, `reviewer`, `squad-coordinator`, `builder`, `cpp-architect`.

For each, you can articulate which tool the mode allows or denies that drove your choice.

## Reflection

Which mode would tempt you to "just give it edit access for one task"? Resist. The blast-radius argument always wins.
