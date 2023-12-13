{-# LANGUAGE NamedFieldPuns #-}

import Debug.Trace

---------------- Models ----------------

data Problem = Problem {
    state  :: [Char],
    target :: [Int]
} deriving (Show)

---------------- Parsing ---------------

parse :: String -> [Problem]
parse = map parse_line . lines
        
parse_line :: String -> Problem
parse_line line = Problem {
    state = tokens !! 0,
    target
}
    where
        tokens = words line
        target = map (\x -> read x :: Int) $ words $ map (\x -> if x == ',' then ' ' else x) $ tokens !! 1

----------------- Solve ----------------

solve :: [Problem] -> Int
solve = sum . map (\Problem { state, target } -> solve_problem state target)

solve_problem :: [Char] -> [Int]-> Int
solve_problem [] [] = 1
solve_problem [] _  = 0

solve_problem ('?':state) [] = solve_problem state []
solve_problem ('#':state) [] = 0                     
solve_problem ('.':state) t  = solve_problem state t 

solve_problem state allt@(num:target)
    | num == possible_size && num == length state                          = solve_target
    | num <= possible_size && (state !! num == '.' || state !! num == '?') = if head state == '#' then solve_target else (solve_problem (tail state) allt) + solve_target 
    | head state == '#'                                                    = 0
    | otherwise                                                            = solve_problem (tail state) allt
    where
        prefix         = takeWhile (\field -> field == '?' || field == '#') state
        possible_size  = length prefix
        solve_target   = solve_problem (drop (num + 1) state) target

failproof_tail :: [a] -> [a]
failproof_tail []   = []
failproof_tail list = tail list 

------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

