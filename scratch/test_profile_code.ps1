# TestProfileCode.ps1
# Focused regression test for GetDstvProfileCode in scratch/dstv_exporter.vb.
# Extracts the real function source, wraps it into a VB harness, compiles
# with vbc and runs the assertions. Repeatable; no Inventor needed.
$ErrorActionPreference = "Stop"
$root = "C:\Users\ricog\3D Modeling\Inventor API work"
$src = "$root\scratch\dstv_exporter.vb"
$dir = "$root\scratch\compile_check"
New-Item -ItemType Directory -Force $dir | Out-Null
$text = [IO.File]::ReadAllText($src)
$startMarker = "Function GetDstvProfileCode("
$si = $text.IndexOf($startMarker)
if ($si -lt 0) { throw "GetDstvProfileCode not found" }
$endMarker = "End Function"
$ei = $text.IndexOf($endMarker, $si)
if ($ei -lt 0) { throw "End Function not found" }
$func = $text.Substring($si, $ei - $si + $endMarker.Length)
$harness = [IO.File]::ReadAllText("$dir\profile_code_harness.vb")
$combined = $harness.Replace("%%FUNC%%", $func)
$vf = "$dir\profile_code_test.vb"
[IO.File]::WriteAllText($vf, $combined, [Text.UTF8Encoding]::new($false))
$vbc = "C:\Windows\Microsoft.NET\Framework64\v4.0.30319\vbc.exe"
$outExe = "$dir\profile_code_test.exe"
$out = & $vbc /nologo /t:exe /platform:x64 /out:$outExe /r:System.dll $vf 2>&1
$code = $LASTEXITCODE
Write-Host "vbc exit=$code"
if ($out) { $out | ForEach-Object { Write-Host $_ } }
if ($code -ne 0) { exit $code }
& $outExe
$rc = $LASTEXITCODE
Write-Host "test exit=$rc"
exit $rc