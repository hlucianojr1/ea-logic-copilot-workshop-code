Add-Type -AssemblyName System.Drawing
$img = [System.Drawing.Bitmap]::new('C:\Users\rrehman\source\repos\ea_copilot_workshop\output\ea-cpp-games\screenshot.png')
$w = $img.Width
$h = $img.Height
Write-Host ("Full size: " + $w + "x" + $h)

# Check all four quadrants
$qw = $w / 2
$qh = $h / 2

foreach ($qname in @("TopLeft","TopRight","BotLeft","BotRight")) {
    $ox = if ($qname -like "*Right") { $qw } else { 0 }
    $oy = if ($qname -like "Bot*")   { $qh } else { 0 }
    $nonDark = 0
    $step = 16
    for ($y = $oy; $y -lt ($oy + $qh); $y += $step) {
        for ($x = $ox; $x -lt ($ox + $qw); $x += $step) {
            $px = $img.GetPixel($x, $y)
            if ($px.R -gt 20 -or $px.G -gt 20 -or $px.B -gt 40) { $nonDark++ }
        }
    }
    Write-Host ($qname + ": non-dark=" + $nonDark)
}

# Sample center of each quadrant
foreach ($qname in @("TopLeft","TopRight","BotLeft","BotRight")) {
    $ox = if ($qname -like "*Right") { [int]($qw * 1.5) } else { [int]($qw * 0.5) }
    $oy = if ($qname -like "Bot*")   { [int]($qh * 1.5) } else { [int]($qh * 0.5) }
    $px = $img.GetPixel($ox, $oy)
    Write-Host ($qname + " center (" + $ox + "," + $oy + "): R=" + $px.R + " G=" + $px.G + " B=" + $px.B)
}
$img.Dispose()
