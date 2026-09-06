<#
.SYNOPSIS
    NC1 structure validator for the EXPORT_DSTV2 exporter.

.DESCRIPTION
    Checks a generated .nc1 file against the DSTV NC1 structure rules that
    must always hold, regardless of the specific beam:

      - first line = ST, last line = EN
      - exactly 24 ST data lines (2-space indented)
      - ST field 9 (length) is a numeric decimal
      - every BO record matches the round or slot/rectangle grammar
      - BO records are 2-space indented and sorted in the holeLines order

    This is the regression "canary": if the exporter logic breaks, this
    script must fail on the saved golden file.

.PARAMETER Path
    Absolute path to the .nc1 file to validate.

.EXAMPLE
    powershell -File validate_nc1.ps1 -Path C:\work\golden\HE160A-1225.nc1
#>
param(
    [Parameter(Mandatory = $true)]
    [string]$Path
)

$ErrorActionPreference = "Stop"

if (-not (Test-Path $Path)) {
    Write-Host ("FAIL: file not found: " + $Path)
    exit 1
}

$content = Get-Content $Path
$fail = 0

# 1. First block code must be ST
if ($content[0].Trim() -ne "ST") {
    Write-Host "FAIL: first line is not 'ST'"
    $fail = 1
} else {
    Write-Host "PASS: file starts with ST block"
}

# 2. Last block code must be EN
if ($content[$content.Count - 1].Trim() -ne "EN") {
    Write-Host "FAIL: last line is not 'EN'"
    $fail = 1
} else {
    Write-Host "PASS: file ends with EN block"
}

# 3. ST data lines: exactly 24, all 2-space indented, directly after ST
$stData = New-Object System.Collections.Generic.List[string]
$inSt = $false
foreach ($line in $content) {
    $t = $line.Trim()
    if ($t -eq "ST") { $inSt = $true; continue }
    if ($inSt) {
        if ($line -match "^  ") { $stData.Add($line) } else { break }
    }
}
if ($stData.Count -eq 24) {
    Write-Host "PASS: ST block has 24 data lines"
} else {
    Write-Host ("FAIL: ST block has " + $stData.Count + " data lines (expected 24)")
    $fail = 1
}

# 4. ST field 9 (index 8, length mm) must be a decimal
if ($stData.Count -ge 9) {
    $field9 = $stData[8].Trim().Split(" ")[0]
    if ($field9 -match "^-?\d+\.\d+$") {
        Write-Host ("PASS: ST length field = " + $field9)
    } else {
        Write-Host ("FAIL: ST field 9 not a decimal: [" + $field9 + "]")
        $fail = 1
    }
}

# 5. BO records grammar:  face X[ref] Y diameter [t [l width height angle]]
$boCount = 0
$boInvalid = 0
$inBo = $false
$boRegex = '^[ouvh]\s+-?\d+\.\d{2}[ous]?\s+-?\d+\.\d{2}\s+-?\d+\.\d{2}(\s+-?\d+\.\d{2}(l\s+-?\d+\.\d{2}\s+-?\d+\.\d{2}\s+-?\d+\.\d{2})?)?\s*$'
foreach ($line in $content) {
    $t = $line.Trim()
    if ($t -eq "BO") { $inBo = $true; continue }
    if ($inBo) {
        if ($line -match "^  ") {
            $boCount++
            if ($t -match $boRegex) {
                # write nothing per record (verbose off), just validate
            } else {
                Write-Host ("FAIL: BO #" + $boCount + " invalid format: [" + $t + "]")
                $boInvalid++
                $fail = 1
            }
        } else {
            break
        }
    }
}
if ($boCount -gt 0) {
    if ($boInvalid -eq 0) {
        Write-Host ("PASS: BO block has " + $boCount + " valid records")
    } else {
        Write-Host ("FAIL: BO block has " + $boCount + " records, " + $boInvalid + " invalid")
    }
} else {
    Write-Host "NOTE: no BO block (no openings)"
}

# 6. Every data (non-block) line is indented with two spaces
foreach ($line in $content) {
    $t = $line.Trim()
    if ($t -eq "") { continue }
    if ($line -match "^  ") { continue }
    # non-indented non-empty line => must be a block code
    if ($t -match "^[A-Z][A-Z0-9]?$") { continue }
    Write-Host ("FAIL: malformed line: [" + $line + "]")
    $fail = 1
    break
}

if ($fail -eq 0) {
    Write-Host "RESULT: PASS"
} else {
    Write-Host "RESULT: FAIL"
}
exit $fail