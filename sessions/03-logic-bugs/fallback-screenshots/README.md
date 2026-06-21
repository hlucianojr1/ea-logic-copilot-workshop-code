# Fallback Screenshots — Session 03

Pre-captured Copilot interactions used by the
[facilitator-script.md](../facilitator-script.md) recovery plan when the live demo fails
(network outage, model regression, etc.).

## Capture checklist (run T-1 day, after a green baseline)

Capture each interaction below as a PNG named exactly as listed. Use a clean VS Code theme,
no EA-confidential UI, and crop to the Chat panel plus the relevant editor split.

| File name              | What to capture                                                                                                    |
| ---------------------- | ------------------------------------------------------------------------------------------------------------------ |
| `bug-002-observe.png`  | Ask-tab analysis of `game_loop.{h,cpp}` + constitution identifying `float m_accumulator_seconds`, citing Article 5 |
| `bug-002-red-test.png` | Terminal: `ctest --preset default-debug -R test_game_loop` failing on substep drift                                 |
| `bug-002-fix-diff.png` | Edit-tab diff: `float` → `double`, redundant casts removed                                                         |
| `bug-002-green.png`    | Terminal: `ctest --preset default-debug -R test_game_loop` passing                                                 |
| `bug-007-observe.png`  | Ask-tab analysis of `timer.{h,cpp}` explaining signed-overflow UB and guard elision at `-O2`                       |
| `bug-007-red-test.png` | Terminal: `ctest --preset optimized -R test_timer` failing                                                         |
| `bug-007-fix-diff.png` | Edit-tab diff: `int32_t` → `uint64_t`, guard removed                                                               |
| `bug-007-green.png`    | Terminal: full suite green after the fix                                                                           |

## Rules

- Screenshots are demo fallbacks only — they are not committed training content and must
  not contain tokens, account names, or proprietary code.
- Refresh captures whenever the Copilot UI or the model output format changes materially.
