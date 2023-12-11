open System

let lines =
    (fun _ -> Console.ReadLine())
    |> Seq.initInfinite
    |> Seq.takeWhile (fun x -> x <> null)
    |> Seq.toList

let instructions = lines.[0]

let maps =
    lines[2..]
    |> List.map (fun l ->
        let src = l.Split("=").[0].Trim()

        let [| l; r |] = l.Split("=").[1].Split(", ")

        let l = l[2..]

        let r = r.[0 .. r.Length - 2]

        (src, (l, r)))
    |> Map

let steps =
    let mutable pos = "AAA"

    Seq.initInfinite (fun i -> instructions.[i % instructions.Length])
    |> Seq.takeWhile (fun i ->
        let res = pos <> "ZZZ"

        let (l, r) = maps.[pos]

        match i with
        | 'L' -> pos <- l
        | 'R' -> pos <- r
        | _ -> failwith "jabajga"

        res)
    |> Seq.toList


let gcd (n1: int64) (n2: int64) =
    seq { (min n1 n2) .. -1L .. 1L } |> Seq.find (fun i -> n1 % i = 0 && n2 % i = 0)


let ghostSteps =
    let positions = maps.Keys |> Seq.filter (fun k -> k.EndsWith("A")) |> Seq.toArray

    let posLenghts =
        positions
        |> Seq.map (fun p ->
            let mutable pos = p

            Seq.initInfinite (fun i -> instructions.[i % instructions.Length])
            |> Seq.takeWhile (fun i ->
                let res = not (pos.EndsWith("Z"))

                let (l, r) = maps.[pos]

                match i with
                | 'L' -> pos <- l
                | 'R' -> pos <- r
                | _ -> failwith "jabajga"

                res)
            |> Seq.toList
            |> Seq.length)
        |> Seq.map int64
        |> Seq.toList

    posLenghts |> List.fold (fun lcm x -> lcm * x / (gcd lcm x)) 1




printfn "%d" (steps.Length)
printfn "%d" (ghostSteps)
