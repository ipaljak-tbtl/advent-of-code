import strutils

var pos = 50
var pass = 0

for l in stdin.lines:
    let l = l.strip()
    if l == "":
        continue
    let dir = l[0]
    let dist = parseInt(l[1 .. l.len-1])
    case dir:
    of 'L':
        for _ in 1 .. dist:
            pos -= 1
            if pos == 0:
                pass += 1

            if pos < 0:
                pos += 100
    of 'R':
        for _ in 1 .. dist:
            pos += 1
            if pos == 100:
                pos -= 100

            if pos == 0:
                pass += 1
    else:
        raise newException(ValueError, "Invalid direction: " & $dir)


echo "pass = ", pass
