open System

let lines =
    (fun _ -> Console.ReadLine())
    |> Seq.initInfinite
    |> Seq.takeWhile (fun x -> x <> null)
    |> Seq.toList

let board = lines |> List.map Seq.toArray |> List.toArray

let boardWidth = board.[0].Length
let boardHeight = board.Length

let emptyRows =
    [ for i in 0 .. boardHeight - 1 do
          if board.[i] |> Array.forall (fun c -> c = '.') then
              yield int64 i ]

let emptyCols =
    [ for j in 0 .. boardWidth - 1 do
          if board |> Array.forall (fun row -> row.[j] = '.') then
              yield int64 j ]

let galaxies =
    [ for i in 0 .. boardHeight - 1 do
          for j in 0 .. boardWidth - 1 do
              if board.[i].[j] = '#' then
                  yield (int64 i, int64 j) ]


let galaxiesExpanded expansion =
    galaxies
    |> List.map (fun (i, j) ->
        let emptyRows = emptyRows |> Seq.filter (fun r -> r < i) |> Seq.length |> int64
        let emptyCols = emptyCols |> Seq.filter (fun c -> c < j) |> Seq.length |> int64

        (i + emptyRows * expansion - emptyRows, j + emptyCols * expansion - emptyCols))


let dists (galaxies: list<int64 * int64>) =
    [ for i in 0 .. galaxies.Length - 1 do
          for j in i + 1 .. galaxies.Length - 1 do
              let (i1, j1) = galaxies.[i]
              let (i2, j2) = galaxies.[j]

              yield abs (i1 - i2) + abs (j1 - j2) ]


printfn "%A" emptyRows
printfn "%A" emptyCols

printfn "%d" galaxies.Length
printfn "%d" (dists (galaxiesExpanded 1) |> List.sum)
printfn "%d" (dists (galaxiesExpanded 1000000) |> List.sum)
