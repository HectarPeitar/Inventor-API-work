$f = 'C:/Users/ricog/3D Modeling/Inventor API work/scratch/dstv_exporter.vb'
$lines = [System.IO.File]::ReadAllLines($f)

for ($i = 0; $i -lt $lines.Count; $i++) {
    if ($lines[$i] -like '*Math.Max(sizeXmm, sizeYmm)*') {
        $lines[$i] = $lines[$i] -replace 'Math\.Max\(sizeXmm, sizeYmm\)', 'sizeYmm'
    }
    if ($lines[$i] -like '*Math.Min(sizeXmm, sizeYmm)*') {
        $lines[$i] = $lines[$i] -replace 'Math\.Min\(sizeXmm, sizeYmm\)', 'sizeXmm'
    }
}

[System.IO.File]::WriteAllLines($f, $lines)
Write-Host 'Done'
