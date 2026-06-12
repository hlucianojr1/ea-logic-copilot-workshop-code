---
description: Generate reproducible crash-dump fixtures (minidumps + matched PDBs) for Session 2.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit", "runCommands"]
inputs: []
outputs:
  - path: output/ea-cpp-games/fixtures/crash_dumps/README.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/fixtures/crash_dumps/repro/CMakeLists.txt
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/fixtures/crash_dumps/repro/bug001_arena_oob.cpp
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/fixtures/crash_dumps/repro/bug003_uaf_world.cpp
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/fixtures/crash_dumps/repro/run-and-capture.ps1
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/fixtures/crash_dumps/repro/run-and-capture.sh
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/fixtures/crash_dumps/expected/BUG-001.md
    kind: file
    overwrite: false
  - path: output/ea-cpp-games/fixtures/crash_dumps/expected/BUG-003.md
    kind: file
    overwrite: false
validation:
  - "test -f output/ea-cpp-games/fixtures/crash_dumps/README.md"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Produce **reproducible** crash-dump fixtures that drive Session 2's demo. The actual `.dmp`
and `.pdb` binaries are generated **at session start** by running the repro programs against
the bugged demo workspace. We commit the source repros, the capture scripts, and the
expected analysis. We do NOT commit the binary dumps (they go into `.gitignore` as
`*.dmp.local` / `*.pdb.local`) — they are reproducible from these sources.

## Context references

- `#file:../../factory-overlay/demo-patterns/crash-dump-triage.md`
- `#file:../../output/ea-cpp-games/fixtures/seeded-bugs.md` (BUG-001, BUG-003)

## Pre-conditions

- `demo-workspace-engine-module.prompt.md` completed (seeded bugs in place).

## Steps

1. **`README.md`** — explains the fixture model: source repros checked in; binary dumps
   generated locally; how a facilitator runs the capture before a live session.
2. **Repro programs** — small `int main()` programs that link against `engine_demo` and
   trigger BUG-001 / BUG-003 deterministically. Each prints the expected fault address and
   exits via SIGSEGV / access-violation, producing a minidump under `crash_dumps/local/`.
3. **`run-and-capture.ps1` (Windows)** — sets `procdump` or Windows Error Reporting to
   write a minidump on crash; runs the repro; copies `.dmp` and matching `.pdb` to a stable
   path; prints the SHA256 so reproducibility can be verified.
4. **`run-and-capture.sh` (Linux/macOS)** — uses `coredumpctl` (Linux) or `lldb` (macOS) to
   capture; converts to a minidump-like format using `breakpad`'s `dump_syms` tool. Documents
   that minidumps are inherently Windows-flavored; on macOS/Linux we capture cores and the
   facilitator demos the analysis path against the macOS/Linux equivalents.
5. **`expected/BUG-001.md`** — the analysis a facilitator will demonstrate Copilot reproducing:
   faulting frame, Copilot's diagnosis, the fix, the test that verifies the fix.
6. **`expected/BUG-003.md`** — same shape for BUG-003.

> **HITL gate:** facilitator runs `run-and-capture.{sh,ps1}` 24h before the session and
> verifies a fresh `.dmp` is produced and Copilot can attribute the fault correctly.

## Output contract

All declared files exist; repro programs compile against `engine_demo`; capture scripts
documented; expected-analysis files contain the verbatim chat prompts to use.

## Self-validation

```bash
test -f output/ea-cpp-games/fixtures/crash_dumps/repro/CMakeLists.txt
grep -q "BUG-001" output/ea-cpp-games/fixtures/crash_dumps/expected/BUG-001.md
grep -q "BUG-003" output/ea-cpp-games/fixtures/crash_dumps/expected/BUG-003.md
```

## Failure modes

- **Committing a `.dmp` or `.pdb`**: never. They go in `.gitignore`. The repro source IS the
  fixture.
- **Repro that doesn't crash deterministically**: rewrite until it does. Non-deterministic
  fixtures destroy the demo.
- **PDB / source mismatch**: the capture script must rebuild before capturing to guarantee
  PDB ↔ source rev linkage.
