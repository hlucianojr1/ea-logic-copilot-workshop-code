# Session 03 — Trainer Dry-Run Fixes

**Date:** 2026-06-19  
**Branch:** `main`  
**Scope:** Post-dry-run action items from full Phases 1–4 trainer walkthrough

---

## Action items resolved

| # | Bug | File changed | Status |
|---|-----|--------------|--------|
| 1 | BUG-006 | `tests/engine_demo/test_frame_budget.cpp` | ✅ Done |
| 2 | BUG-008 | `tests/engine_demo/test_replay_state.cpp` | ✅ Done |
| 3 | BUG-009 | `sessions/03-logic-bugs/exercises/05-atomic-but-not-ordered.md` | ✅ Done |
| 4 | BUG-004 | _(no change — confirmed Session 04 scope)_ | ✅ Out of scope |

---

## BUG-006 — `test_frame_budget.cpp` DISABLED_ test strengthened

**Problem:** The original `DISABLED_first_sample_is_not_double_counted_on_warmup` test used a
single sample and asserted `rolling_average() == 10.0`. This assertion cannot distinguish the
buggy implementation from the fixed one: `m_samples[256]{}` zero-initialises every slot, and
averaging is commutative, so the numeric result is always correct regardless of which slot the
iterator starts from. BUG-006 is a code-review finding (iterator diverges from spec post-wrap),
not a numeric one.

**Fix applied:** Replaced the 1-sample test body with a 3-sample scenario (10.0, 20.0, 30.0)
that asserts `sample_count() == 3` and `rolling_average() == 20.0 ± 1e-9`. Added a multi-line
comment above the test explaining why BUG-006 cannot be caught by `rolling_average()` return
value. The `DISABLED_` prefix is retained so the test is compiled but not run until the fix is
applied.

---

## BUG-008 — `test_replay_state.cpp` rewritten for Apple Silicon reliability

**Problem:** The original `DISABLED_padding_does_not_affect_comparison` test used a
`volatile char stack_disturber[64]{}` array, filled alternately with `0xCC` and `0xDD` between
two `make_snapshot()` calls, hoping to corrupt the padding bytes of the returned struct.

On Apple Silicon (AArch64) this does not work. A 48-byte `replay_snapshot` is returned via a
hidden `sret` pointer into the caller's stack frame — not through integer registers. Writing to
a nearby `volatile` local touches a *different* stack slot; the `sret` slot's prior contents are
undisturbed. Both `make_snapshot()` calls reuse the same zeroed-by-OS page, so padding bytes
are identical in both structs → `memcmp` returns 0 → test passes even with the bug.

**Struct layout confirmed from `replay_state.h`:**

| Offset | Field | Size |
|--------|-------|------|
| 0 | `flags` (`uint8_t`) | 1 byte |
| 1–7 | _(padding)_ | 7 bytes |
| 8 | `position_x` (`double`) | 8 bytes |
| 16 | `position_y` (`double`) | 8 bytes |
| 24 | `frame_number` (`uint32_t`) | 4 bytes |
| 28–31 | _(padding)_ | 4 bytes |
| 32 | `velocity_x` (`double`) | 8 bytes |
| 40 | `velocity_y` (`double`) | 8 bytes |
| **48** | _(total)_ | |

**Fix applied:** After constructing both structs normally, `std::memset` poisons the padding
bytes directly:

- `a`: bytes `[1..7]` and `[28..31]` → `0xAB`
- `b`: bytes `[1..7]` and `[28..31]` → `0xCD`

A `static_assert(sizeof(replay_snapshot) == 48)` guards against layout drift. This approach is
deterministic on x86-64, AArch64, and any future port. Added `#include <cstring>` to the file.

---

## BUG-009 — TSan facilitator note added to exercise 05

**Problem:** Step 1 of `05-atomic-but-not-ordered.md` showed `ctest --preset tsan -R event_queue`
with no guidance for facilitators. TSan produces 3+ verbose data-race warnings plus an abnormal
process abort; the raw output overwhelms live demos.

**Fix applied:** Inserted a `> **Facilitator note:**` blockquote immediately after the `ctest`
code block, explaining the verbosity and providing a direct binary invocation piped through
`head -30` for focused live demonstrations.

---

## Build verification

After all three changes:

```
cmake --build --preset default-debug
ctest --preset default-debug
```

Result: **11/11 tests passed, 0 failures.** The two `DISABLED_` tests remain compiled but
excluded from the count, as intended.
