{-# LANGUAGE NamedFieldPuns #-}

import Text.Read
import Data.Char
import Data.List (intersect, find, intercalate)
import Data.Maybe

---------------- Parsing ---------------

parse :: String -> (Integer, Integer)
parse input = (times, distances)
    where
        input_lines = lines input
        times       = read ((intercalate "" . tail . words) (input_lines !! 0)) :: Integer
        distances   = read ((intercalate "" . tail . words) (input_lines !! 1)) :: Integer

----------------- Solve ----------------

solve :: (Integer, Integer) -> Integer 
solve (time, distance) = calculate ((fromIntegral time), (fromIntegral distance))

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

