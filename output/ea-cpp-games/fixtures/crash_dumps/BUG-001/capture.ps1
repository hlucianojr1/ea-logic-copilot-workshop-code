# Capture a Windows minidump for BUG-001.
#
# Requires: cl.exe (MSVC 19.38+) on PATH, ProcDump from Sysinternals on PATH.

$ErrorActionPreference = 'Stop'
Set-Location $PSScriptRoot

$root = (Resolve-Path "..\..\..").Path

cl.exe /nologo /std:c++20 /EHs-c- /GR- /Zi /Od `
    /I "$root\include" `
    "$root\src\engine_demo\allocator.cpp" `
    "repro.cpp" `
    /Fe:repro.exe /Fo:repro.obj /Fd:repro.pdb | Out-Null

if (Get-Command procdump -ErrorAction SilentlyContinue) {
    procdump -accepteula -ma -e .\repro.exe BUG-001.dmp.local
} else {
    Write-Warning "procdump not found; running unmonitored."
    .\repro.exe
}
