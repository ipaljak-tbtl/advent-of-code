import strutils
import sequtils

let input = stdin.readAll().strip().split(",").mapIt(it.split("-"))

var res = 0

for i in input:
    let frm = parseInt(i[0])
    let to = parseInt(i[1])

    for j in frm .. to:
        let js = $j
        if js[0 ..< js.len div 2] == js[js.len div 2 ..< js.len]:
            res += j

echo "res = ", res
