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

### Verify your tools

Confirm your toolchain is ready. You can ask Copilot to read your config files, run the
checks yourself, or both.

**Option A — Ask Copilot (prompt).** Paste this into the Copilot Chat **Ask** tab to have
Copilot verify your environment reads correctly:

```text
#file:output/ea-cpp-games/CMakeLists.txt
#file:output/ea-cpp-games/CMakePresets.json
I am about to run this workshop on my machine. Tell me: (a) which CMake presets are
available, (b) which compiler toolchain each preset expects, and (c) whether my
VCPKG_ROOT is likely configured correctly for a vcpkg-manifest build. Report any
missing configuration you can detect from these files.
```

**Option B — Run it yourself (manual).** Run these commands in your terminal and confirm
each line prints a version, not an error:

```bash
cmake --version        # must be 3.21 or higher
ninja --version        # any version is fine
echo $VCPKG_ROOT       # must print a non-empty path to your vcpkg clone (macOS/Linux)
echo %VCPKG_ROOT%      # Windows equivalent
```

If a tool is missing or `VCPKG_ROOT` is empty, fix it before going further — the configure
step will fail silently and produce a confusing error. See the
[Troubleshooting](#troubleshooting) table for the most common remediation steps.

### Build and confirm the green baseline

Get a clean, green tree before you touch any bug. All enabled tests must pass and the seeded
regressions must still be `DISABLED_`. That green tree is your starting line — do not begin a
bug until you see it.

**Option A — Ask Copilot (prompt).** Paste this into the **Agent** tab with
`@logic-bug-tutor` selected to have the tutor validate the baseline for you:

```text
@logic-bug-tutor
Verify the Session-03 baseline in output/ea-cpp-games/ before we start. Do not fix anything:
1. Run ctest --preset default-debug and confirm it is fully green.
2. Confirm all DISABLED_ regression tests are still prefixed DISABLED_ (none enabled yet).
3. Confirm git status --short shows a clean working tree.
Report PASS or FAIL for each item and stop.
```

**Option B — Run it yourself (manual).** Open `output/ea-cpp-games/` and, from that folder,
configure, build, and test:

```bash
cd output/ea-cpp-games
cmake --preset default-debug
cmake --build --preset default-debug
ctest --preset default-debug --output-on-failure
```

If any item is **FAIL**, do not start a bug. Run `./reset_workshop.sh` from
`output/ea-cpp-games/` to restore the clean seeded baseline, then re-run the check.

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

## Start as a self-paced training

Use this section if you want Copilot to act as a step-by-step instructor for the entire
session — pacing you through each bug, teaching reasoning patterns, and enforcing the
test-first and HITL rules so you do the work rather than watching Copilot do it.

Paste the prompt below into the Copilot Chat **Agent** tab with **`logic-bug-tutor`**
selected, then press Enter:

```text
@logic-bug-tutor
I am a self-guided learner working through Session 03 — Logic Bugs. Please act as my
instructor for this session:
1. Verify the output/ea-cpp-games/ baseline is green and all DISABLED_ tests are still
   disabled. Stop and report before we touch any bug.
2. Show me the bug ladder (easiest → hardest) and ask me which bug I want to start with.
3. For each bug I pick, walk me through the four phases — OBSERVE, REPRODUCE, FIX,
   VERIFY — using Socratic questions and hints, not answers. Do not reveal the root
   cause or the fix until I have a red test.
4. Before each phase transition, confirm I am ready to move on.
5. After each bug is verified green, summarize: bug ID, root cause (one sentence),
   constitutional articles restored, and suggest the next rung on the ladder.
start
```

**What the tutor will do:**

- Ask you questions ("What type is `m_accumulator_seconds`?") instead of handing you the
  answer — escalating specificity only when you are stuck twice.
- Refuse to discuss a fix until you enable the matching `DISABLED_` test and show it red.
- Present each phase transition as a gate that requires your explicit confirmation.
- Read code and run `ctest` checks on your behalf; it never edits files — you make every
  change.

**If the tutor does not appear in the agents dropdown:** confirm that
`.github/agents/logic-bug-tutor.agent.md` exists in the workspace root and that the GitHub
Copilot Chat extension is version 0.20 or later. See [Troubleshooting](#troubleshooting).

## Outcomes

1. Apply the **observe → reproduce → bisect** pattern to a non-crashing logic bug.
2. Author a **minimal failing test before** writing any fix (Article 7, test-first).
3. Distinguish numerical **drift** (BUG-002) from an **off-by-one** (BUG-006) by their repro
   shape.
4. Gate every fix behind a human-in-the-loop approval (Article 8).

## Key concepts

These three patterns appear throughout the session. You do not need to memorize them — the
tutor and prompts guide you — but knowing the vocabulary helps you follow along.

- **Chain-of-Thought (CoT):** linear, step-by-step reasoning along a single hypothesis —
  "trace this value from declaration to the crash, one step at a time." Best when there is
  one likely root cause.
- **Tree-of-Thought (ToT):** explore 2–3 hypotheses in parallel, score each on evidence and
  minimal-diff, then prune and converge. Best when the symptom could have several causes
  (e.g., BUG-008 memcmp, BUG-010 sentinel). The training doc has the full scoring rubric.
- **Human-in-the-Loop (HITL):** the rule that Copilot proposes and you approve before any
  irreversible step (enabling a test, applying a fix). The four HITL gates are: diagnosis
  approval, constitutional compliance, red-test confirmation, and fix-apply approval.

## Walk-through

Work each bug as a four-phase loop. Every prompt below is copy-paste ready — paste it into the
named Copilot tab exactly as written.

> **Two ways to run every command step.** Wherever this guide asks you to build or run tests,
> it gives you a choice:
>
> - **Option A — Ask Copilot (prompt):** paste the `@logic-bug-tutor` prompt into the **Agent**
>   tab and let the tutor run the build/test on your behalf and report red or green. The tutor
>   never edits your files — you still make every fix.
> - **Option B — Run it yourself (manual):** run the shell commands in your terminal.
>
> Pick whichever you prefer per step — they are equivalent. New to the workspace? Start with
> Option A.

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

Then run just that test and watch it go red.

**Option A — Ask Copilot (prompt).** In the **Agent** tab:

```text
@logic-bug-tutor
For BUG-002, rebuild the default-debug preset and run only ctest --preset default-debug
-R test_game_loop. Report the failing assertion and whether the test is red or green.
Do not edit any files and do not propose a fix.
```

**Option B — Run it yourself (manual).** From `output/ea-cpp-games/`:

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

**4. Verify.** Re-run the single test (now green), then the full suite.

**Option A — Ask Copilot (prompt).** In the **Agent** tab:

```text
@logic-bug-tutor
Verify my BUG-002 fix: rebuild the default-debug preset and run the full
ctest --preset default-debug suite. Confirm long_run_does_not_drift is green and the whole
suite stays green. Report PASS or FAIL and stop — do not edit any files.
```

**Option B — Run it yourself (manual).** From `output/ea-cpp-games/`:

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

Accept the edit, then rebuild before running ctest — `ctest` does not compile and will test
a stale binary if you skip this step.

**Option A — Ask Copilot (prompt).** In the **Agent** tab:

```text
@logic-bug-tutor
For BUG-006, rebuild the default-debug preset and run only ctest --preset default-debug
-R test_frame_budget. Report whether first_sample_is_not_double_counted_on_warmup is red
or green and show the failing assertion if any. Do not edit any files.
```

**Option B — Run it yourself (manual).** From `output/ea-cpp-games/`:

```bash
cd output/ea-cpp-games
cmake --build --preset default-debug
ctest --preset default-debug --output-on-failure -R test_frame_budget
```

**4. Verify.** Run the full suite and confirm green.

**Option A — Ask Copilot (prompt).** In the **Agent** tab:

```text
@logic-bug-tutor
Verify my BUG-006 fix: rebuild the default-debug preset and run the full
ctest --preset default-debug suite. Confirm the suite is fully green. Report PASS or FAIL
and stop — do not edit any files.
```

**Option B — Run it yourself (manual).** From `output/ea-cpp-games/`:

```bash
cd output/ea-cpp-games
ctest --preset default-debug --output-on-failure
```

> **What good looks like:** `rolling_average()` iterates the most-recent `m_count` samples in
> wrap order and no longer double-counts the warm-up sample. The re-enabled
> `first_sample_is_not_double_counted_on_warmup` test passes and the suite stays green.
>
> **Reset before the next bug:** return to the clean baseline so the next bug starts fresh.
> In the **Agent** panel, run:

```text
@logic-bug-tutor
I finished BUG-006. Reset output/ea-cpp-games/ to the clean seeded baseline (revert my fix,
re-DISABLE_ the test, rebuild) and confirm ctest --preset default-debug is green before I
continue.
```

Manual equivalent: from `output/ea-cpp-games/`, run `git restore src/engine_demo
include/engine_demo tests/engine_demo` then `cmake --build --preset default-debug`.

### BUG-007 — signed-overflow UB at -O2

This bug passes in Debug but is silently broken in the optimized build. The signed-overflow
guard `m_elapsed_ms + delta_ms > m_elapsed_ms` is undefined behavior — the compiler legally
deletes it at `-O2`. Never validate against the Debug preset alone.

**1. Observe.** In the **Ask** tab:

```text
#file:output/ea-cpp-games/include/engine_demo/sim/timer.h
#file:output/ea-cpp-games/src/engine_demo/sim/timer.cpp
#file:output/ea-cpp-games/specs/constitution.md
The timer has an overflow guard: `m_elapsed_ms + delta_ms > m_elapsed_ms`. Analyze
whether this guard is effective at -O2. Cite what the C++ standard says about signed
integer overflow ([expr.pre]/4) and which constitutional article is violated.
```

Copilot should explain that signed overflow is UB, so a conforming optimizer proves the
comparison always true and **elides the branch**.

**2. Reproduce (test-first).** Enable the regression test:

```text
#file:output/ea-cpp-games/tests/engine_demo/test_timer.cpp
Remove the DISABLED_ prefix from overflow_guard_not_elided. Explain in one sentence why
this test must be run under the optimized preset, not default-debug.
```

Then build and run with **both** presets to witness the contrast — red at `-O2`, green at
`-O0` is the bug's fingerprint.

**Option A — Ask Copilot (prompt).** In the **Agent** tab:

```text
@logic-bug-tutor
For BUG-007, run overflow_guard_not_elided under both presets so I can see the contrast:
1. Configure and build the optimized preset, then run ctest --preset optimized
   -R test_timer — report whether it is red.
2. Build the default-debug preset, then run ctest --preset default-debug -R test_timer —
   report whether it is green.
Report both results and stop. Do not edit any files or propose a fix.
```

**Option B — Run it yourself (manual).** First the optimized preset, where the test
**fails** at `-O2`:

```bash
cd output/ea-cpp-games
cmake --preset optimized && cmake --build --preset optimized
ctest --preset optimized --output-on-failure -R test_timer
```

Now verify it still passes at `-O0`:

```bash
cmake --build --preset default-debug
ctest --preset default-debug --output-on-failure -R test_timer
```

That contrast — red at `-O2`, green at `-O0` — is the bug's fingerprint.

**3. Fix.** In the **Edit** tab:

```text
#file:output/ea-cpp-games/include/engine_demo/sim/timer.h
#file:output/ea-cpp-games/src/engine_demo/sim/timer.cpp
Change m_elapsed_ms to std::uint64_t. Remove the fragile overflow guard entirely —
unsigned wraparound is defined behavior and takes ~584 million years at 1ms resolution.
Update tick() return type and elapsed_ms() accordingly. Constitutional articles 1 and 5
must hold.
```

**4. Verify.** Rebuild and rerun the `optimized` preset — then the full suite.

**Option A — Ask Copilot (prompt).** In the **Agent** tab:

```text
@logic-bug-tutor
Verify my BUG-007 fix across both presets: rebuild and run the full ctest --preset optimized
suite, then the full ctest --preset default-debug suite. Confirm overflow_guard_not_elided
and both suites are green. Report PASS or FAIL per preset and stop — do not edit any files.
```

**Option B — Run it yourself (manual).** From `output/ea-cpp-games/`:

```bash
cd output/ea-cpp-games
cmake --build --preset optimized
ctest --preset optimized --output-on-failure
ctest --preset default-debug --output-on-failure
```

> **What good looks like:** `m_elapsed_ms` is `uint64_t`, the guard is gone, and both
> presets are green. The fix is a type change — not a rewritten guard.
>
> **Reset:** `git restore src/engine_demo include/engine_demo tests/engine_demo` then
> `cmake --build --preset default-debug`.

### The rest of the set — let the tutor pace you

The advanced path adds four more bugs. The compact reference below keeps this guide
self-contained; the **`logic-bug-tutor`** agent runs the full four-phase loop for each, and
[logic-bug-workshop-training.md](logic-bug-workshop-training.md) has the deep dives.
Hands-on exercise files for BUG-004, 008, 009, and 010 are in [exercises/](exercises/).

| Bug     | Files (under `output/ea-cpp-games/`)         | Re-enable this test                                          | OBSERVE prompt files                      | One-line fix                                         |
| ------- | -------------------------------------------- | ------------------------------------------------------------ | ----------------------------------------- | ---------------------------------------------------- |
| BUG-004 | `src/engine_demo/physics/constraint.{h,cpp}` | `DISABLED_solve_is_deterministic_across_construction_orders` | `constraint.{h,cpp}`, `constitution.md`   | Sort constraints; read bodies via a dense index      |
| BUG-008 | `src/engine_demo/sim/replay_state.{h,cpp}`   | `DISABLED_padding_does_not_affect_comparison`                | `replay_state.{h,cpp}`, `constitution.md` | Replace `memcmp` with member-wise comparison         |
| BUG-009 | `src/engine_demo/sim/event_queue.{h,cpp}`    | `DISABLED_consumer_observes_complete_payload`                | `event_queue.{h,cpp}`, `constitution.md`  | `relaxed` → `release` store / `acquire` load         |
| BUG-010 | `src/engine_demo/sim/interpolator.{h,cpp}`   | `DISABLED_unstarted_does_not_read_oob`                       | `interpolator.{h,cpp}`, `constitution.md` | Check the `-1` sentinel **before** the unsigned cast |

For each bug, use this OBSERVE prompt (Ask tab) — substitute the files from the table:

```text
#file:output/ea-cpp-games/include/engine_demo/<area>/<file>.h
#file:output/ea-cpp-games/src/engine_demo/<area>/<file>.cpp
#file:output/ea-cpp-games/specs/constitution.md
Identify the root cause of <symptom from the bug report>. Cite the constitutional
article violated and trace the data flow from the defect site to the observable symptom.
```

After observing, enable the matching `DISABLED_` test and run it red before proposing any
fix.

**Option A — Ask Copilot (prompt).** In the **Agent** tab, substitute the bug ID and its
test name from the table above:

```text
@logic-bug-tutor
For <BUG-ID>, enable its DISABLED_ regression test, rebuild, and run only that test on the
correct preset (default-debug for most bugs, tsan for BUG-009). Report whether it is red or
green and show the failing assertion. Do not edit any source files and do not propose a fix.
```

You can also hand the whole four-phase loop to the tutor by naming the bug:

```text
@logic-bug-tutor BUG-004
```

**Option B — Run it yourself (manual).** Rebuild, then run the matching test binary (from
`output/ea-cpp-games/`):

```bash
cd output/ea-cpp-games
cmake --build --preset default-debug
ctest --preset default-debug --output-on-failure -R <test-binary>
```

BUG-009 requires the `tsan` preset instead of `default-debug` — build and run with
`--preset tsan`.

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

### Exercise 3 — UB and the optimizer (BUG-007)

- **Goal:** Experience why "passes in Debug" is never validation — reproduce a signed-overflow
  guard that the compiler silently deletes at `-O2`.
- **Starter:** Open `output/ea-cpp-games/src/engine_demo/sim/timer.cpp`.
- **Suggested prompt** (Ask tab):

  ```text
  #file:output/ea-cpp-games/include/engine_demo/sim/timer.h
  #file:output/ea-cpp-games/src/engine_demo/sim/timer.cpp
  This timer has a "safety guard" for overflow. Analyze whether this guard is effective
  at -O2. Explain what the C++ standard says about signed integer overflow
  ([expr.pre]/4) and how a conforming optimizer treats this code. Do not propose a fix.
  ```

- **Expected outcome:** You build with the `optimized` preset, watch the test **fail** at
  `-O2`, then build with `default-debug` and watch it **pass** at `-O0` — the preset
  contrast is the proof. You apply the type-level fix (`uint64_t` + drop the guard).
- Full steps: [exercises/03-ub-and-the-optimizer.md](exercises/03-ub-and-the-optimizer.md).

<details>
<summary>Hint</summary>

Signed overflow is undefined behavior. A conforming optimizer sees `x + positive > x` and
proves: "overflow can't happen, so this is always true." The branch is deleted. `-fwrapv` or
a bigger guard treats the symptom — the correct fix is an unsigned type.

</details>

### Exercise 4 — Bitwise vs. logical equality (BUG-008)

- **Goal:** Use a Tree-of-Thought prompt to surface three competing hypotheses for an
  intermittent test failure, then converge on the padding root cause.
- **Starter:** Open `output/ea-cpp-games/src/engine_demo/sim/replay_state.cpp`.
- **Suggested prompt** (Ask tab):

  ```text
  #file:output/ea-cpp-games/src/engine_demo/sim/replay_state.cpp
  #file:output/ea-cpp-games/include/engine_demo/sim/replay_state.h
  #file:output/ea-cpp-games/specs/constitution.md
  Two replay_state values built from identical inputs compare unequal — but only
  sometimes. Simulate three experts proposing distinct root-cause hypotheses (e.g.,
  uninitialized member, padding bytes, float NaN). Each expert: hypothesis, evidence,
  confidence %, one-line disproof test. Converge on the most probable cause.
  ```

- **Expected outcome:** The padding expert wins — `memcmp` compares object representation
  including indeterminate padding bytes. You replace `memcmp` with member-wise `operator==`
  (or `= default`) and the test becomes deterministically green.
- Full steps: [exercises/04-bitwise-vs-logical.md](exercises/04-bitwise-vs-logical.md).

<details>
<summary>Hint</summary>

A single green run of the intermittent test proves nothing — uninitialized padding sometimes
matches by luck. Run the test several times. `memset`-ing the struct masks the symptom;
replace the comparison to fix the root cause.

</details>

### Exercise 5 — Atomic, but not ordered (BUG-009)

- **Goal:** Use ThreadSanitizer — not a debugger — to reproduce a data race caused by
  insufficient memory ordering, and correctly dismiss FP-003 (the flag IS atomic; the
  ordering is wrong).
- **Starter:** Open `output/ea-cpp-games/src/engine_demo/sim/event_queue.cpp`.
- **Suggested prompt** (Ask tab):

  ```text
  #file:output/ea-cpp-games/src/engine_demo/sim/event_queue.cpp
  #file:output/ea-cpp-games/include/engine_demo/sim/event_queue.h
  #file:output/ea-cpp-games/specs/constitution.md
  TSan reports a data race on m_payload between publish() and try_consume(). Evaluate
  these two claims independently: (1) "m_ready is not atomic, that's the race" and
  (2) "m_ready is atomic but the memory ordering doesn't synchronize m_payload". For
  each: cite the exact line, say true or false, justify from [atomics.order].
  Which claim is a false positive?
  ```

- **Expected outcome:** Claim (1) is **FP-003** — `m_ready` is `std::atomic<bool>`.
  Claim (2) is the real defect. You change `memory_order_relaxed` to `release` on the
  store and `acquire` on the load. Build with the `tsan` preset to verify (not
  `default-debug` — TSan requires a separate build).
- Full steps: [exercises/05-atomic-but-not-ordered.md](exercises/05-atomic-but-not-ordered.md).

<details>
<summary>Hint</summary>

Relaxed atomics guarantee atomicity but NOT ordering. The consumer can observe `m_ready ==
true` before it sees the payload write. Only `release`/`acquire` or `seq_cst` pairs create
the happens-before edge that synchronizes `m_payload`.

</details>

### Exercise 6 — The sentinel trap (BUG-010)

- **Goal:** Fix a `-1` sentinel that converts to `SIZE_MAX` via signed-to-unsigned promotion
  and defeats the bounds check — then compare CoT vs. ToT to learn when each earns its cost.
- **Starter:** Open `output/ea-cpp-games/src/engine_demo/sim/interpolator.cpp`.
- **Round 1 — CoT prompt** (Ask tab, fresh context):

  ```text
  #file:output/ea-cpp-games/src/engine_demo/sim/interpolator.cpp
  #file:output/ea-cpp-games/include/engine_demo/sim/interpolator.h
  An unstarted interpolator reads an arbitrary array slot instead of returning a default
  value. Reason step by step through sample()'s control flow with m_current_index == -1:
  trace the value through every conversion, state where the bounds check fails, and name
  the root cause. One linear chain — no alternatives.
  ```

- **Round 2 — ToT prompt** (Ask tab, **new chat**):

  ```text
  #file:output/ea-cpp-games/src/engine_demo/sim/interpolator.cpp
  #file:output/ea-cpp-games/include/engine_demo/sim/interpolator.h
  #file:output/ea-cpp-games/specs/constitution.md
  Same symptom: unstarted interpolator reads out of bounds. Simulate three experts with
  distinct hypotheses (off-by-one in bounds check, signed-to-unsigned sentinel
  conversion, stale keyframe pointer). Each: hypothesis, evidence, confidence %,
  one-line disproof. Converge.
  ```

- **Expected outcome:** Both approaches converge on the same root cause; CoT usually
  arrives faster on this single-path bug. You add a sentinel guard before the cast and
  rerun ctest until green.
- Full steps: [exercises/06-sentinel-trap.md](exercises/06-sentinel-trap.md).

<details>
<summary>Hint</summary>

`int32_t(-1)` cast to `size_t` yields `SIZE_MAX` (4,294,967,295 on 32-bit or
18,446,744,073,709,551,615 on 64-bit). The bounds check `index < size` is then trivially
false and the comparison is skipped. Guard the sentinel before any unsigned conversion.

</details>

## Troubleshooting

| Symptom                                                  | Fix                                                                                                                                                         |
| -------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `cmake --preset default-debug` fails immediately         | `VCPKG_ROOT` is unset or wrong. Point it at your vcpkg clone, then re-run configure.                                                                        |
| The drift test "passes" with the `float` bug             | You built optimized. Use the **Debug** preset so the drift is observable.                                                                                   |
| `ctest -R <name>` finds no tests                         | The test is still `DISABLED_`. Remove the prefix and **rebuild** before running ctest — `ctest` does not compile.                                           |
| BUG-006 fix breaks the rolling average                   | Confirm `m_count` is updated and the wrap math uses `(m_index - m_count + window_size) % window_size`.                                                      |
| Copilot rewrites unrelated code in the Edit tab          | Reject the diff and re-prompt with "change only the accumulator type; leave other code."                                                                    |
| BUG-007 passes in Debug but you need to see it fail      | Use `cmake --preset optimized && cmake --build --preset optimized` then `ctest --preset optimized -R test_timer`. The bug only manifests at `-O2`.          |
| `logic-bug-tutor` does not appear in the agents dropdown | Confirm `.github/agents/logic-bug-tutor.agent.md` exists in the workspace root. If it does, check that the GitHub Copilot Chat extension is version ≥ 0.20. |
| Tutor says "baseline is green" but gives no bug prompts  | The `DISABLED_` tests are likely already enabled from a previous run. Run `git restore tests/` and `cmake --build --preset default-debug`, then retry.      |

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
