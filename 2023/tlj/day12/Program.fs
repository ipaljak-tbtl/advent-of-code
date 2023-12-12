open System

let lines =
    (fun _ -> Console.ReadLine())
    |> Seq.initInfinite
    |> Seq.takeWhile (fun x -> x <> null)
    |> Seq.toList

let conditions =
    lines
    |> List.map (fun l ->
        let [| conds; groups |] = l.Split(" ")

        let groups = groups.Split(",") |> Array.toList |> List.map int

        (conds |> Seq.toArray, groups))

let rec validCombinations (startFrom: int) (groupIdx: int) (conds: array<char>) groups : (list<int>) =
    match groups with
    | h :: rest ->
        let mutable alreadyVisited = Set.empty

        [ for i in startFrom - h .. conds.Length - 1 do

              let newConds =
                  conds
                  |> Array.mapi (fun ii c ->
                      if ii >= i && ii < i + h then
                          if c = '?' then (ii, '#') else (ii, c)
                      else
                          (ii, c))


              let damagedes =
                  [ let mutable from = 0
                    let mutable isIn = false

                    for (i, c) in newConds do
                        if not isIn then
                            if c = '#' then
                                isIn <- true
                                from <- i
                        else if c <> '#' then
                            isIn <- false
                            yield (from, i)


                    if isIn then
                        yield (from, newConds.Length) ]

              printfn "====="
              printfn "newConds = %A" newConds
              printfn "damagededs = %A" damagedes
              printfn "rest = %A" rest
              printfn "groupIdx = %d" groupIdx
              printfn "i = %d" i
              printfn "h = %d" h
              printfn "%A" ([] |> List.forall (fun x -> true))
              printfn "====="

              if
                  damagedes.Length > groupIdx
                  && damagedes
                     |> List.mapi (fun i x -> (i, x))
                     |> List.filter (fun (i, _) -> i < groupIdx)
                     |> List.forall (fun (_, (_, until)) -> until < i)
              then
                  let (dmgFrom, dmgTo) = damagedes.[groupIdx]

                  printfn "kurac h=%d dmgFrom=%d dmgTo=%d groupIdx=%d i=%d" h dmgFrom dmgTo groupIdx i

                  if dmgTo - dmgFrom = h then
                      printfn "tri kurca"

                      let newConds = (newConds |> Array.map (fun (_, c) -> c))

                      printfn "%A" alreadyVisited

                      if not (alreadyVisited |> Set.contains newConds) then

                          yield! validCombinations dmgTo (groupIdx + 1) newConds rest

                          alreadyVisited <- (alreadyVisited |> Set.add newConds) ]


    | [] ->
        printfn "==="
        printfn "picka"
        printfn "==="
        [ 1 ]


let nCombs = conditions |> List.map (fun (c, g) -> validCombinations 0 0 c g)


printfn "%A" (nCombs |> List.map List.length)
printfn "%d" (nCombs |> List.map List.length |> List.sum)
