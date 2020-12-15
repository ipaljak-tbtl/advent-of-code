import Data.List.Split
import Data.List

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . findNumber 2020 . parseInputData

parseInputData :: String -> [Int]
parseInputData = map read . filter (/="") . splitOn ","

findNumber :: Int -> [Int] -> Int
findNumber index list
    | (length list) == index = last list
    | doesLastAlreadyExist = findNumber index (list ++ [(length list) - (last indices) - 1])
    | otherwise            = findNumber index (list ++ [0])
        where doesLastAlreadyExist = indices /= []
              indices              = elemIndices (last list) (init list)

