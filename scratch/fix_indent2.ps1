# Fix indentation of the rectangle debug line
$filepath = 'C:/Users/ricog/3D Modeling/Inventor API work/scratch/dstv_exporter.vb'
$lines = [System.IO.File]::ReadAllLines($filepath, [System.Text.Encoding]::UTF8)

for ($i = 0; $i -lt $lines.Count; $i++) {
    if ($lines[$i] -match 'OPENING \(rect\):.*angle=') {
        # Fix indentation to 6 tabs
        $lines[$i] = "`t`t`t`t`t`t`t" + $lines[$i].Trim()
    }
}

[System.IO.File]::WriteAllLines($filepath, $lines, [System.Text.Encoding]::UTF8)
Write-Host "Fixed indentation"
