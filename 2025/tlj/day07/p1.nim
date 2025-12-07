import strutils
import sequtils

var diag = toSeq(stdin.lines).mapIt(it.strip()).filterIt(it != "")

let s = diag[0].find('S')

var res = 0

diag[1][s] = '|'

for i in countup(2, diag.len - 1, 2):
    for j in 0 ..< diag[0].len:
        if diag[i][j] == '^' and diag[i-1][j] == '|':
            diag[i+1][j+1] = '|'
            diag[i+1][j-1] = '|'
            diag[i][j+1] = '|'
            diag[i][j-1] = '|'
            res += 1
        elif diag[i][j] == '.' and diag[i-1][j] == '|':
            diag[i][j] = '|'
            diag[i+1][j] = '|'

echo "res = ", res

