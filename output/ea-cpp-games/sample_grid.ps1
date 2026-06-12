Add-Type -AssemblyName System.Drawing
$img = [System.Drawing.Bitmap]::new('C:\Users\rrehman\source\repos\ea_copilot_workshop\output\ea-cpp-games\screenshot.png')
$w = $img.Width
$h = $img.Height
Write-Host ("Size: " + $w + "x" + $h)

# Sample a grid of 25 points across the image
$points = @()
foreach ($row in 0..4) {
    foreach ($col in 0..4) {
        $x = [int]($w * ($col + 0.5) / 5)
        $y = [int]($h * ($row + 0.5) / 5)
        $px = $img.GetPixel($x, $y)
        $points += ("  ({0,4},{1,4}) R={2,3} G={3,3} B={4,3}" -f $x, $y, $px.R, $px.G, $px.B)
    }
}
$img.Dispose()
$points | ForEach-Object { Write-Host $_ }
