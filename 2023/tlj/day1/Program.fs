open System

let lines =
    (fun _ -> Console.ReadLine())
    |> Seq.initInfinite
    |> Seq.takeWhile (fun x -> x <> null)
    |> Seq.toList

let get_sum lines =
    lines
    |> Seq.map (String.filter Char.IsDigit)
    |> Seq.map (fun dg -> Int32.Parse($"{dg.[0]}{dg.[dg.Length - 1]}"))
    |> Seq.sum

let sum_fp = lines |> get_sum

let sum_sp =
    lines
    |> Seq.map (fun s ->
        seq {
            for i in 0 .. s.Length - 1 do
                if s.Substring(i).StartsWith("one") then yield '1'
                elif s.Substring(i).StartsWith("two") then yield '2'
                elif s.Substring(i).StartsWith("three") then yield '3'
                elif s.Substring(i).StartsWith("four") then yield '4'
                elif s.Substring(i).StartsWith("five") then yield '5'
                elif s.Substring(i).StartsWith("six") then yield '6'
                elif s.Substring(i).StartsWith("seven") then yield '7'
                elif s.Substring(i).StartsWith("eight") then yield '8'
                elif s.Substring(i).StartsWith("nine") then yield '9'
                else yield s.[i]
        }
        |> String.Concat)
    |> get_sum

// First part
printfn "%d" sum_fp

// Second part
printfn "%d" sum_sp
