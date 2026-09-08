$f = Get-Content 'C:/Users/ricog/3D Modeling/Inventor API work/scratch/dstv_exporter.vb'
for ($i = 1334; $i -lt 1350; $i++) {
    Write-Output ("{0}: {1}" -f ($i+1), $f[$i])
}