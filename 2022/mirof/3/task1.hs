import Data.Char
import Data.List
import Data.Set as Set (fromList, intersection, toList, Set)

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

parse :: String -> [(Set Char, Set Char)]
parse = map halve_to_sets . lines

halve_to_sets :: String -> (Set Char, Set Char)
halve_to_sets input = (fromList first_half, fromList second_half)
    where
        len         = length input `div` 2
        first_half  = take len input
        second_half = drop len input

solve :: [(Set Char, Set Char)] -> Int
solve = sum . map convert_to_num . map find_intersection

find_intersection :: (Set Char, Set Char) -> Char
find_intersection (set1, set2) = head $ toList $ intersection set1 set2

convert_to_num :: Char -> Int
convert_to_num char
    | ord char >= ord 'A' && ord char <= ord 'Z' = (ord char) - 65 + 27
    | ord char >= ord 'a' && ord char <= ord 'z' = (ord char) - 97 + 1

