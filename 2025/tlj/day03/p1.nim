import strutils

var res = 0

for l in stdin.lines:
    let l = l.strip()

    if l == "":
        continue

    var max = 0
    for i in 0 ..< l.len - 1:
        for j in i + 1 ..< l.len:
            let num = parseInt(l[i] & l[j])
            if num > max:
                max = num

    res += max

echo "res = ", res
