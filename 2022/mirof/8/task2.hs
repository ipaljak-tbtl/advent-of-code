import Text.Read
import Data.List (transpose)

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

parse :: String -> [[Int]]
parse = map (map readInt) . lines

readInt :: Char -> Int
readInt input = read [input] :: Int

solve :: [[Int]] -> Int
solve matrix = foldr1 max andedFlattenMatricies
    where
        matrix0degrees        = visibleLeftToRightMatrix                                       matrix
        matrix90degrees       = (rotate . rotate . rotate . visibleLeftToRightMatrix . rotate) matrix
        matrix180degrees      = (rotate . rotate . visibleLeftToRightMatrix . rotate . rotate) matrix
        matrix270degrees      = (rotate . visibleLeftToRightMatrix . rotate . rotate . rotate) matrix
        andedFlattenMatricies = andFlattenMatricies matrix0degrees matrix90degrees matrix180degrees matrix270degrees

andFlattenMatricies :: [[Int]] -> [[Int]] -> [[Int]] -> [[Int]] -> [Int]
andFlattenMatricies m1 m2 m3 m4 = res
    where
        a1  = map (\(x, y) -> x * y) $ zip (concat m1) (concat m2)
        a2  = map (\(x, y) -> x * y) $ zip a1          (concat m3)
        res = map (\(x, y) -> x * y) $ zip a2          (concat m4)

rotate :: [[a]] -> [[a]]
rotate = transpose . reverse

visibleLeftToRightMatrix :: [[Int]] -> [[Int]]
visibleLeftToRightMatrix matrix = map (visibleLeftToRight (-1)) matrix

visibleLeftToRight :: Int -> [Int] -> [Int]
visibleLeftToRight _       []         = []
visibleLeftToRight current (elem:row) = (count elem row 0) : (visibleLeftToRight elem row)

count :: Int -> [Int] -> Int -> Int
count _    []         counter = counter
count elem (tree:row) counter
    | elem <= tree = counter + 1
    | otherwise    = count elem row (counter + 1)

