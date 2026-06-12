# Crash-dump fixtures — BUG-001

> Demo workspace for Session 02 (Bug & Defect Fixing — Crash Dumps). The dump file is
> reproducibly captured from the seeded defect in `src/engine_demo/allocator.cpp`.

## Files

| File                       | Purpose                                                           |
| -------------------------- | ----------------------------------------------------------------- |
| `repro.cpp`                | Minimal reproducer — three aligned allocations against a 192-byte arena. |
| `capture.sh`               | Linux: build with debug symbols, run, package the core.           |
| `capture.ps1`              | Windows: build, run with WER configured to write a minidump.      |
| `BUG-001.dmp` / `.pdb`     | **Not committed.** Captured via the scripts above on first run.   |
| `BUG-001.dmp.local`        | Local working copy (gitignored).                                  |

## How to reproduce

### Linux

```bash
cd output/ea-cpp-games/fixtures/crash_dumps/BUG-001
./capture.sh
```

### Windows (PowerShell)

```powershell
cd output\ea-cpp-games\fixtures\crash_dumps\BUG-001
.\capture.ps1
```

## What Session 02 does with this

Learners load `BUG-001.dmp` (or the matching core file) into VS Code, attach Copilot via
the `analyze-crash-dump.prompt.md` workshop prompt, and walk:

1. Identify the failing frame via Copilot.
2. Trace the corruption back to the allocator bookkeeping order (the OOB write).
3. Propose a fix that re-orders the bounds check before the offset commit.
4. Add a regression test re-enabling
   `allocator.DISABLED_third_aligned_alloc_does_not_overrun_arena`.
