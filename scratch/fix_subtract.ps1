$filepath = 'C:/Users/ricog/3D Modeling/Inventor API work/scratch/dstv_exporter.vb'
$lines = [System.IO.File]::ReadAllLines($filepath, [System.Text.Encoding]::UTF8)

for ($i = 0; $i -lt $lines.Count; $i++) {
    # Replace projected.Subtract(normalComponent)
    if ($lines[$i] -match '^\s*projected\.Subtract\(normalComponent\)') {
        $lines[$i] = $lines[$i] -replace 'projected\.Subtract\(normalComponent\)', 'projected = ThisApplication.TransientGeometry.CreateVector(projected.X - normalComponent.X, projected.Y - normalComponent.Y, projected.Z - normalComponent.Z)'
    }
    # Replace xProjected.Subtract(xNormalComponent)
    if ($lines[$i] -match '^\s*xProjected\.Subtract\(xNormalComponent\)') {
        $lines[$i] = $lines[$i] -replace 'xProjected\.Subtract\(xNormalComponent\)', 'xProjected = ThisApplication.TransientGeometry.CreateVector(xProjected.X - xNormalComponent.X, xProjected.Y - xNormalComponent.Y, xProjected.Z - xNormalComponent.Z)'
    }
}

[System.IO.File]::WriteAllLines($filepath, $lines, [System.Text.Encoding]::UTF8)
Write-Host "Fixed Subtract calls"
