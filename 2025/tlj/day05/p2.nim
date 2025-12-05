import strutils
import sequtils
import std/algorithm

let lines = toSeq(stdin.lines).mapIt(it.strip())

type Range = enum
    From, To

let idx = lines.findIt(it == "")

let ranges = lines[0 ..< idx].mapIt do:
    let parts = it.split("-")
    (parts[0].parseInt(), parts[1].parseInt())


var newRanges: seq[(Range, int)] = @[]

for (f, t) in ranges:
    newRanges.add((Range.From, f))
    newRanges.add((Range.To, t))

newRanges.sort do (a, b: (Range, int)) -> int:
    let valCmp = cmp(a[1], b[1])
    if valCmp == 0:
        if a[0] == Range.From and b[0] == Range.To:
            return -1
        elif a[0] == Range.To and b[0] == Range.From:
            return 1
        else:
            return 0
    else:
        return valCmp

var fromStack: seq[int] = @[]
var res = 0

for (rType, v) in newRanges:
    case rType:
    of Range.From:
        fromStack.add(v)
    of Range.To:
        let lastFrom = fromStack.pop()
        if fromStack.len == 0:
            res += v - lastFrom + 1

echo "res = ", res
