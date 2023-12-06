{-# LANGUAGE NamedFieldPuns #-}

import Text.Read
import Data.Char
import Data.List (intersect, find)
import Data.Maybe

---------------- Parsing ---------------

parse :: String -> ([Integer], [Integer])
parse input = (times, distances)
    where
        input_lines = lines input
        times       = (map (\num -> read num :: Integer) . tail . words) (input_lines !! 0)
        distances   = (map (\num -> read num :: Integer) . tail . words) (input_lines !! 1)

----------------- Solve ----------------

solve :: ([Integer], [Integer]) -> Integer 
solve (times, distances) = foldl (*) 1 $ map calculate $ zip (map fromIntegral times) (map fromIntegral distances)

calculate :: (Double, Double) -> Integer
calculate (time, distance) = (floor x2_adjusted) - (ceiling x1_adjusted) + 1
    where
        x1 = (time - sqrt (time ^ 2 - 4 * distance)) / 2 
        x2 = (time + sqrt (time ^ 2 - 4 * distance)) / 2 
        x1_adjusted = if floor x1 == ceiling x1 then x1 + 1 else x1
        x2_adjusted = if floor x2 == ceiling x2 then x2 - 1 else x2
        
------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

