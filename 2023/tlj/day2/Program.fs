open System


let lines =
    (fun _ -> Console.ReadLine())
    |> Seq.initInfinite
    |> Seq.takeWhile (fun x -> x <> null)
    |> Seq.toList

let parseCube (s: string) =
    let [| n; color |] = s.Trim().Split(" ")
    let n = Int32.Parse(n)

    match color with
    | "red" -> (n, 0, 0)
    | "green" -> (0, n, 0)
    | "blue" -> (0, 0, n)
    | _ -> failwith "Oslo ukurac"

let sumCubes (rgb: seq<(int * int * int)>) =
    rgb |> Seq.reduce (fun (r, g, b) (rn, gn, bn) -> (r + rn, g + gn, b + bn))

let minCubes (rgb: seq<(int * int * int)>) =
    rgb |> Seq.reduce (fun (r, g, b) (rn, gn, bn) -> (max r rn, max g gn, max b bn))

let parseDraw (s: string) = s.Split(",") |> Seq.map parseCube

let parseMultipleDraws (s: string) = s.Split(";") |> Seq.map parseDraw

let parseGame (s: string) =
    let [| gameInfo; draws |] = s.Split(":")

    let gameIdx = Int32.Parse(gameInfo.Trim().Split(" ").[1])

    gameIdx, parseMultipleDraws draws

let MAX_RED = 12
let MAX_GREEN = 13

let MAX_BLUE = 14

let validGames =
    lines
    |> Seq.map parseGame
    |> Seq.filter (fun (_, game) ->
        not (
            game
            |> Seq.map (sumCubes)
            |> Seq.exists (fun (r, g, b) -> r > MAX_RED || g > MAX_GREEN || b > MAX_BLUE)
        ))

let minGames =
    lines
    |> Seq.map parseGame
    |> Seq.map (fun (_, game) -> game |> Seq.map minCubes |> minCubes)
    |> Seq.map (fun (r, g, b) -> r * g * b)
    |> Seq.sum

printfn "%d" (validGames |> Seq.map (fun (g, _) -> g) |> Seq.sum)

printfn "%d" minGames
