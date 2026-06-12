# Exercise 01 — Author a scoped instruction file

**Time:** 15 min · **Difficulty:** intermediate

## Goal

Draft `.github/instructions/test-authoring.instructions.md` (or your own variant) with valid front-matter and an `applyTo` glob that targets `tests/**/*.cpp`. Get `npm run validate:prompts` green.

## Steps

1. Copy the front-matter shape from `cpp-snippets.instructions.md`.
2. Body: 3–5 rules specific to GTest authoring in this workspace (e.g., "use `EXPECT_*` over `ASSERT_*` unless continuation is unsafe").
3. Run `npm run validate:prompts`.

## Acceptance

- Validator passes.
- The file follows the [schema](../../../.github/instructions/prompt-authoring.instructions.md) exactly.
- `applyTo` is narrow enough to target only test files, not production code.

## Reflection

Which rule did you almost put in `cpp-snippets.instructions.md` but rightly kept here? Explain why scoping matters.
