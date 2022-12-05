{-# LANGUAGE NamedFieldPuns #-}

import Text.Read

-- Number of elements that should be moved from source to destination
data Delta = Delta
    { elems       :: Int
    , source      :: Int
    , destination :: Int
    } deriving (Show)

main = do
    input <- readFile "input.txt"
    let initial_state = parseStacks $ lines input
    let deltas        = parseDeltas $ lines input
    let solution      = solve initial_state deltas
    putStrLn solution

parseStacks :: [String] -> [String]
parseStacks _ = [">", "PLMNWVBH", "HQM", "LMQFGBDN", "GWMQFTZ", "PHTM", "TGHDJMBC", "RVFBNM", "SGRMHLP", "NCBDP"]

parseDeltas :: [String] -> [Delta]
parseDeltas lines = map parseDelta instructions
    where
        instructions = tail $ dropWhile ((/=) "") lines

parseDelta :: String -> Delta
parseDelta line = Delta { elems, source, destination }
    where
        parts       = words line
        elems       = read (parts !! 1) :: Int
        source      = read (parts !! 3) :: Int
        destination = read (parts !! 5) :: Int

solve :: [String] -> [Delta] -> String
solve state [] = map head state
solve state (Delta { elems, source, destination } : deltas) = solve new_state deltas
    where
        intermedate_state = replace last_elems  state             destination
        new_state         = replace first_elems intermedate_state source
        first_elems       = drop elems (state !! source)
        last_elems        = (reverse $ take elems (state !! source)) ++ (state !! destination)

replace :: a -> [a] -> Int -> [a]
replace _    []          0     = []
replace elem (_:list)    0     = elem : list
replace e    (elem:list) index = elem : (replace e list (index - 1))
