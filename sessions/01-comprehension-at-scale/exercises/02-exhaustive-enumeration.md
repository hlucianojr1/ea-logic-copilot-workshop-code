# Exercise 02 — Exhaustive enumeration

**Time:** 10 minutes · **Difficulty:** intermediate

## Goal

Use the "exhaustive enumeration" trick to map every read site of `m_samples` in
`engine_demo::frame_budget`, then verify by hand.

## Steps

1. Open `output/ea-cpp-games/src/engine_demo/frame_budget.cpp` and `.../include/engine_demo/frame_budget.h` side by side.
2. In the **Ask** tab:

```text
#file:output/ea-cpp-games/include/engine_demo/frame_budget.h
#file:output/ea-cpp-games/src/engine_demo/frame_budget.cpp
List every code path that READS m_samples. Quote the line. One-sentence rationale each.
```

1. **By hand**, grep both files for `m_samples`. Compare to Copilot's list.

## Acceptance

Your hand-verified read sites match Copilot's enumeration exactly. If they don't, the
truth is the file, not the model — note the divergence in your retro feedback.

## Reflection

The Session 03 fix for BUG-006 will require knowing every read and write site. You're
building the muscle for that today.
