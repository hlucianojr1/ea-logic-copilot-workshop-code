#!/usr/bin/env bash
#
# reset_workshop.sh — Session 03 (Logic Bugs) pre-flight reset + readiness check.
#
# Run this BEFORE the instructor starts the session. It:
#   1. Reverts the seeded engine_demo source + tests back to the clean committed
#      baseline (undoes any prior demo's fix and re-DISABLEs every seeded test).
#   2. Configures and builds the default-debug preset.
#   3. Runs the full default-debug suite and asserts a GREEN baseline.
#   4. Confirms all 10 seeded regression tests are still DISABLED_.
#   5. Prints a clear READY / NOT-READY verdict.
#
# It only ever uses `git restore` (reversible) — never `git reset --hard` or any
# history-rewriting / destructive op. Restore is scoped to the engine_demo trees,
# so your edits to docs / sessions / tooling are left untouched.
#
# Usage (from anywhere; the script cd's to its own directory):
#   ./reset_workshop.sh            # restore + build + verify
#   ./reset_workshop.sh --no-git   # skip git restore (keep manual source edits)
#
set -euo pipefail

# --- locate the workspace (this script lives in output/ea-cpp-games/) ----------
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

PRESET="default-debug"
DO_GIT_RESTORE=1
for arg in "$@"; do
    case "$arg" in
        --no-git) DO_GIT_RESTORE=0 ;;
        -h|--help) sed -n '2,28p' "${BASH_SOURCE[0]}"; exit 0 ;;
        *) echo "Unknown argument: $arg" >&2; exit 2 ;;
    esac
done

# --- pretty output -------------------------------------------------------------
if [[ -t 1 ]]; then
    BOLD=$'\033[1m'; GREEN=$'\033[32m'; RED=$'\033[31m'; YELLOW=$'\033[33m'; RESET=$'\033[0m'
else
    BOLD=""; GREEN=""; RED=""; YELLOW=""; RESET=""
fi
step() { echo "${BOLD}==>${RESET} $*"; }
ok()   { echo "  ${GREEN}OK${RESET}  $*"; }
warn() { echo "  ${YELLOW}!!${RESET}  $*"; }
fail() { echo "  ${RED}XX${RESET}  $*"; }

# The 10 seeded regression tests (base case name -> owning test binary file).
SEEDED_TESTS=(
    "stale_handle_does_not_revive_after_recycle:test_world.cpp"
    "third_aligned_alloc_does_not_overrun_arena:test_allocator.cpp"
    "long_run_does_not_drift:test_game_loop.cpp"
    "solve_is_deterministic_across_construction_orders:test_constraint.cpp"
    "first_sample_is_not_double_counted_on_warmup:test_frame_budget.cpp"
    "overflow_guard_not_elided:test_timer.cpp"
    "padding_does_not_affect_comparison:test_replay_state.cpp"
    "consumer_observes_complete_payload:test_event_queue.cpp"
    "distinct_high_words_yield_distinct_streams:test_rng.cpp"
    "unstarted_does_not_read_oob:test_interpolator.cpp"
)
TESTS_DIR="tests/engine_demo"

READY=1

# --- 1. revert seeded source + tests to the clean baseline ---------------------
if [[ "$DO_GIT_RESTORE" -eq 1 ]]; then
    step "Reverting seeded source + tests to the committed baseline (git restore)"
    if git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
        # Scope the restore to the engine_demo trees only — leaves docs/tooling alone.
        git restore -- \
            "$TESTS_DIR" \
            src/engine_demo \
            include/engine_demo 2>/dev/null || true
        ok "git restore applied to tests/engine_demo, src/engine_demo, include/engine_demo"
    else
        warn "Not a git work tree — skipping restore. Verify the source state manually."
    fi
else
    step "Skipping git restore (--no-git): keeping current source edits"
fi

# --- 2. configure + build default-debug ----------------------------------------
step "Configuring + building the ${PRESET} preset"
cmake --preset "$PRESET" >/dev/null
cmake --build --preset "$PRESET" >/dev/null
ok "Build complete (binaryDir: build/)"

# --- 3. confirm every seeded test is still DISABLED_ ---------------------------
step "Confirming all 10 seeded regression tests are DISABLED_"
for entry in "${SEEDED_TESTS[@]}"; do
    name="${entry%%:*}"
    file="${entry##*:}"
    path="$TESTS_DIR/$file"
    if [[ ! -f "$path" ]]; then
        fail "Missing test file: $path"; READY=0; continue
    fi
    if grep -q "DISABLED_${name}" "$path"; then
        # Also ensure no ENABLED copy of the same case slipped through.
        if grep -E "TEST\(" "$path" | grep -q "[ ,]${name}\b" && \
           ! grep -E "TEST\(" "$path" | grep -q "DISABLED_${name}\b"; then
            fail "${name} appears ENABLED in ${file}"; READY=0
        else
            ok "${name} is DISABLED_ (${file})"
        fi
    else
        fail "${name} not found as DISABLED_ in ${file} (was it renamed/enabled?)"; READY=0
    fi
done

# --- 4. run the green baseline -------------------------------------------------
step "Running the full ${PRESET} suite (green baseline)"
if ctest --preset "$PRESET" --output-on-failure; then
    ok "All enabled tests passed"
else
    fail "ctest reported failures — the baseline is NOT green"; READY=0
fi

# --- 5. verdict ----------------------------------------------------------------
echo
if [[ "$READY" -eq 1 ]]; then
    echo "${BOLD}${GREEN}READY${RESET} — clean baseline, all seeded tests DISABLED_, suite green."
    echo "You can start the session."
    exit 0
else
    echo "${BOLD}${RED}NOT READY${RESET} — see the XX lines above. Resolve before starting."
    exit 1
fi
