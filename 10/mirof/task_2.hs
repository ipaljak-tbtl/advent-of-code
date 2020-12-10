import Data.List
import Data.List.Split

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . combinations . parseInputData

parseInputData :: String -> [Int]
parseInputData input = sort $ [0] ++ (map (\x -> read x :: Int) $ lines input)

combinations :: [Int] -> Int
combinations numbers = foldl (\acc x -> acc * (countCombinations x)) 1 $ map (\x -> (length x) + 1)  $ filter (/=[]) $ splitOn [3] (zipWith (-) (tail numbers) numbers ++ [3])

countCombinations :: Int -> Int
countCombinations 0      = 0
countCombinations 1      = 1
countCombinations 2      = 1
countCombinations 3      = 2
countCombinations number = (countCombinations (number - 1)) + (countCombinations (number - 2)) + (countCombinations (number - 3))

