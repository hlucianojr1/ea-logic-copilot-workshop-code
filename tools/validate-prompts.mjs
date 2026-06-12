#!/usr/bin/env node
// Validate front-matter on every customization file under .github/{prompts,instructions,chatmodes}.
// Schemas are intentionally lenient: required fields only; warn on stale `last_reviewed`.
//
// Usage:
//   node tools/validate-prompts.mjs
//   node tools/validate-prompts.mjs --json

import { readFile, readdir } from "node:fs/promises";
import path from "node:path";

const ROOT = process.cwd();
const TARGETS = [
  {
    dir: ".github/prompts",
    suffix: ".prompt.md",
    required: ["description", "mode", "outputs", "last_reviewed", "reviewer"],
  },
  {
    dir: ".github/instructions",
    suffix: ".instructions.md",
    required: ["applyTo", "last_reviewed", "reviewer"],
  },
  {
    dir: ".github/chatmodes",
    suffix: ".chatmode.md",
    required: ["description", "model", "tools", "last_reviewed", "reviewer"],
  },
];
const STALE_DAYS = 90;
const wantJson = process.argv.includes("--json");

async function* walk(dir) {
  let entries;
  try {
    entries = await readdir(dir, { withFileTypes: true });
  } catch {
    return;
  }
  for (const e of entries) {
    const p = path.join(dir, e.name);
    if (e.isDirectory()) yield* walk(p);
    else if (e.isFile()) yield p;
  }
}

function parseFrontMatter(text) {
  if (!text.startsWith("---\n")) return null;
  const end = text.indexOf("\n---", 4);
  if (end === -1) return null;
  const body = text.slice(4, end);
  const out = {};
  let key = null;
  for (const line of body.split("\n")) {
    const m = line.match(/^([A-Za-z_][A-Za-z0-9_]*):\s*(.*)$/);
    if (m) {
      key = m[1];
      out[key] = m[2].trim();
    } else if (key && /^\s*-\s+/.test(line)) {
      out[key] = Array.isArray(out[key]) ? out[key] : out[key] ? [out[key]] : [];
      out[key].push(line.replace(/^\s*-\s+/, "").trim());
    }
  }
  return out;
}

function staleDays(iso) {
  const d = Date.parse(iso);
  if (Number.isNaN(d)) return Infinity;
  return Math.floor((Date.now() - d) / 86_400_000);
}

const findings = [];
for (const t of TARGETS) {
  const dir = path.join(ROOT, t.dir);
  for await (const f of walk(dir)) {
    if (!f.endsWith(t.suffix)) continue;
    const text = await readFile(f, "utf8");
    const fm = parseFrontMatter(text);
    const rel = path.relative(ROOT, f);
    if (!fm) {
      findings.push({
        file: rel,
        severity: "Critical",
        message: "Missing or unparseable front-matter",
      });
      continue;
    }
    for (const req of t.required) {
      if (!(req in fm) || fm[req] === "") {
        findings.push({
          file: rel,
          severity: "Significant",
          message: `Missing required field: ${req}`,
        });
      }
    }
    if (fm.last_reviewed && staleDays(fm.last_reviewed) > STALE_DAYS) {
      findings.push({
        file: rel,
        severity: "Minor",
        message: `last_reviewed is older than ${STALE_DAYS} days`,
      });
    }
  }
}

if (wantJson) {
  console.log(JSON.stringify({ findings }, null, 2));
} else {
  for (const f of findings) console.log(`[${f.severity}] ${f.file}: ${f.message}`);
  console.log(findings.length === 0 ? "OK: no findings." : `Total findings: ${findings.length}`);
}
process.exit(
  findings.some((f) => f.severity === "Critical" || f.severity === "Significant") ? 1 : 0,
);
