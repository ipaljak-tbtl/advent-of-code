open System

let lines =
    (fun _ -> Console.ReadLine())
    |> Seq.initInfinite
    |> Seq.takeWhile (fun x -> x <> null)
    |> Seq.toList


let times =
    lines.[0].Split(":").[1].Split(" ")
    |> Array.filter (fun s -> s <> "")
    |> Array.map int

let megaTime = lines.[0].Split(":").[1].Replace(" ", "") |> int64

let megaDistance = lines.[1].Split(":").[1].Replace(" ", "") |> int64

let records =
    lines.[1].Split(":").[1].Split(" ")
    |> Array.filter (fun s -> s <> "")
    |> Array.map int


let simulateGame (buttonPressTime: int64) (maxTime: int64) =
    (maxTime - buttonPressTime) * buttonPressTime

let results =
    Array.zip times records
    |> Array.map (fun (t, d) ->
        [ for i in 0 .. t - 1 do
              if simulateGame i t > d then yield 1 else yield 0 ]
        |> List.sum)

printfn "%d" (results |> Array.reduce (fun x y -> x * y))

printfn
    "%d"
    (seq {
        for i in 0L .. megaTime - 1L do
            if simulateGame i megaTime > megaDistance then
                yield true
     }
     |> Seq.length)
