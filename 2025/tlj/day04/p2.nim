import strutils
import sequtils

var inpt = toSeq(stdin.lines).mapIt(it.strip()).filterIt(it != "")

var res = 0

var inptCpy = inpt
while true:
    var removedRolls = 0
    for i in 0 ..< inpt.len:
        for j in 0 ..< inpt[0].len:
            var neighborCount = 0
            if inpt[i][j] != '@':
                continue

            for (di, dj) in [(-1, 0), (1, 0), (0, -1), (0, 1), (-1, -1), (-1,
                    1), (1, -1), (1, 1)]:
                let ni = i + di
                let nj = j + dj
                if ni >= 0 and ni < inpt.len and nj >= 0 and nj < inpt[0].len:
                    if inpt[ni][nj] == '@':
                        neighborCount += 1

            if neighborCount < 4:
                res += 1
                removedRolls += 1
                inptCpy[i][j] = '.'

    inpt = inptCpy

    if removedRolls == 0:
        break

echo "res = ", res
