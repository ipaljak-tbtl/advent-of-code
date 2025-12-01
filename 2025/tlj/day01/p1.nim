import strutils

var pos = 50
var pass = 0

for l in stdin.lines:
    var l = l.strip()
    if l == "":
        continue
    let dir = l[0]
    let dist = parseInt(l[1 .. l.len-1])
    case dir:
    of 'L':
        pos -= dist
    of 'R':
        pos += dist
    else:
        raise newException(ValueError, "Invalid direction: " & $dir)

    pos = pos mod 100
    if pos < 0:
        pos += 100

    echo "pos = ", pos

    if pos == 0:
        pass += 1

echo "pass = ", pass
