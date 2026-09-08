$f = 'C:/Users/ricog/3D Modeling/Inventor API work/scratch/dstv_exporter.vb'
$lines = [System.IO.File]::ReadAllLines($f)

# Find and replace lines 1429-1431 (0-indexed: 1428-1430)
for ($i = 0; $i -lt $lines.Count; $i++) {
    if ($lines[$i] -like '*rectWidthMm*sizeXmm*') {
        $lines[$i] = $lines[$i] -replace 'sizeXmm', 'Math.Max(sizeXmm, sizeYmm)'
    }
    if ($lines[$i] -like '*rectHeightMm*sizeYmm*') {
        $lines[$i] = $lines[$i] -replace 'sizeYmm', 'Math.Min(sizeXmm, sizeYmm)'
    }
}

[System.IO.File]::WriteAllLines($f, $lines)
Write-Host 'Done'
