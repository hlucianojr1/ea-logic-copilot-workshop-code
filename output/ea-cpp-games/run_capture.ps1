Set-Location 'C:\Users\rrehman\source\repos\ea_copilot_workshop\output\ea-cpp-games'
$exe = '.\build\apps\sandbox\ea-sandbox.exe'
$proc = Start-Process -FilePath $exe -ArgumentList '--screenshot','screenshot.png','--warmup','90' -PassThru -Wait
Write-Host "Exit code: $($proc.ExitCode)"
if (Test-Path 'screenshot.png') {
    Write-Host "Screenshot saved: $(Resolve-Path 'screenshot.png')"
} else {
    Write-Host "No screenshot found"
}

