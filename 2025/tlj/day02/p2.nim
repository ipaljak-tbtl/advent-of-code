import strutils
import sequtils

let input = stdin.readAll().strip().split(",").mapIt(it.split("-"))

var res = 0

for i in input:
    let frm = parseInt(i[0])
    let to = parseInt(i[1])

    for j in frm .. to:
        let js = $j
        for k in 1 .. js.len div 2:
            if js.len mod k != 0:
                continue

            let isInvalid = toSeq(countup(0, js.len - 1 - k, k)).all do (
                it: int) -> bool:
                js[it ..< it + k] == js[it + k ..< it + 2*k]

            if isInvalid:
                res += j
                break

echo "res = ", res
