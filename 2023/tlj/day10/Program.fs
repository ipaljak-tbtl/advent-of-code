open System

let lines =
    (fun _ -> Console.ReadLine())
    |> Seq.initInfinite
    |> Seq.takeWhile (fun x -> x <> null)
    |> Seq.toList

let board = lines |> List.map Seq.toArray |> List.toArray

let boardWidth = board.[0].Length
let boardHeight = board.Length

let startPos =
    seq {
        for i in 0 .. boardHeight - 1 do
            for j in 0 .. boardWidth - 1 do
                if board.[i].[j] = 'S' then
                    yield (i, j)
    }
    |> Seq.head

let getNeighbors (i, j) =
    let res =
        match board.[i].[j] with
        | 'S' -> [ (i + 1, j); (i, j + 1); (i - 1, j); (i, j - 1) ]
        | '.' -> []
        | '-' -> [ (i, j - 1); (i, j + 1) ]
        | '|' -> [ (i + 1, j); (i - 1, j) ]
        | 'F' -> [ (i + 1, j); (i, j + 1) ]
        | 'J' -> [ (i - 1, j); (i, j - 1) ]
        | '7' -> [ (i + 1, j); (i, j - 1) ]
        | 'L' -> [ (i - 1, j); (i, j + 1) ]
        | _ -> failwith "jebajga"

    res
    |> List.filter (fun (i, j) -> i >= 0 && i < boardHeight && j >= 0 && j < boardWidth)

let rec longestLoop (fi, fj) (i, j) visited =
    let neighbors =
        getNeighbors (i, j) |> List.filter (fun n -> not (visited |> List.contains n))

    let res = if (fi, fj) = (i, j) then visited else []

    neighbors
    |> List.map (fun n -> longestLoop (fi, fj) n (visited @ [ n ]))
    |> List.append [ res ]
    |> List.sortBy (fun l -> l.Length)
    |> List.tryLast
    |> Option.defaultValue []


let theLoop = (longestLoop startPos startPos [])
let loopSet = theLoop |> Set


let rec floodFill (i, j) (previouslyFilled: Set<int * int>) =

    if (loopSet |> Set.contains (i, j)) || (previouslyFilled |> Set.contains (i, j)) then
        (0, previouslyFilled)
    else
        let mutable filled = previouslyFilled

        filled <- filled.Add(i, j)

        let mutable queue = [ (i, j) ]

        let mutable res = 0

        while not queue.IsEmpty do
            let (i, j) = queue.Head

            queue <- queue.Tail

            res <- res + 1

            let neighbors =
                [ (i + 1, j); (i, j + 1); (i - 1, j); (i, j - 1) ]
                |> List.filter (fun (i, j) -> i >= 0 && i < boardHeight && j >= 0 && j < boardWidth)
                |> List.filter (fun (i, j) -> not (loopSet |> Set.contains (i, j)))
                |> List.filter (fun (i, j) -> not (filled |> Set.contains (i, j)))

            filled <- filled |> Set.union (Set neighbors)
            queue <- queue @ neighbors

        (res, filled)

printfn "%A" startPos

printfn "%A" (theLoop.Length / 2)


let (enclosed, _) =
    theLoop
    |> List.pairwise
    |> List.mapFold
        (fun previouslyFilled ((i1, j1), (i2, j2)) ->
            if i1 = i2 then
                if j2 > j1 then
                    floodFill (i1 + 1, j2) previouslyFilled
                else
                    floodFill (i1 - 1, j1) previouslyFilled
            else if i2 > i1 then
                floodFill (i2, j1 - 1) previouslyFilled
            else
                floodFill (i1, j1 + 1) previouslyFilled)
        Set.empty

let (enclosed2, _) =
    theLoop
    |> List.pairwise
    |> List.mapFold
        (fun previouslyFilled ((i1, j1), (i2, j2)) ->
            if i1 = i2 then
                if j2 > j1 then
                    floodFill (i1 - 1, j2) previouslyFilled
                else
                    floodFill (i1 + 1, j1) previouslyFilled
            else if i2 > i1 then
                floodFill (i2, j1 + 1) previouslyFilled
            else
                floodFill (i1, j1 - 1) previouslyFilled)
        Set.empty

printfn "%d" (enclosed |> List.sum)
printfn "%d" (enclosed2 |> List.sum)
