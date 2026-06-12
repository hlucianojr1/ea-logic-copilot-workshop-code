#!/usr/bin/env node
// Scaffold a new session under sessions/NN-slug/ from the canonical 7-file template.
// Usage:
//   node tools/new-session.mjs <NN> <slug> "<title>"

import { mkdir, writeFile, readdir, access } from "node:fs/promises";
import path from "node:path";

const [nn, slug, title] = process.argv.slice(2);
if (!nn || !slug || !title) {
  console.error('Usage: node tools/new-session.mjs <NN> <slug> "<title>"');
  process.exit(2);
}

const dir = path.join(process.cwd(), "sessions", `${nn}-${slug}`);
try {
  await access(dir);
  console.error(`Refusing to overwrite ${dir}`);
  process.exit(2);
} catch {
  // good
}

await mkdir(path.join(dir, "exercises"), { recursive: true });

const today = new Date().toISOString().slice(0, 10);
const stub = (kind) =>
  `---\nsession: ${nn}\ntitle: "${title}"\nkind: ${kind}\nlast_reviewed: ${today}\nreviewer: Insight Engagement Lead\n---\n\n# ${title} — ${kind}\n\nTODO\n`;

const files = {
  "facilitator-script.md": stub("facilitator-script"),
  "learner-guide.md": stub("learner-guide"),
  "slides.outline.md": stub("slides-outline"),
  "retro-survey.md": stub("retro-survey"),
  "pre-work-email.md": stub("pre-work-email"),
  "exercises/01-todo.md": stub("exercise"),
};

for (const [name, content] of Object.entries(files)) {
  await writeFile(path.join(dir, name), content, "utf8");
}
console.log(`Created ${dir}`);
