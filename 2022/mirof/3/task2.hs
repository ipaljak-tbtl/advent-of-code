import Data.Set as Set
import Data.List as List
import Data.Char

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

parse :: String -> [(Set Char)]
parse = List.map Set.fromList . lines

solve :: [Set Char] -> Int
solve [] = 0
solve (set1:set2:set3:list) = int_intersection + (solve list)
    where
          intersection     = Set.intersection set1 $ Set.intersection set2 set3
          int_intersection = convert_to_num $ head $ toList $ intersection

convert_to_num :: Char -> Int
convert_to_num char
    | ord char >= ord 'A' && ord char <= ord 'Z' = (ord char) - 65 + 27
    | ord char >= ord 'a' && ord char <= ord 'z' = (ord char) - 97 + 1

