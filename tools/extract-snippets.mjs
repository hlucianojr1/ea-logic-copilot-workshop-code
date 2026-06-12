#!/usr/bin/env node
// Extract fenced ```cpp blocks from markdown across the repo, write each one into the
// snippet-cmake-template, and verify they all compile under the engagement constraints
// (-std=c++20 -fno-exceptions -fno-rtti).
//
// Usage:
//   node tools/extract-snippets.mjs            # extract + build
//   node tools/extract-snippets.mjs --extract  # extract only
//   node tools/extract-snippets.mjs --json     # machine-readable summary

import { readFile, writeFile, mkdir, rm, readdir, stat } from "node:fs/promises";
import { existsSync } from "node:fs";
import { createHash } from "node:crypto";
import { spawnSync } from "node:child_process";
import path from "node:path";

const ROOT = process.cwd();
const TEMPLATE_DIR = path.join(ROOT, "tools", "snippet-cmake-template");
const SNIPPETS_DIR = path.join(TEMPLATE_DIR, "snippets");
const BUILD_DIR = path.join(TEMPLATE_DIR, "build");
const EXCLUDE = new Set(["node_modules", "output", "third_party", "build", ".git"]);

const args = new Set(process.argv.slice(2));
const wantJson = args.has("--json");
const extractOnly = args.has("--extract");

async function* walk(dir) {
  for (const entry of await readdir(dir, { withFileTypes: true })) {
    if (EXCLUDE.has(entry.name)) continue;
    const p = path.join(dir, entry.name);
    if (entry.isDirectory()) yield* walk(p);
    else if (entry.isFile() && p.endsWith(".md")) yield p;
  }
}

// Match fenced cpp blocks only when the fence starts at the beginning of a line (not inside
// inline code spans like `\`\`\`cpp` references). Closing fence must also be at line start.
// Blocks whose info-string contains `no-compile` are skipped (they're illustrative only).
const FENCE_RE = /^```cpp\b([^\n]*)\n([\s\S]*?)^```\s*$/gm;

function extractFromContent(content, file) {
  const blocks = [];
  let m;
  while ((m = FENCE_RE.exec(content)) !== null) {
    const info = m[1] || "";
    if (/\bno-compile\b/.test(info)) continue;
    const before = content.slice(0, m.index);
    const line = before.split("\n").length + 1;
    const code = m[2];
    blocks.push({
      file,
      line,
      code,
      hash: createHash("sha1")
        .update(file + ":" + line + ":" + code)
        .digest("hex")
        .slice(0, 12),
    });
  }
  return blocks;
}

async function gatherBlocks() {
  const out = [];
  for await (const file of walk(ROOT)) {
    const content = await readFile(file, "utf8");
    out.push(...extractFromContent(content, path.relative(ROOT, file)));
  }
  return out;
}

async function writeSnippets(blocks) {
  await rm(SNIPPETS_DIR, { recursive: true, force: true });
  await mkdir(SNIPPETS_DIR, { recursive: true });
  const tmpl = await readFile(path.join(TEMPLATE_DIR, "main.cpp.in"), "utf8");
  for (const b of blocks) {
    const wrapped = tmpl
      .replaceAll("/* SNIPPET_BODY */", b.code)
      .replaceAll("/* SNIPPET_ID */", b.hash)
      .replaceAll("/* SNIPPET_SOURCE */", `${b.file}:${b.line}`);
    await writeFile(path.join(SNIPPETS_DIR, `s_${b.hash}.cpp`), wrapped, "utf8");
  }
}

function build() {
  const cmake = spawnSync("cmake", ["-S", TEMPLATE_DIR, "-B", BUILD_DIR, "-G", "Ninja"], {
    stdio: "inherit",
  });
  if (cmake.status !== 0) return cmake.status;
  const b = spawnSync("cmake", ["--build", BUILD_DIR], { stdio: "inherit" });
  return b.status;
}

(async () => {
  const blocks = await gatherBlocks();
  if (!wantJson) console.log(`Found ${blocks.length} cpp block(s).`);
  await writeSnippets(blocks);
  if (extractOnly) {
    if (wantJson) console.log(JSON.stringify({ extracted: blocks.length, blocks }, null, 2));
    return;
  }
  if (!existsSync(path.join(TEMPLATE_DIR, "CMakeLists.txt"))) {
    console.error("Snippet CMake template missing.");
    process.exit(2);
  }
  const status = build();
  if (wantJson)
    console.log(JSON.stringify({ extracted: blocks.length, build_status: status }, null, 2));
  if (status !== 0) process.exit(status);
})().catch((e) => {
  console.error(e);
  process.exit(1);
});
