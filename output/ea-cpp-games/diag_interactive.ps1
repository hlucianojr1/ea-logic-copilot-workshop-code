Set-Location 'C:\Users\rrehman\source\repos\ea_copilot_workshop\output\ea-cpp-games'
$log = 'diag_run.txt'
if (Test-Path $log) { Remove-Item $log }
# Run interactively (no --screenshot) for 3 seconds, capture stderr
$p = Start-Process -FilePath '.\build\apps\sandbox\ea-sandbox.exe' -RedirectStandardError $log -PassThru -WindowStyle Normal
Start-Sleep -Seconds 3
$p.Kill()
Start-Sleep -Milliseconds 500
if (Test-Path $log) {
    Write-Host "=== STDERR (first 60 lines) ==="
    Get-Content $log | Select-Object -First 60
} else {
    Write-Host "No log file produced"
}
