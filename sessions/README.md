# sessions/

One folder per workshop session. Folder names are kebab-case `NN-slug`.

Contents are **generated** by the corresponding Tier-3 prompt
(`.github/prompts/session-NN-*.prompt.md`). Do not edit by hand. To scaffold a new session
stub manually: `npm run scaffold:session -- --number NN --slug my-slug`.

Each folder contains:

- `facilitator-script.md`
- `learner-guide.md`
- `slides.outline.md`
- `exercises/01-*.md`, `exercises/02-*.md`
- `retro-survey.md`
- `pre-work-email.md`
