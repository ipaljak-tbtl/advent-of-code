import strutils
import sequtils
import std/math

var diag = toSeq(stdin.lines).mapIt(it.strip()).filterIt(it != "")

let s = diag[0].find('S')

diag[1][s] = '|'

var pathCounts = newSeqWith(diag.len, newSeqWith(diag[0].len, 0))
pathCounts[1][s] = 1

for i in countup(2, diag.len - 1, 2):
    for j in 0 ..< diag[0].len:
        if diag[i][j] == '^' and pathCounts[i-1][j] > 0:
            let prevCount = pathCounts[i-1][j]
            pathCounts[i+1][j+1] += prevCount
            pathCounts[i+1][j-1] += prevCount

        elif diag[i][j] == '.' and pathCounts[i-1][j] > 0:
            let prevCount = pathCounts[i-1][j]
            pathCounts[i+1][j] += prevCount

let res = pathCounts[^1].sum()

echo "res = ", res
