{-# LANGUAGE NamedFieldPuns #-}

import Data.Char

---------------- Parsing ---------------

parse :: String -> [String]
parse []         = [] 
parse (',':rest) = parse rest
parse input      = (takeWhile (/=',') input) : parse (dropWhile (/=',') input)

----------------- Solve ----------------

solve :: [String] -> Int
solve = sum . map (solve_entry 0) 

solve_entry :: Int -> String -> Int
solve_entry acc []       = acc
solve_entry acc (c:rest) = solve_entry ((acc + ord c) * 17 `mod` 256 ) rest 
        
------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse $ init input -- remove endline with init
    putStrLn $ show solution

