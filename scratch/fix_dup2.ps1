$filepath = 'C:/Users/ricog/3D Modeling/Inventor API work/scratch/dstv_exporter.vb'
$lines = [System.IO.File]::ReadAllLines($filepath, [System.Text.Encoding]::UTF8)

# Remove the duplicate debug comment
$output = @()
$skipNext = $false
for ($i = 0; $i -lt $lines.Count; $i++) {
    if ($skipNext) {
        $skipNext = $false
        continue
    }
    
    $line = $lines[$i]
    
    # Check for the duplicate pattern
    if ($line -match "DEBUG: per-opening face decision \(rectangle\)") {
        # Check if the next line is also the same pattern (with blank line between)
        $j = $i + 1
        while ($j -lt $lines.Count -and $lines[$j].Trim() -eq "") {
            $j++
        }
        if ($j -lt $lines.Count -and $lines[$j] -match "DEBUG: per-opening face decision \(rectangle\)") {
            # Skip this one, keep the second one
            continue
        }
    }
    
    $output += $line
}

[System.IO.File]::WriteAllLines($filepath, $output, [System.Text.Encoding]::UTF8)
Write-Host "Removed duplicate. Lines: $($lines.Count) -> $($output.Count)"
