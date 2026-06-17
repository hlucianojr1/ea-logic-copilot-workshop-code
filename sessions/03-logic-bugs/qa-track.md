# Session 03 — QA Track: Verifying Logic-Bug Fixes

> **Audience:** QA engineers and SDETs. The developer track
> ([learner-guide.md](learner-guide.md), [sdlc-walkthrough.md](sdlc-walkthrough.md))
> covers _finding and fixing_; this track covers _proving the fix and gating the merge_.
> You don't need to write the fix — you need to be unfoolable about whether it works.

## Outcomes

By the end of this track you can:

- Author a Copilot-assisted test plan for a seeded logic bug before seeing any fix.
- Triage Copilot bug-hunt output into real defects vs. false positives using a rubric.
- Operate the four HITL gates as the sign-off authority, with written verdicts.
- Use headless trace comparison as a quantitative regression metric.

## 1. Author the test plan first

QA enters at the _issue_ stage, before a branch exists. Draft a test plan from the bug
report alone:

```text
#file:output/ea-cpp-games/fixtures/bug-reports/BUG-002.md
#file:output/ea-cpp-games/specs/constitution.md
Draft a test plan for verifying a fix to this bug. Include: (1) the exact failing
condition as a testable assertion, (2) boundary cases the fix must not regress,
(3) which build presets must be exercised (default-debug / optimized / tsan) and why,
(4) a determinism check using the headless sandbox trace. Do not propose a fix.
```

Quality bar for accepting the plan:

- Every assertion is executable — a ctest filter or a trace diff, not "verify it works".
- Preset selection is justified per bug class: optimizer-sensitive bugs (BUG-007) need
  `optimized`; concurrency bugs (BUG-009) need `tsan`; everything needs `default-debug`.
- The plan distinguishes "the bug no longer manifests" from "the defect is removed" —
  for races and UB those are different claims (see Exercise 05's stretch question).

## 2. Triage rubric — real bug or false positive?

When Copilot hunts for defects it will surface both. The demo workspace seeds three
deliberate false positives to practice on. For every candidate, run this rubric in
order and stop at the first failure:

| #   | Check     | Pass means…                                                         |
| --- | --------- | ------------------------------------------------------------------- |
| 1   | Reproduce | A failing test exists in <5 lines, or a TSAN/UBSan report is shown. |
| 2   | Trace     | The data flow from cause to symptom is traceable in the code.       |
| 3   | Cite      | A constitution article (or CWE) is genuinely violated.              |
| 4   | Disprove  | An attempt to _disprove_ the claim was made and failed.             |

Calibration set — verdicts you should reach:

- **FP-001 / FP-002** (see `fixtures/seeded-bugs.md`): fail the rubric at step 1 or 2.
- **FP-003** — "m*ready is not atomic": fails at step 2. The flag \_is*
  `std::atomic<bool>`; the real defect (BUG-009) is the relaxed _ordering_. A dismissal
  must say what _is_ correct, not just "false positive".
- **BUG-004, BUG-008**: pass all four — note that intermittent reproduction (BUG-008's
  padding) still counts at step 1 if the test fails reliably across a small batch of runs.

Write each dismissal as one sentence in the PR thread. Silent dismissals don't count —
the next hunter will surface the same candidate again.

## 3. Gate sign-off — the QA half of HITL

In the [SDLC walkthrough](sdlc-walkthrough.md) the developer drives the agent; QA owns
the verdicts. Use this template per gate (copy into the PR or issue thread):

```text
Gate N: <PLAUSIBLE | COMPLIANT | REPRODUCED | MINIMAL> — <APPROVED | REJECTED>
Evidence: <file:line, test name, or ctest/TSAN output quoted>
Checked by: <name>, <date>
```

Gate-specific verification, beyond reading the agent's claims:

- **Gate 1 (hypothesis):** run the disproof yourself. If the hypothesis is "float
  accumulator", confirm the member really is `float` at the cited line.
- **Gate 2 (constitution):** grep the proposed diff for the hot-list patterns
  (`std::vector`, `try`, C-style casts — see
  [cpp-snippets.instructions.md](../../.github/instructions/cpp-snippets.instructions.md)).
- **Gate 3 (test reproduces):** check out the branch _before_ the fix commit and run
  the enabled test — it must fail. Commit order is evidence; trust the history, not
  the PR description.
- **Gate 4 (fix minimal):** `git diff --stat` — files touched beyond the defect and its
  test require justification or rejection.

## 4. Regression metrics — trace comparison

Pass/fail tests answer "does the assertion hold". For determinism and drift bugs, QA
also wants "did anything _else_ change". The headless sandbox provides that:

```bash
cd output/ea-cpp-games
# Baseline on main, candidate on the fix branch — same seed, same frame count:
./build/apps/sandbox/ea-sandbox --headless --seed 42 --frames 600 --out trace-main.csv
git switch fix/bug-002-accumulator-drift && cmake --build --preset default-debug
./build/apps/sandbox/ea-sandbox --headless --seed 42 --frames 600 --out trace-fix.csv
diff trace-main.csv trace-fix.csv | head -20
```

Interpretation:

- **Determinism fix (BUG-004):** post-fix, repeated runs with the same seed produce
  byte-identical traces. Pre-fix they don't. Run it three times — once is luck.
- **Drift fix (BUG-002):** the divergence between sim-time and wall-time columns stays
  bounded over the full 600 frames instead of growing.
- **Any other diff lines** are unexplained behavior changes — Gate 4 material. A fix
  that "also" changes unrelated trace columns is not minimal.

Record the trace command lines and result summary in the sign-off; CSVs attach to the PR.

## 5. The sign-off checklist

Merge requires all of:

- [ ] Test plan (Section 1) existed before the fix branch.
- [ ] All triage candidates dispositioned — real bugs have tests, FPs have one-line
      dismissals (Section 2).
- [ ] Four gate verdicts recorded with evidence (Section 3).
- [ ] Regression test passes under every preset the test plan named.
- [ ] Trace comparison clean or every diff line explained (Section 4).
- [ ] `DISABLED_` prefix restored on the regression test after verification, with the
      fix verified in the same PR.

## Try it yourself

Run this track end-to-end against **BUG-008** (Exercise
[04-bitwise-vs-logical.md](exercises/04-bitwise-vs-logical.md)) with a partner driving
the developer track. The intermittent failure mode makes the "reproduce reliably across
a batch" judgment call real rather than theoretical.

## Going further

- [Exercise 05](exercises/05-atomic-but-not-ordered.md) — FP-003 triage under TSAN.
- [sdlc-walkthrough.md](sdlc-walkthrough.md) — the developer half of this loop.
- [retro-survey.md](retro-survey.md) — leave feedback on this track.
