open System

let lineso =
    (fun _ -> Console.ReadLine())
    |> Seq.initInfinite
    |> Seq.takeWhile (fun x -> x <> null)
    |> Seq.toArray

let seeds = lineso.[0].Split(": ").[1].Split(" ") |> Seq.map int64 |> Seq.toList

let seedRanges =
    seq { 0..2 .. seeds.Length - 1 }
    |> Seq.map (fun i -> (seeds[i], seeds[i + 1]))
    |> Seq.toArray

let lines = lineso |> Array.skip 2

let gmaps =
    lines
    |> Seq.mapi (fun i l ->

        if l.Contains("map") then
            Some lines[i + 1 .. (Seq.findIndex (fun l -> l = "") lines[i + 1 ..] + i)]
        else
            None)
    |> Seq.choose (fun l -> l)
    |> Seq.map (fun maps ->
        maps
        |> Array.map (fun l ->
            let map = l.Split(" ") |> Array.map int64
            (map.[0], map.[1], map.[2]))
        |> Array.toList)
    |> Seq.toList

let mapId id map =
    match (map |> Seq.tryFind (fun (_, src, len) -> id >= src && id <= src + len - 1L)) with
    | Some(dest, src, _) -> dest + (id - src)
    | None -> id


let mapSeed maps s = maps |> Seq.fold mapId s

type Point =
    | MapLeft of (int64 * int64)
    | MapRight of int64

let rec mapSeedRange (id, (len: int64)) (maps: list<list<(int64 * int64 * int64)>>) =
    match maps with
    | hmap :: rest ->
        let left = id
        let right = id + len - 1L

        let sortedMaps =
            hmap
            |> List.map (fun (dest, src, lenm) -> [ MapLeft(dest, src); MapRight(src + lenm - 1L) ])
            |> List.concat
            |> List.sortBy (fun m ->
                match m with
                | MapLeft(_, i) -> i
                | MapRight i -> i)

        let sortedMaps =
            let (MapLeft(_, srcf)) = List.head sortedMaps
            let (MapRight srcl) = List.last sortedMaps

            [ MapLeft(Int64.MinValue, Int64.MinValue); MapRight(srcf - 1L) ]
            @ sortedMaps
            @ [ MapLeft(srcl + 1L, srcl + 1L); MapRight(Int64.MaxValue - 1L) ]


        sortedMaps
        |> List.pairwise
        |> List.map (fun (m1, m2) ->
            match (m1, m2) with
            | (MapLeft(dest, l), MapRight r) ->
                let f = max left l
                let t = min right r

                if f <= t then
                    mapSeedRange (dest + (f - l), t - f + 1L) rest
                else
                    []
            | (MapRight f, MapLeft(_, t)) ->
                let f = max left (f + 1L)
                let t = min right (t - 1L)

                if f <= t then mapSeedRange (f, t - f + 1L) rest else []
            | _ -> failwith "jebajga")
        |> List.concat
    | [] -> [ id ]

let mappedSeeds = seeds |> Seq.map (mapSeed gmaps)

let mappedSeedRanges =
    seedRanges
    |> Seq.map (fun r -> mapSeedRange r gmaps)
    |> Seq.concat
    |> Seq.toList

printfn "%d" (mappedSeeds |> Seq.min)
printfn "%d" (mappedSeedRanges |> Seq.min)
