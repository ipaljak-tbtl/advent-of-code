import strutils
import sequtils

let lines = toSeq(stdin.lines).mapIt(it.strip())

let idx = lines.findIt(it == "")

let ranges = lines[0 ..< idx].mapIt do:
    let parts = it.split("-")
    (parts[0].parseInt(), parts[1].parseInt())

let inpts = lines[idx ..< lines.len].filterIt(it != "").mapIt(it.parseInt())

var res = 0
for i in inpts:
    var found = false
    for (low, high) in ranges:
        if i >= low and i <= high:
            found = true
            res += 1
            break

echo "res = ", res
