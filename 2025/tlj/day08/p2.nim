import strutils
import sequtils
import std/[tables, sets]
import std/math
import std/algorithm

let boxes = toSeq(stdin.lines).filterIt(it != "").mapIt(it.split(",").mapIt(
    parseInt(it)))

var circuits = initTable[seq[int], ref HashSet[seq[int]]]()

var diffs: seq[(int, (seq[int], seq[int]))] = @[]

for i in 0 ..< boxes.len - 1:
    for j in i + 1 ..< boxes.len:
        var diff = 0
        for k in 0 ..< boxes[i].len:
            diff += (boxes[i][k] - boxes[j][k]) * (boxes[i][k] - boxes[j][k])

        diffs.add((diff, (boxes[i], boxes[j])))

diffs.sort do (a, b: (int, (seq[int], seq[int]))) -> int:
    cmp(a[0], b[0])

for i in 0 ..< diffs.len:
    let boxi = diffs[i][1][1]
    let boxj = diffs[i][1][0]

    let hasCircuitI = boxi in circuits
    let hasCircuitJ = boxj in circuits

    if hasCircuitI and hasCircuitJ:
        let ci = circuits[boxi]
        let cj = circuits[boxj]

        if ci != cj:
            ci[].incl(cj[])
            for j in ci[]:
                circuits[j] = ci

    elif hasCircuitI:
        let ci = circuits[boxi]
        ci[].incl(boxj)
        circuits[boxj] = ci

    elif hasCircuitJ:
        let cj = circuits[boxj]
        cj[].incl(boxi)
        circuits[boxi] = cj

    else:
        var newSet: ref HashSet[seq[int]]
        new(newSet)
        newSet[] = initHashSet[seq[int]]()
        newSet[].incl(boxi)
        newSet[].incl(boxj)
        circuits[boxi] = newSet
        circuits[boxj] = newSet


    if circuits.values.toSeq()[0][].len == boxes.len:
        echo "res = ", boxi[0] * boxj[0]
        break



