# sessions/

One folder per workshop session. Folder names are kebab-case `NN-slug`.

Contents are **generated** by the corresponding Tier-3 prompt
(`.github/prompts/session-NN-*.prompt.md`). Do not edit by hand. To scaffold a new session
stub manually: `npm run scaffold:session -- --number NN --slug my-slug`.

Each folder contains:

- `facilitator-script.md`
- `learner-guide.md`
- `slides.outline.md`
- `exercises/01-*.md` … `exercises/NN-*.md`
- `retro-survey.md`
- `pre-work-email.md`

Session 03 additionally ships:

- `logic-bug-workshop-training.md` — instructor deep-dive (CoT/ToT/HITL, agents)
- `sdlc-walkthrough.md` — full issue → branch → agent fix → PR → CI → merge loop
- `qa-track.md` — QA/SDET verification track (test plans, FP triage, gate sign-off)
- `fallback-screenshots/` — capture checklist for demo recovery
