open System

let lines =
    (fun _ -> Console.ReadLine())
    |> Seq.initInfinite
    |> Seq.takeWhile (fun x -> x <> null)
    |> Seq.toList

let cards =
    lines
    |> Seq.map (fun l ->
        let nums = l.Split(":").[1]
        let [| winning; got |] = nums.Split("|")

        let winning =
            winning.Split(" ") |> Seq.filter (fun x -> x <> "") |> Seq.map int |> Seq.toList

        let got =
            got.Split(" ") |> Seq.filter (fun x -> x <> "") |> Seq.map int |> Seq.toList

        (winning, got))

let results1 =
    cards
    |> Seq.map (fun (winning, got) ->
        let intersect = Set.intersect (Set.ofList winning) (Set.ofList got)

        if intersect.Count = 0 then
            0
        else
            pown 2 (intersect.Count - 1))

let results2 =
    let nwinning =
        cards
        |> Seq.map (fun (winning, got) ->
            let intersect = Set.intersect (Set.ofList winning) (Set.ofList got)

            intersect.Count)
        |> Seq.toArray

    let mutable ncards = [| for i in 0 .. nwinning.Length - 1 -> 1 |]


    for i in 0 .. nwinning.Length - 1 do
        for _ in 0 .. ncards[i] - 1 do
            for k in 1 .. nwinning.[i] do
                if k + i <= ncards.Length - 1 then
                    ncards.[k + i] <- ncards.[k + i] + 1

    ncards




printfn "%d" (results1 |> Seq.sum)
printfn "%d" (results2 |> Seq.sum)
