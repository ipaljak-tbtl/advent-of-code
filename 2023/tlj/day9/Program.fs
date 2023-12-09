open System

let lines =
    (fun _ -> Console.ReadLine())
    |> Seq.initInfinite
    |> Seq.takeWhile (fun x -> x <> null)
    |> Seq.toList

let histories =
    lines |> List.map (fun l -> l.Split(" ") |> Array.map int |> Array.toList)

let rec extrapolateRight (h: list<int>) =
    let diff = h |> List.pairwise |> List.map (fun (a, b) -> b - a)

    let res =
        if diff |> List.exists (fun x -> x <> 0) then
            (List.last h) + extrapolateRight diff
        else
            (List.last h)

    res

let rec extrapolateLeft (h: list<int>) =
    let diff = h |> List.pairwise |> List.map (fun (a, b) -> b - a)

    let res =
        if diff |> List.exists (fun x -> x <> 0) then
            (List.head h) - extrapolateLeft diff
        else
            (List.head h)

    res

let extrapolatesRight = histories |> List.map extrapolateRight
let extrapolatesLeft = histories |> List.map extrapolateLeft

printfn "%d" (extrapolatesRight |> List.sum)
printfn "%d" (extrapolatesLeft |> List.sum)
