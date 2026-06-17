# Session 03 — Bug & Defect Fixing: Logic Bugs (facilitator script)

> **Cross-references:** [`learner-guide.md`](learner-guide.md) · [`slides.outline.md`](slides.outline.md) · [`retro-survey.md`](retro-survey.md) · [exercises](exercises/) · [`sdlc-walkthrough.md`](sdlc-walkthrough.md) · [`qa-track.md`](qa-track.md)

## Session at a glance

- **Duration:** 60 min · **Level:** advanced · **Plan tier:** Business
- **Demo state:** S2 fix to BUG-001 merged; tests green.
- **Outcomes:**
  1. Apply the **observe → reproduce → bisect** pattern to a non-crashing logic bug.
  2. Use Copilot to author a _minimal failing test_ before any fix.
  3. Distinguish numerical drift from off-by-one — both anchors live in this session.

> **Facilitator note:** dual-track session. Developers follow the live demo; QA
> engineers additionally own the HITL-gate verdicts using [`qa-track.md`](qa-track.md).
> Announce the split in the opening and pair each QA learner with a developer.

## Pre-session checklist (T-15 min)

> **Do:** open `src/engine_demo/sim/game_loop.cpp` (BUG-002) and `src/engine_demo/frame_budget.cpp` (BUG-006) in two editor groups.
> **Do:** verify `ctest --preset default-debug --output-on-failure` is green; the seeded regressions are still DISABLED.
> **Watch for:** Session 02's allocator fix changed test count; confirm the green baseline before starting.

## Opening (0:00 – 0:05)

> **Say:** "Last week we used the debugger to find _where_ a bug fires. This week the bug never fires loudly — it drifts. Replay diverges. Telemetry is slightly wrong. We need a different muscle."

> **Do:** show the agenda. Two bugs: BUG-002 (numerical drift, 25 min), BUG-006 (off-by-one, 20 min).

> **Say:** "If you're QA: your job today is not to fix anything — it's to be unfoolable. At every HITL gate you'll record an approve/reject verdict with evidence, using the template in the QA track doc."

## Block 1: BUG-002 — observe / reproduce / bisect (0:05 – 0:30)

> **Say:** "Phase 1 is **observe**: turn the symptom into a measurement Copilot can reason about."

> **Do:** in the **Ask** tab:

```text
#file:output/ea-cpp-games/include/engine_demo/sim/game_loop.h
#file:output/ea-cpp-games/src/engine_demo/sim/game_loop.cpp
#file:output/ea-cpp-games/specs/constitution.md
A long replay diverges from a reference run after ~30 simulated seconds. Identify any
violation of the constitution's article 5 in this code.
```

> **Watch for:** Copilot points at the `float m_accumulator_seconds` and cites Article 5.

> **Say:** "Phase 2 is **reproduce**: produce a minimal failing test that captures the drift."

```text
#file:output/ea-cpp-games/tests/engine_demo/test_game_loop.cpp
Re-enable DISABLED_long_run_does_not_drift. Confirm it fails. State, in one sentence, why
it fails."
```

> **HITL gate:** facilitator runs ctest; learners see the failure live.

> **Facilitator note (QA track):** pause 30 s — QA learners record the Gate 3 verdict
> (test reproduces failure) using the template in [`qa-track.md`](qa-track.md) §3.

> **Say:** "Phase 3 is **bisect** — but in a single-file scope, bisection is just 'change the type and rebuild'."

> **Do:** Edit Mode:

```text
#file:output/ea-cpp-games/include/engine_demo/sim/game_loop.h
#file:output/ea-cpp-games/src/engine_demo/sim/game_loop.cpp
Promote m_accumulator_seconds from float to double. Remove the now-unnecessary casts.
Constitutional articles 1, 2, 5 must hold.
```

> **Watch for:** the diff also drops the `static_cast<float>` calls. If Copilot leaves them in, ask "are any casts now redundant?"

> **HITL gate:** rerun ctest; the regression test passes.

> **Facilitator note (QA track):** QA learners record Gate 4 (fix minimal & safe) —
> `git diff --stat` should show exactly two files: the header and the source.

## Block 2: BUG-006 — off-by-one in a rolling window (0:30 – 0:50)

> **Say:** "Off-by-one bugs hide in plain sight. The trick is to ask Copilot to enumerate slot states, not infer them."

> **Do:** **Ask** tab:

```text
#file:output/ea-cpp-games/include/engine_demo/frame_budget.h
#file:output/ea-cpp-games/src/engine_demo/frame_budget.cpp
After three calls to record_sample(2.0), record_sample(4.0), record_sample(6.0) on a
freshly-constructed frame_budget(window_size=4), state the value of every slot in
m_samples[] and the value Copilot would expect from rolling_average(). Show your math.
```

> **Watch for:** Copilot's prediction matches `(2+4+6)/3 = 4.0`. Then ask:

```text
Now read the actual code: what does rolling_average() compute, byte for byte, on the
above input? Reconcile with your prediction.
```

> **Say:** "The reconciliation is where the bug lives. Notice Copilot's first answer was the _spec_, not the _code_."

> **Do:** Edit Mode:

```text
#file:output/ea-cpp-games/src/engine_demo/frame_budget.cpp
Fix rolling_average so it iterates the most-recent m_count samples in wrap order
starting from (m_index - m_count) mod m_window_size. Re-enable
DISABLED_first_sample_is_not_double_counted_on_warmup.
```

> **HITL gate:** ctest green.

## Q&A (0:50 – 0:57)

- **Q: "How do you know it's drift vs. an off-by-one?"** → "Drift accumulates monotonically; off-by-one is binary. Different repro shapes."
- **Q: "What about race conditions?"** → "Session 09. Different muscle entirely."

## Retro micro-survey (0:57 – 1:00)

> **Do:** post [`retro-survey.md`](retro-survey.md).

## Stretch goals

- Combine BUG-002 + BUG-006 into a single "find them both with one belt" exercise.
- Walk the full issue→branch→PR→merge loop for BUG-002 using
  [`sdlc-walkthrough.md`](sdlc-walkthrough.md) — including the headless trace diff as
  PR evidence.
- Self-paced follow-ups: [exercises 03–06](exercises/) cover BUG-007/008/009/010 with
  the `optimized` and `tsan` presets.

## Recovery script

If learners can't reproduce the drift live: ship a recorded GIF of the failure, walk the math on a whiteboard.

## Post-session checklist

- Confirm the BUG-002 and BUG-006 fixes merged; the catalog now lists them as "fixed in S03".
- Update Session 04's pre-work to reflect the now-clean tree.
