$ErrorActionPreference = 'Stop'
$root = "C:\Users\ricog\3D Modeling\Inventor API work"
$src = "$root\scratch\dstv_exporter.vb"
$dir = "$root\scratch\compile_check"
New-Item -ItemType Directory -Force $dir | Out-Null

# Build harness: the iLogic rule body wrapped in a Module, plus a stub for
# the iLogic implicit global ThisApplication. The rule itself uses unqualified
# Inventor types and MessageBox - iLogic implicitly imports those namespaces,
# a standalone compile needs explicit Imports.
$body = [System.IO.File]::ReadAllText($src)
$nl = [string][char]13 + [string][char]10

$combined =
    'Imports System' + $nl +
    'Imports System.Collections.Generic' + $nl +
    'Imports System.Windows.Forms' + $nl +
    'Imports Inventor' + $nl +
    $nl +
    'Module DstvRule' + $nl +
    $body + $nl +
    'End Module' + $nl +
    $nl +
    'Module ILogicHost' + $nl +
    '    Public ThisApplication As Inventor.Application = Nothing' + $nl +
    'End Module' + $nl

[System.IO.File]::WriteAllText("$dir\harness.vb", $combined, (New-Object System.Text.UTF8Encoding($true)))
Write-Host "harness.vb written ($((Get-Item "$dir\harness.vb").Length) bytes)"

$vbc = 'C:\Windows\Microsoft.NET\Framework64\v4.0.30319\vbc.exe'
$interop = 'C:\Program Files\Autodesk\Inventor 2026\Bin\Public Assemblies\Autodesk.Inventor.Interop.dll'

$out = & $vbc /nologo /t:library /platform:x64 /out:"$dir\dstv_check.dll" /r:"$interop" /r:System.Windows.Forms.dll "$dir\harness.vb" 2>&1
$code = $LASTEXITCODE
Write-Host "vbc exit code: $code"
if ($out) {
    Write-Host "--- vbc output ---"
    foreach ($line in $out) { Write-Host $line }
}
if ($code -eq 0) {
    Write-Host 'COMPILE RESULT: PASS (BUILT)'
} else {
    Write-Host 'COMPILE RESULT: FAIL'
}