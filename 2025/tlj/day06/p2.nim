import strutils
import sequtils
import std/math

let lines = toSeq(stdin.lines).filterIt(it != "")

let nums = lines[0 .. ^2]

let opLine = lines[^1]

let opsIdx = toSeq(0 ..< opLine.len).filterIt(opLine[it] in ['+', '*'])

var ops = zip(opsIdx, opsIdx[1 .. ^1])
ops.add((opsIdx[^1], opLine.len))

var res = 0

for (opf, opt) in ops:
    let opChar = opLine[opf]

    let operands = toSeq(opf ..< opt).mapIt(cast[string](toSeq(0 ..<
            nums.len).map(proc(i: int): char = nums[i][it])).strip()).filterIt(
                    it != "").mapIt(it.parseInt())
    case opChar
    of '+':
        res += operands.sum()
    of '*':
        res += operands.prod()
    else:
        raise newException(ValueError, "Unknown op: " & $opChar)

echo "res = ", res
