---
description: Generate factory-overlay/domain-profiles/games.md — domain profile for AAA game development.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit", "fetch"]
inputs: []
outputs:
  - path: factory-overlay/domain-profiles/games.md
    kind: file
    overwrite: false
validation:
  - "test -f factory-overlay/domain-profiles/games.md"
  - "npm run lint"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Capture the **AAA games** domain profile: open-source landscape, EASTL conventions, public
EA repos relevant to this engagement, and demo-app archetypes.

## Context references

- `#file:../../docs/engagement-charter.md`
- Public source: `https://github.com/electronicarts` (EASTL, Cnc_Red_Alert, etc.)

## Steps

1. Sections to produce:
   - **Identity** — id `games`, sub-domains (engine, gameplay, tools).
   - **Public OSS landscape** — `EASTL`, `Cnc_Red_Alert`, `EAStdC`, `EAAssert`,
     `EAStdC` (verify current names via the org page; do not invent).
   - **Compliance / IP guardrails** — never reference EA-internal repo names; use only
     public org repos as exemplars; redact any screenshots that include internal data.
   - **Demo-app archetypes** — three options at increasing complexity:
     1. _Allocator pool + frame budget_ (small).
     2. _ECS with deterministic update loop_ (medium).
     3. _Physics constraint solver atop the ECS_ (large; used by Sessions 6–9).
   - **Crash-dump / fixture conventions** — minidump + matched PDB + source rev tag,
     reproducible from open-source code only.
   - **Real-time constraints** — frame budgets (16.67 ms @ 60 FPS, 8.33 ms @ 120 FPS),
     allocation-in-inner-loop forbidden, branch-prediction-friendly idioms.
   - **Multi-million-line codebase patterns** — per-subsystem `SUBSYSTEM.md` summaries used
     as Copilot context anchors; named `#file:`/`#sym:` recipes; instruction-file scoping
     via `applyTo` per subsystem folder.

## Output contract

File exists with all seven sections; references only public EA org repos by URL.

## Self-validation

```bash
grep -q "github.com/electronicarts" factory-overlay/domain-profiles/games.md
grep -q "## Multi-million-line" factory-overlay/domain-profiles/games.md
npm run lint
```

## Failure modes

- **Inventing repo names**: do not list `Cnc_Generals` or any other repo not actually under
  the public org. When in doubt, fetch the org page and verify.
- **Speculating on internal EA practices**: keep the profile to publicly visible patterns.
