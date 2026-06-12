Add-Type -AssemblyName System.Drawing
$img = [System.Drawing.Bitmap]::new('C:\Users\rrehman\source\repos\ea_copilot_workshop\output\ea-cpp-games\screenshot.png')
$width = $img.Width
$height = $img.Height
$nonDark = 0
$step = 4
for ($y = 0; $y -lt $height; $y += $step) {
    for ($x = 0; $x -lt $width; $x += $step) {
        $px = $img.GetPixel($x, $y)
        if ($px.R -gt 30 -or $px.G -gt 30 -or $px.B -gt 50) {
            $nonDark++
        }
    }
}
$img.Dispose()
Write-Host ("Non-background pixels (sampled every 4px): " + $nonDark)
