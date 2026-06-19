# Bug map — engine_demo seeded logic bugs

> Resource for the `logic-bug-triage` skill. Per-bug source file, header, `DISABLED_`
> regression test, and the ctest preset that surfaces the failure. Paths are relative to the
> repository root. Do not edit `fixtures/seeded-bugs.md` or the source defects themselves —
> they are the demo material.

## Bug → file → test → preset

| Bug     | Source (`output/ea-cpp-games/...`)       | Header                                     | `DISABLED_` test (`tests/engine_demo/...`)                                        | Preset          |
| ------- | ---------------------------------------- | ------------------------------------------ | --------------------------------------------------------------------------------- | --------------- |
| BUG-002 | `src/engine_demo/sim/game_loop.cpp`      | `include/engine_demo/sim/game_loop.h`      | `test_game_loop.cpp::DISABLED_long_run_does_not_drift`                            | `default-debug` |
| BUG-006 | `src/engine_demo/frame_budget.cpp`       | `include/engine_demo/frame_budget.h`       | `test_frame_budget.cpp::DISABLED_first_sample_is_not_double_counted_on_warmup`    | `default-debug` |
| BUG-010 | `src/engine_demo/sim/interpolator.cpp`   | `include/engine_demo/sim/interpolator.h`   | `test_interpolator.cpp::DISABLED_unstarted_does_not_read_oob`                     | `default-debug` |
| BUG-008 | `src/engine_demo/sim/replay_state.cpp`   | `include/engine_demo/sim/replay_state.h`   | `test_replay_state.cpp::DISABLED_padding_does_not_affect_comparison`              | `default-debug` |
| BUG-007 | `src/engine_demo/sim/timer.cpp`          | `include/engine_demo/sim/timer.h`          | `test_timer.cpp::DISABLED_overflow_guard_not_elided`                              | `optimized`     |
| BUG-004 | `src/engine_demo/physics/constraint.cpp` | `include/engine_demo/physics/constraint.h` | `test_constraint.cpp::DISABLED_solve_is_deterministic_across_construction_orders` | `default-debug` |
| BUG-009 | `src/engine_demo/sim/event_queue.cpp`    | `include/engine_demo/sim/event_queue.h`    | `test_event_queue.cpp::DISABLED_consumer_observes_complete_payload`               | `tsan`          |

## Preset notes

- `default-debug` — the standard `-O0` build; surfaces most logic and precision bugs.
- `optimized` — the `-O2` build. **Required for BUG-007**: the signed-overflow guard is only
  elided by the optimizer, so the bug does not reproduce under `default-debug`.
- `tsan` — ThreadSanitizer build. **Required for BUG-009**: the relaxed-ordering data race is
  only flagged with TSAN (and only manifests on weakly-ordered hardware otherwise).

## False positives — do not "fix"

| ID     | Where                         | Why it is not a bug                                                                             |
| ------ | ----------------------------- | ----------------------------------------------------------------------------------------------- |
| FP-001 | `src/engine_demo/sim/rng.cpp` | Seed derivation narrow-widens via XOR; no data is lost.                                         |
| FP-002 | `physics/constraint.cpp` loop | Trailing iteration is a sentinel that never reads the buffer.                                   |
| FP-003 | `include/.../event_queue.h`   | `m_ready` IS `std::atomic<bool>`. The real bug (BUG-009) is the memory ORDERING, not atomicity. |
