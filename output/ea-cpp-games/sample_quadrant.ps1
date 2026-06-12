Add-Type -AssemblyName System.Drawing
$img = [System.Drawing.Bitmap]::new('C:\Users\rrehman\source\repos\ea_copilot_workshop\output\ea-cpp-games\screenshot.png')
$w = $img.Width
$h = $img.Height
Write-Host ("Full size: " + $w + "x" + $h)

# Only sample the top-left quadrant where content should be (2560x1440 out of 5120x2880)
$qw = $w / 2
$qh = $h / 2
Write-Host ("Content quadrant: " + $qw + "x" + $qh)

$nonDark = 0
$step = 8
for ($y = 0; $y -lt $qh; $y += $step) {
    for ($x = 0; $x -lt $qw; $x += $step) {
        $px = $img.GetPixel($x, $y)
        if ($px.R -gt 30 -or $px.G -gt 30 -or $px.B -gt 50) {
            $nonDark++
        }
    }
}

# Sample center of content area at fine resolution
Write-Host "--- Center region pixels ---"
foreach ($row in 0..4) {
    foreach ($col in 0..4) {
        $x = [int]($qw * ($col + 0.5) / 5)
        $y = [int]($qh * ($row + 0.5) / 5)
        $px = $img.GetPixel($x, $y)
        Write-Host ("  ({0,4},{1,4}) R={2,3} G={3,3} B={4,3}" -f $x, $y, $px.R, $px.G, $px.B)
    }
}

$img.Dispose()
Write-Host ("Non-background pixels in content quadrant (sampled every 8px): " + $nonDark)
