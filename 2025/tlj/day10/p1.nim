import strutils
import sequtils
import std/tables

let inpt = stdin.lines.toSeq().filterIt(it.strip() != "").mapIt do:
    let splt = it.split(" ")
    let conf = splt[0][1 ..< ^1]
    let buttons = splt[1 ..< ^1].mapIt do:
        it[1 ..< ^1].split(",").mapIt it.parseInt()
    (conf, buttons)

proc bfs(start: string, finish: string, buttons: seq[seq[int]]): int =
    var queue: seq[(string, int)] = @[(start, 0)]
    var visited = initTable[string, bool]()

    while queue.len > 0:
        let (curr, dist) = queue[0]
        queue = queue[1 ..< queue.len]

        if curr == finish:
            return dist

        if visited.contains(curr):
            continue
        visited[curr] = true

        for button in buttons:
            var newConf = curr
            for i in 0 ..< button.len:
                let pos = button[i]
                newConf[pos] = if newConf[pos] == '#': '.' else: '#'
            queue.add((newConf, dist + 1))

    return -1

var res = 0

for (conf, buttons) in inpt:
    echo "Processing conf = ", conf, "  buttons = ", buttons
    let dist = bfs(repeat('.', conf.len), conf, buttons)
    if dist != -1:
        res += dist

echo "res = ", res
