# IK invariant checker for generated NC1 files.
# Checks per IK block: 5 points, closed (first=last), 4 distinct corners,
# radius 0.00 everywhere, clockwise orientation (shoelace < 0).
param(
    [Parameter(Mandatory = $true)]
    [string]$Path
)

$lines = Get-Content $Path
$blocks = New-Object System.Collections.ArrayList
$cur = $null
$inIk = $false
$boD0Count = 0

foreach ($ln in $lines) {
    $t = $ln.Trim()

    if ($t -eq 'IK') {
        $inIk = $true
        $cur = New-Object System.Collections.ArrayList
        [void]$blocks.Add($cur)
        continue
    }

    if ($t -eq 'BO' -or $t -eq 'EN' -or $t -eq 'ST') {
        $inIk = $false
        $cur = $null
        continue
    }

    if ($inIk -and ($null -ne $cur)) {
        if ($t -match '^([ouvh]) +(-?[0-9]+\.[0-9]{2})[ous]? +(-?[0-9]+\.[0-9]{2}) +(-?[0-9]+\.[0-9]{2})$') {
            [void]$cur.Add(@{ X = [double]$Matches[2]; Y = [double]$Matches[3]; R = $Matches[4]; F = $Matches[1] })
        } elseif ($t -ne '') {
            Write-Output ("  MALFORMED IK line: [" + $t + "]")
        }
        continue
    }

    if ($t -match '^[ouvh] +\S+ +\S+ +0\.00 +0\.00l ') {
        $boD0Count++
    }
}

Write-Output ("File: " + $Path)
Write-Output ("IK blocks found: " + $blocks.Count)
Write-Output ("BO records with d=0.00+l (must be 0): " + $boD0Count)

$bi = 0
foreach ($blk in $blocks) {
    $bi++
    $n = $blk.Count
    $first = $blk[0]
    $last = $blk[$n - 1]
    $closed = ($first.X -eq $last.X -and $first.Y -eq $last.Y)
    $radiusOk = $true
    foreach ($p in $blk) { if ($p.R -ne '0.00') { $radiusOk = $false } }
    $uniq = ($blk[0..($n - 2)] | ForEach-Object { "$($_.X),$($_.Y)" } | Sort-Object -Unique).Count
    $faces = ($blk | ForEach-Object { $_.F } | Sort-Object -Unique)

    $area = 0.0
    for ($i = 0; $i -lt $n; $i++) {
        $j = ($i + 1) % $n
        $area += $blk[$i].X * $blk[$j].Y - $blk[$j].X * $blk[$i].Y
    }
    $orient = 'CLOCKWISE'
    if ($area -gt 0) { $orient = 'COUNTER-CLOCKWISE' }
    if ($area -eq 0) { $orient = 'DEGENERATE' }

    $verdict = 'OK'
    if (-not $closed) { $verdict = 'NOT CLOSED' }
    if ($uniq -ne 4) { $verdict = 'CORNER COUNT WRONG' }
    if (-not $radiusOk) { $verdict = 'RADIUS NOT ZERO' }
    if ($orient -ne 'CLOCKWISE') { $verdict = 'ORIENTATION WRONG' }

    Write-Output ("  IK#" + $bi + " face=" + ($faces -join '/') + " points=" + $n + " closed=" + $closed + " distinctCorners=" + $uniq + " radiusAllZero=" + $radiusOk + " shoelaceArea=" + $area + " -> " + $orient + "  [" + $verdict + "]")
}
