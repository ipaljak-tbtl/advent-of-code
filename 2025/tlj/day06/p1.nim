import strutils
import sequtils
import std/math

let lines = toSeq(stdin.lines).mapIt(it.strip()).filterIt(it != "")

let nums = lines[0 .. ^2].mapIt(it.splitWhitespace().mapIt(it.parseInt()))

let ops = lines[^1].splitWhitespace()

var res = 0

for i in 0 ..< nums[0].len:
    let op = ops[i]

    case op
    of "+":
        res += toSeq((0 ..< nums.len)).mapIt(nums[it][i]).sum()
    of "*":
        res += toSeq((0 ..< nums.len)).mapIt(nums[it][i]).prod()
    else:
        raise newException(ValueError, "Unknown op: " & op)

echo "res = ", res
