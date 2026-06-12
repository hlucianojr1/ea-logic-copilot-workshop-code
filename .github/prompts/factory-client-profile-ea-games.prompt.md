---
description: Generate factory-overlay/client-profiles/ea-games.yaml — the EA client profile consumed by the workshop factory.
mode: agent
model: Claude Sonnet 4.6
tools: ["codebase", "edit"]
inputs: []
outputs:
  - path: factory-overlay/client-profiles/ea-games.yaml
    kind: file
    overwrite: false
validation:
  - 'node -e "const y=require(''yaml'');y.parse(require(''fs'').readFileSync(''factory-overlay/client-profiles/ea-games.yaml'',''utf8''))" || true'
  - "test -f factory-overlay/client-profiles/ea-games.yaml"
last_reviewed: 2026-04-29
reviewer: Insight Engagement Lead
---

## Objective

Encode the EA engagement as a YAML client-profile compatible with the existing
copilot-workshop-factory schema (see `axcelis-cplusplus.yaml` for the closest precedent).

## Context references

- Reference: `/Users/rrehman/Documents/projects/copilot-workshop-factory/client-profiles/axcelis-cplusplus.yaml`
- `#file:../../docs/engagement-charter.md`
- `#file:../instructions/cpp-snippets.instructions.md`

## Steps

Produce a YAML file with at minimum these top-level keys:

- `client`: `name: "Electronic Arts"`, `slug: "ea-games"`, `industry: "video-games"`,
  `team_size: ~`, `experience_level: advanced`, `copilot_familiarity: "prior sessions delivered"`.
- `stacks`: list with one entry id `cpp-game-engine` (mirroring the stack profile).
- `demo_project`: `type: generated`, `domain: games`, `app_name: engine_demo`, with a
  short description and recommended entities (Frame, Allocator, Entity, Component, System,
  PhysicsConstraint, RingBuffer, FixedString).
- `delivery`: `format: virtual`, `schedule: "9 sessions, 1 hour each"`,
  `copilot_plan: Enterprise`, `restrictions: []`, `output_location: new-repo`.
- `customization.must_include`: ["Agent Mode", "Custom Instructions", "Spec-Kit",
  "Coding Agent", "MCP Servers", "Multi-Agent Squad"].
- `customization.must_avoid`: ["std:: containers in committed code", "exceptions",
  "RTTI", "raw new/delete"].
- `customization.custom_mistakes`: at least 8 entries — the EA flavor of Copilot drift
  (mirroring Section 4 of `cpp-snippets.instructions.md`).
- `customization.custom_do_not`: at least 8 entries — explicit prohibitions.
- `customization.branding`: empty unless EA provides assets.

## Output contract

File exists; parses as YAML; matches the factory's expected schema.

## Self-validation

```bash
test -f factory-overlay/client-profiles/ea-games.yaml
node -e "const fs=require('fs');const t=fs.readFileSync('factory-overlay/client-profiles/ea-games.yaml','utf8');if(!t.includes('slug: \"ea-games\"'))process.exit(1)"
```

## Failure modes

- **Inventing team size**: leave as `~` (YAML null) until intake confirms; do not guess.
- **Listing internal EA tooling**: use only public, generic categories.
