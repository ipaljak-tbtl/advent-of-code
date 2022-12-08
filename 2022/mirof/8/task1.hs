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
solve matrix = sum $ map (\x -> if x then 1 else 0) andedFlattenMatricies
    where
        matrix0degrees        = visibleLeftToRightMatrix                                       matrix
        matrix90degrees       = (rotate . rotate . rotate . visibleLeftToRightMatrix . rotate) matrix
        matrix180degrees      = (rotate . rotate . visibleLeftToRightMatrix . rotate . rotate) matrix
        matrix270degrees      = (rotate . visibleLeftToRightMatrix . rotate . rotate . rotate) matrix
        andedFlattenMatricies = andFlattenMatricies matrix0degrees matrix90degrees matrix180degrees matrix270degrees

andFlattenMatricies :: [[Bool]] -> [[Bool]] -> [[Bool]] -> [[Bool]] -> [Bool]
andFlattenMatricies m1 m2 m3 m4 = res
    where
        a1  = map (\(x, y) -> x || y) $ zip (concat m1) (concat m2)
        a2  = map (\(x, y) -> x || y) $ zip a1          (concat m3)
        res = map (\(x, y) -> x || y) $ zip a2          (concat m4)

rotate :: [[a]] -> [[a]]
rotate = transpose . reverse

visibleLeftToRightMatrix :: [[Int]] -> [[Bool]]
visibleLeftToRightMatrix matrix = map (visibleLeftToRight (-1)) matrix

visibleLeftToRight :: Int -> [Int] -> [Bool]
visibleLeftToRight _          []         = []
visibleLeftToRight currentMax (elem:row) = (currentMax < elem) : (visibleLeftToRight (max currentMax elem) row)
