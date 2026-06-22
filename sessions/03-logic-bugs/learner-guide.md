# Session 03 — Logic Bugs (learner guide)

> **Cross-references:** [facilitator-script.md](facilitator-script.md) ·
> [logic-bug-workshop-training.md](logic-bug-workshop-training.md) · [exercises](exercises/) ·
> [sdlc-walkthrough.md](sdlc-walkthrough.md) · [qa-track.md](qa-track.md) ·
> [retro-survey.md](retro-survey.md)

This guide is self-contained: you can run the whole session **solo**, without a facilitator.
You have two ways to work through it — pick one:

- **Self-guided (recommended):** let the **`logic-bug-tutor`** agent pace you, one bug at a
  time, with built-in human-in-the-loop gates. See [Before you start](#before-you-start).
- **Manual:** copy the prompts in [Walk-through](#walk-through) into Copilot Chat yourself.

- **Level:** advanced · **Duration:** ~60 min · **Plan tier:** Business

## Before you start

### Prerequisites

- **VS Code** with the **GitHub Copilot** and **GitHub Copilot Chat** extensions, signed in.
- A C++20 toolchain: **CMake ≥ 3.21**, **Ninja**, and a compiler (Clang, AppleClang, or MSVC).
- **vcpkg** cloned locally, with the `VCPKG_ROOT` environment variable pointing at it. On
  macOS arm64 the demo is verified with AppleClang and the `arm64-osx` triplet (Xcode CLT +
  Homebrew `ninja` and `pkg-config`).

### Build and confirm the green baseline

Open `output/ea-cpp-games/` and, from that folder, configure, build, and test:

```bash
cd output/ea-cpp-games
cmake --preset default-debug
cmake --build --preset default-debug
ctest --preset default-debug --output-on-failure
```

All enabled tests must pass and the seeded regressions must still be `DISABLED_`. That clean,
green tree is your starting line — do not begin a bug until you see it.

### Files you will touch

- `output/ea-cpp-games/specs/constitution.md` — the eight engine rules. Skim **Article 5
  (determinism)**; it is the article most of today's bugs violate.
- `output/ea-cpp-games/src/engine_demo/sim/game_loop.cpp` + its header (BUG-002).
- `output/ea-cpp-games/src/engine_demo/frame_budget.cpp` + its header (BUG-006).
- `output/ea-cpp-games/fixtures/bug-reports/` — one report per bug.

### Start the self-guided tutor

1. Open the Copilot Chat view (Ask / Edit / Agent tabs).
2. From the **agents dropdown**, select **`logic-bug-tutor`**.
3. Type `start`. The tutor checks your baseline, then walks you through OBSERVE → REPRODUCE →
   FIX → VERIFY for each bug, pausing for your approval before any edit.

Prefer to drive manually? Skip the tutor and follow the prompts below.

## Outcomes

1. Apply the **observe → reproduce → bisect** pattern to a non-crashing logic bug.
2. Author a **minimal failing test before** writing any fix (Article 7, test-first).
3. Distinguish numerical **drift** (BUG-002) from an **off-by-one** (BUG-006) by their repro
   shape.
4. Gate every fix behind a human-in-the-loop approval (Article 8).

## Walk-through

Work each bug as a four-phase loop. Every prompt below is copy-paste ready — paste it into the
named Copilot tab exactly as written.

### BUG-002 — accumulator drift (numerical)

**1. Observe.** In the **Ask** tab:

```text
#file:output/ea-cpp-games/include/engine_demo/sim/game_loop.h
#file:output/ea-cpp-games/src/engine_demo/sim/game_loop.cpp
#file:output/ea-cpp-games/specs/constitution.md
A long replay diverges from a reference run after ~30 simulated seconds. Identify any
violation of the constitution's article 5 in this code.
```

Copilot should point at `float m_accumulator_seconds` and cite Article 5.

**2. Reproduce (test-first).** In the **Ask** tab:

```text
#file:output/ea-cpp-games/tests/engine_demo/test_game_loop.cpp
Re-enable DISABLED_long_run_does_not_drift. Confirm it fails. State, in one sentence, why
it fails.
```

Then run just that test and watch it go red (from `output/ea-cpp-games/`):

```bash
cd output/ea-cpp-games
cmake --build --preset default-debug
ctest --preset default-debug --output-on-failure -R test_game_loop
```

**3. Fix.** In the **Edit** tab:

```text
#file:output/ea-cpp-games/include/engine_demo/sim/game_loop.h
#file:output/ea-cpp-games/src/engine_demo/sim/game_loop.cpp
Promote m_accumulator_seconds from float to double. Remove the now-unnecessary casts.
Constitutional articles 1, 2, 5 must hold.
```

Review the diff before accepting it. If Copilot leaves the old `static_cast<float>` calls in,
ask: "are any casts now redundant?"

**4. Verify.** Re-run the single test (now green), then the full suite:

```bash
cd output/ea-cpp-games
ctest --preset default-debug --output-on-failure
```

> **What good looks like:** your diff widens `m_accumulator_seconds` to `double` and removes
> the redundant `static_cast<float>` casts — two files (header + source), no new guard, no
> `std::`. The re-enabled `long_run_does_not_drift` test passes and the suite stays green.
>
> **Reset before the next bug:** return to the clean baseline so BUG-006 starts fresh. In the
> **Agent** panel, run:

```text
@logic-bug-tutor
I finished BUG-002. Reset output/ea-cpp-games/ to the clean seeded baseline (revert my fix,
re-DISABLE_ the test, rebuild) and confirm ctest --preset default-debug is green before BUG-006.
```

Manual equivalent: from `output/ea-cpp-games/`, run `git restore src/engine_demo
include/engine_demo tests/engine_demo` then `cmake --build --preset default-debug`.

### BUG-006 — rolling-window off-by-one

**1. Observe.** In the **Ask** tab, make Copilot enumerate slot states rather than infer them:

```text
#file:output/ea-cpp-games/include/engine_demo/frame_budget.h
#file:output/ea-cpp-games/src/engine_demo/frame_budget.cpp
After three calls to record_sample(2.0), record_sample(4.0), record_sample(6.0) on a
freshly-constructed frame_budget(window_size=4), state the value of every slot in
m_samples[] and the value you would expect from rolling_average(). Show your math.
```

Copilot predicts `(2+4+6)/3 = 4.0`. Now make it read the actual code:

```text
Now read the actual code: what does rolling_average() compute, byte for byte, on the
above input? Reconcile with your prediction.
```

The gap between the prediction (the spec) and the trace (the code) is the bug.

**2. Reproduce + 3. Fix.** In the **Edit** tab:

```text
#file:output/ea-cpp-games/src/engine_demo/frame_budget.cpp
Fix rolling_average so it iterates the most-recent m_count samples in wrap order
starting from (m_index - m_count) mod m_window_size. Re-enable
DISABLED_first_sample_is_not_double_counted_on_warmup.
```

**4. Verify.** Run the full suite and confirm green:

```bash
cd output/ea-cpp-games
ctest --preset default-debug --output-on-failure
```

> **What good looks like:** `rolling_average()` iterates the most-recent `m_count` samples in
> wrap order and no longer double-counts the warm-up sample. The re-enabled
> `first_sample_is_not_double_counted_on_warmup` test passes and the suite stays green.

### The rest of the set — let the tutor pace you

The advanced path adds five more bugs. The compact reference below keeps this guide
self-contained; the **`logic-bug-tutor`** agent runs the full four-phase loop for each, and
[logic-bug-workshop-training.md](logic-bug-workshop-training.md) has the deep dives.
Hands-on exercise files for BUG-007, 008, 009, and 010 are in [exercises/](exercises/).

| Bug     | Files (under `output/ea-cpp-games/`)         | Re-enable this test                                          | One-line fix                                          |
| ------- | -------------------------------------------- | ------------------------------------------------------------ | ----------------------------------------------------- |
| BUG-004 | `src/engine_demo/physics/constraint.{h,cpp}` | `DISABLED_solve_is_deterministic_across_construction_orders` | Sort constraints; read bodies via a dense index       |
| BUG-007 | `src/engine_demo/sim/timer.{h,cpp}`          | `DISABLED_overflow_guard_not_elided`                         | `m_elapsed_ms` `int32_t` → `uint64_t`; drop the guard |
| BUG-008 | `src/engine_demo/sim/replay_state.{h,cpp}`   | `DISABLED_padding_does_not_affect_comparison`                | Replace `memcmp` with member-wise comparison          |
| BUG-009 | `src/engine_demo/sim/event_queue.{h,cpp}`    | `DISABLED_consumer_observes_complete_payload`                | `relaxed` → `release` store / `acquire` load          |
| BUG-010 | `src/engine_demo/sim/interpolator.{h,cpp}`   | `DISABLED_unstarted_does_not_read_oob`                       | Check the `-1` sentinel **before** the unsigned cast  |

## Try it yourself

### Exercise 1 — Write the failing test before the fix (BUG-002)

- **Goal:** Prove to yourself that a red test must come before a fix — never the reverse.
- **Starter:** Open `output/ea-cpp-games/tests/engine_demo/test_game_loop.cpp`.
- **Suggested prompt** (Ask tab):

  ```text
  #file:output/ea-cpp-games/tests/engine_demo/test_game_loop.cpp
  Remove the DISABLED_ prefix from long_run_does_not_drift. Explain in one sentence what
  this test asserts and why it will fail before the accumulator type is fixed.
  ```

- **Expected outcome:** You run `ctest ... -R test_game_loop`, watch it fail, apply
  the BUG-002 fix, and watch it pass — in that order.
- Full steps: [exercises/01-test-before-fix.md](exercises/01-test-before-fix.md).

<details>
<summary>Hint</summary>

The test advances 3600 frames at `1/60` s and asserts every `advance()` returns exactly one
substep. With a `float` accumulator the count starts oscillating between 0 and 1 around frame 1800. Run in **Debug** — an optimized build can mask the drift.

</details>

### Exercise 2 — Find a third logic bug (BUG-004 vs. FP-002)

- **Goal:** Surface candidate defects in the constraint solver, then triage them — separate a
  real bug from a false positive with evidence.
- **Starter:** Open `output/ea-cpp-games/src/engine_demo/physics/constraint.cpp`.
- **Suggested prompt** (Ask tab):

  ```text
  #file:output/ea-cpp-games/include/engine_demo/physics/constraint.h
  #file:output/ea-cpp-games/src/engine_demo/physics/constraint.cpp
  #file:output/ea-cpp-games/specs/constitution.md
  List up to five candidate logic defects in this file. For each: (a) reproduce in <5 lines,
  (b) trace data flow, (c) cite the constitutional article it violates.
  ```

- **Expected outcome:** You identify **BUG-004** (non-determinism from hash-map iteration
  order, Article 5) and correctly **dismiss FP-002** (the sentinel iteration never
  dereferences the buffer).
- Full steps: [exercises/02-find-a-third.md](exercises/02-find-a-third.md).

<details>
<summary>Hint</summary>

Ask Copilot to distinguish "reads past the end" from "iterates one extra sentinel slot without
dereferencing it." Only the first is a bug. For BUG-004, the tell is that the solve result
depends on the order bodies were inserted.

</details>

## Troubleshooting

| Symptom                                          | Fix                                                                                        |
| ------------------------------------------------ | ------------------------------------------------------------------------------------------ |
| `cmake --preset default-debug` fails immediately | `VCPKG_ROOT` is unset or wrong. Point it at your vcpkg clone, then re-run configure.       |
| The drift test "passes" with the `float` bug     | You built optimized. Use the **Debug** preset so the drift is observable.                  |
| `ctest -R <name>` finds no tests                 | The test is still `DISABLED_`. Remove the prefix and rebuild before running it.            |
| BUG-006 fix breaks the rolling average           | Confirm `m_count` is updated and the wrap math uses `(m_index - m_count) mod window_size`. |
| Copilot rewrites unrelated code in the Edit tab  | Reject the diff and re-prompt with "change only the accumulator type; leave other code."   |

## Going further

- [logic-bug-workshop-training.md](logic-bug-workshop-training.md) — the full advanced set
  (BUG-004, 007, 008, 009, 010), plus Chain-of-Thought / Tree-of-Thought theory and the
  end-to-end agentic mesh: `@logic-bug-orchestrator` delegating to the `code-analysis`,
  `test-runner`, and `constitution-checker` sub-agents across four HITL gates.
- [sdlc-walkthrough.md](sdlc-walkthrough.md) — take one bug through the full AI SDLC loop:
  issue → agent fix → PR → CI gate → merge.
- [qa-track.md](qa-track.md) — the QA-engineer track: test-plan authoring, triage rubric,
  and sign-off gates.

## Feedback

Take two minutes for the [retro-survey.md](retro-survey.md) before you close out.
