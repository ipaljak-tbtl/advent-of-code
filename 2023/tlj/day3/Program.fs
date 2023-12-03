open System

let lines =
    (fun _ -> Console.ReadLine())
    |> Seq.initInfinite
    |> Seq.takeWhile (fun x -> x <> null)
    |> Seq.toList

let board = lines |> Seq.map (fun l -> l.ToCharArray()) |> Seq.toArray

let boardHeight = board.Length
let boardWidth = board.[0].Length

let checkSurroundingForSymbol x y =
    let mutable res = false

    for i in (max 0 (x - 1)) .. (min (boardHeight - 1) (x + 1)) do
        for j in (max 0 (y - 1)) .. (min (boardWidth - 1) (y + 1)) do
            let chr = board.[i].[j]
            res <- res || (not (Char.IsDigit chr) && chr <> '.')

    res


let trueParts =
    [ for i in 0 .. boardHeight - 1 do
          let mutable curNum = None

          for j in 0 .. boardWidth - 1 do
              match (curNum, board.[i].[j]) with
              | (None, c) when Char.IsDigit c -> curNum <- Some(String [| c |])
              | (Some s, c) when Char.IsDigit c -> curNum <- Some(s + (String [| c |]))
              | (Some s, _) ->
                  if
                      seq { j - s.Length .. j - 1 }
                      |> Seq.exists (fun k -> checkSurroundingForSymbol i k)
                  then
                      yield (s, (i, j - s.Length))

                  curNum <- None

              | (_, _) -> ignore ()

          match curNum with
          | Some s ->
              if
                  seq { boardWidth - s.Length .. boardWidth - 1 }
                  |> Seq.exists (fun k -> checkSurroundingForSymbol i k)
              then
                  yield (s, (i, boardWidth - s.Length))
          | _ -> ignore () ]

let getGearRatio x y =
    let neighborDigits =
        [ for i in (max 0 (x - 1)) .. (min (boardHeight - 1) (x + 1)) do
              for j in (max 0 (y - 1)) .. (min (boardWidth - 1) (y + 1)) do
                  let c = board.[i].[j]

                  if Char.IsDigit c then
                      yield (i, j) ]

    let gearNumbers =
        trueParts
        |> Seq.filter (fun (s, (i, j)) ->
            neighborDigits
            |> Seq.exists (fun (ii, jj) -> ii = i && jj >= j && jj < j + s.Length))
        |> Seq.toList

    if gearNumbers.Length = 2 then
        gearNumbers
        |> Seq.map (fun (s, _) -> Int32.Parse(s))
        |> Seq.reduce (fun a b -> a * b)
    else
        0

printfn "%d" (trueParts |> Seq.map (fun (n, _) -> Int32.Parse(n)) |> Seq.sum)

let gearRatios =
    seq {
        for i in 0 .. boardHeight - 1 do
            for j in 0 .. boardWidth - 1 do
                let chr = board.[i].[j]

                if chr = '*' then
                    yield getGearRatio i j
    }

printfn "%d" (gearRatios |> Seq.sum)
