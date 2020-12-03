import Data.List.Split
import Data.List

main = do
    inputData <- readFile "problem_1.txt"
    let allLines = lines inputData

    let rowJump = (length $ splitOn "" $ allLines !! 0) - 1
    let columnJump = 3

    let result = length $ filter id $ countTrees 0 allLines

    putStrLn $ show result


countTrees :: Int -> [String] -> [Bool]
countTrees _ [] = []
countTrees startIndex (xs:ys) = [currentChar == '#'] ++ countTrees nextIndex ys
    where currentChar = xs !! startIndex
          nextIndex = mod (startIndex + 3) (length xs)
