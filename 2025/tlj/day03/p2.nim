import strutils

var res = 0

for l in stdin.lines:
    let l = l.strip()

    if l == "":
        continue

    var maxIdx = 0
    var maxBat = ""
    for i in countdown(11, 0, 1):
        var localMax = 0
        for j in maxIdx ..< l.len - i:
            let li = parseInt($l[j])
            if li > localMax:
                localMax = li
                maxIdx = j + 1
        maxBat = maxBat & $localMax

    res += parseInt(maxBat)

echo "res = ", res
