Add-Type -AssemblyName System.Drawing
$img = [System.Drawing.Bitmap]::new('C:\Users\rrehman\source\repos\ea_copilot_workshop\output\ea-cpp-games\screenshot.png')
Write-Host ("Size: " + $img.Width + "x" + $img.Height)
$px = $img.GetPixel($img.Width / 2, $img.Height / 2)
Write-Host ("Center pixel R=" + $px.R + " G=" + $px.G + " B=" + $px.B)
$topleft = $img.GetPixel(10, 10)
Write-Host ("TopLeft pixel R=" + $topleft.R + " G=" + $topleft.G + " B=" + $topleft.B)
$img.Dispose()
