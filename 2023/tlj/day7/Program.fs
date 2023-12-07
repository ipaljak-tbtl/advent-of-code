open System

let lines =
    (fun _ -> Console.ReadLine())
    |> Seq.initInfinite
    |> Seq.takeWhile (fun x -> x <> null)
    |> Seq.toList

let strengths =
    [| '2'; '3'; '4'; '5'; '6'; '7'; '8'; '9'; 'T'; 'J'; 'Q'; 'K'; 'A' |]

let strengthsJoker =
    [| 'J'; '2'; '3'; '4'; '5'; '6'; '7'; '8'; '9'; 'T'; 'Q'; 'K'; 'A' |]


let hands =
    lines
    |> List.map (fun l ->
        let splt = l.Split(" ")
        (splt.[0], int splt.[1]))

let cardStrength c = Array.IndexOf(strengths, c)

let cardStrengthJoker c = Array.IndexOf(strengthsJoker, c)

let handStrength h =
    let groupedStrenghts = h |> List.map cardStrength |> List.groupBy (fun s -> s)

    let (_, maxStrength) = groupedStrenghts |> List.maxBy (fun (_, s) -> s.Length)
    let maxStrength = maxStrength.Length

    match maxStrength with
    | 5 -> 7
    | 4 -> 6
    | 3 ->
        if groupedStrenghts |> List.exists (fun (_, x) -> x.Length = 2) then
            5
        else
            4
    | 2 ->
        if groupedStrenghts |> List.filter (fun (_, x) -> x.Length = 2) |> List.length = 2 then
            3
        else
            2
    | 1 -> 1
    | _ -> failwith "jebajga"

let handStrengthJoker h =
    let groupedStrenghts =
        h
        |> List.filter (fun c -> c <> 'J')
        |> List.map cardStrengthJoker
        |> List.groupBy (fun s -> s)

    let jokers = h |> List.filter (fun c -> c = 'J') |> List.length

    if jokers = 5 then
        7
    else
        let (_, maxStrength) = groupedStrenghts |> List.maxBy (fun (_, s) -> s.Length)
        let maxStrength = maxStrength.Length

        match maxStrength with
        | 5 -> 7
        | 4 -> 6 + jokers
        | 3 ->
            if jokers > 0 then
                5 + jokers
            else if groupedStrenghts |> List.exists (fun (_, x) -> x.Length = 2) then
                5
            else
                4
        | 2 ->
            if jokers = 3 then
                7
            elif jokers = 2 then
                6
            elif jokers = 1 then
                if groupedStrenghts |> List.filter (fun (_, x) -> x.Length = 2) |> List.length = 2 then
                    5
                else
                    4
            else if groupedStrenghts |> List.filter (fun (_, x) -> x.Length = 2) |> List.length = 2 then
                3
            else
                2
        | 1 ->
            match jokers with
            | 0 -> 1
            | 1 -> 2
            | 2 -> 4
            | 3 -> 6
            | 4 -> 7
            | _ -> failwith "jebatga"
        | _ -> failwith "jebajga"

type HandType =
    | FiveOfAKind
    | FourOfAKind
    | ThreeOfAKind
    | TwoPair
    | OnePair
    | HighCard

let compareHands handStrength cardStrength a b =
    let a = a |> Seq.toList
    let b = b |> Seq.toList

    let sa = handStrength a
    let sb = handStrength b

    if sa = sb then
        let na = a |> List.map cardStrength
        let nb = b |> List.map cardStrength

        if na = nb then
            0
        else
            let (a, b) = List.zip na nb |> List.find (fun (a, b) -> compare a b <> 0)
            compare a b
    else
        compare sa sb


let sortedHands =
    hands
    |> List.sortWith (fun (h1, _) (h2, _) -> compareHands handStrength cardStrength h1 h2)

let sortedHandsJoker =
    hands
    |> List.sortWith (fun (h1, _) (h2, _) -> compareHands handStrengthJoker cardStrengthJoker h1 h2)

printfn
    "%d"
    (List.zip sortedHands [ 1 .. sortedHands.Length ]
     |> Seq.map (fun ((_, bid), i) -> bid * i)
     |> Seq.sum)

printfn
    "%d"
    (List.zip sortedHandsJoker [ 1 .. sortedHandsJoker.Length ]
     |> Seq.map (fun ((_, bid), i) -> bid * i)
     |> Seq.sum)
