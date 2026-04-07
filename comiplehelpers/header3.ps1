$lines=[System.IO.File]::ReadAllLines('%~f0')
$b64=''
$in=$false
foreach($l in $lines){
    if($l -eq ':BEGIN_B64'){$in=$true;continue}
    if($l -eq ':END_B64'){break}
    if($in){$b64+=$l}
}
$bytes=[Convert]::FromBase64String($b64)
[System.IO.File]::WriteAllBytes($env:TMP_OUT,$bytes)