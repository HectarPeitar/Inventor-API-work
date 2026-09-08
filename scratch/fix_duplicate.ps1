$filepath = 'C:/Users/ricog/3D Modeling/Inventor API work/scratch/dstv_exporter.vb'
$lines = [System.IO.File]::ReadAllLines($filepath, [System.Text.Encoding]::UTF8)

# Find duplicate facePos blocks after holeZ) in the rectangle section
# We need to find: holeZ) followed by Dim facePos ... holeZ) (duplicate)

$inDuplicate = $false
$output = @()

for ($i = 0; $i -lt $lines.Count; $i++) {
    $line = $lines[$i]
    
    if ($inDuplicate) {
        # Skip lines until we find holeZ) which ends the duplicate block
        if ($line -match 'holeZ\)') {
            $inDuplicate = $false
        }
        continue
    }
    
    $output += $line
    
    # Check if this line contains holeZ) and the next line starts a duplicate facePos
    if ($line -match 'holeZ\)$') {
        $nextLine = $lines[$i + 1]
        if ($nextLine -match 'Dim facePos As Double') {
            # Check if this is a duplicate (the previous holeZ) was also followed by facePos)
            # We're in the duplicate scenario - skip the next facePos block
            $inDuplicate = $true
        }
    }
}

[System.IO.File]::WriteAllLines($filepath, $output, [System.Text.Encoding]::UTF8)
Write-Host "Fixed duplicate facePos blocks. Lines: $($lines.Count) -> $($output.Count)"
