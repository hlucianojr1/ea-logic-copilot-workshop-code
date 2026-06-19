// GoogleTest for engine_demo::sim::game_loop.

#include "engine_demo/sim/game_loop.h"

#include <gtest/gtest.h>

namespace {

TEST(game_loop, single_step_at_exact_period) {
    engine_demo::sim::game_loop gl{{1.0 / 60.0, 8.0}};
    EXPECT_EQ(gl.advance(1.0 / 60.0), 1u);
}

TEST(game_loop, no_steps_below_period) {
    engine_demo::sim::game_loop gl{{1.0 / 60.0, 8.0}};
    EXPECT_EQ(gl.advance(1.0 / 120.0), 0u);
}

// REGRESSION TEST for BUG-002 (drift). Expected to FAIL on the seeded `float`
// accumulator and PASS once Session 03 changes the member to `double` on stage.
//
// The seeded loop feeds delta == fixed_step, which never drifts; that input cannot
// expose the defect. Here we instead feed a sub-period delta (10 ms frames against a
// 1/60 s fixed step) and compare the loop against an inline double-precision reference
// running the identical algorithm. With the seeded `float` accumulator the two diverge
// at frame 4 because `static_cast<float>(0.01) == 0.00999999977f` under-accumulates;
// over 3600 frames the float loop fires 2159 substeps versus the reference's 2160.
TEST(game_loop, DISABLED_long_run_does_not_drift) {
    constexpr double kFixedStep = 1.0 / 60.0;
    constexpr double kMaxSubsteps = 8.0;
    constexpr double kFrameDelta = 1.0 / 100.0;  // 10 ms frames -> 0.6 substeps/frame
    constexpr int kFrames = 3600;                // 36 simulated seconds

    engine_demo::sim::game_loop gl{{kFixedStep, kMaxSubsteps}};

    // Inline double-precision reference (constitutional Article 5 mandate). The fixed
    // game loop runs this exact algorithm, so a corrected loop matches it bit-for-bit.
    double ref_accumulator = 0.0;
    std::uint32_t loop_total = 0;
    std::uint32_t ref_total = 0;

    for (int i = 0; i < kFrames; ++i) {
        const std::uint32_t loop_substeps = gl.advance(kFrameDelta);

        ref_accumulator += kFrameDelta;
        std::uint32_t ref_substeps = 0;
        while (ref_accumulator >= kFixedStep &&
               static_cast<double>(ref_substeps) < kMaxSubsteps) {
            ref_accumulator -= kFixedStep;
            ++ref_substeps;
        }

        loop_total += loop_substeps;
        ref_total += ref_substeps;
        EXPECT_EQ(loop_substeps, ref_substeps) << "substep drift at frame " << i;
    }

    EXPECT_EQ(loop_total, ref_total)
        << "cumulative substep drift over " << kFrames << " frames";
}

}  // namespace
