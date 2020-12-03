import Data.List.Split
import Data.List

main = do
    inputData <- readFile "problem_2.txt"
    let allLines = lines inputData

    let rowJump = (length $ splitOn "" $ allLines !! 0) - 1
    let columnJump = 3

    let slope1 = length $ filter id $ countTrees 1 0 allLines
    let slope2 = length $ filter id $ countTrees 3 0 allLines
    let slope3 = length $ filter id $ countTrees 5 0 allLines
    let slope4 = length $ filter id $ countTrees 7 0 allLines
    let slope5 = length $ filter id $ countTrees 1 0 [line | (index, line) <- zip [0,1..] allLines, (index `mod` 2) == 0]

    putStrLn $ show (slope1)
    putStrLn $ show (slope2)
    putStrLn $ show (slope3)
    putStrLn $ show (slope4)
    putStrLn $ show (slope5)
    putStrLn $ show (slope1 * slope2 * slope3 * slope4 * slope5)


countTrees :: Int -> Int -> [String] -> [Bool]
countTrees _ _ [] = []
countTrees rightStep startIndex (xs:ys) = [currentChar == '#'] ++ countTrees rightStep nextIndex ys
    where currentChar = xs !! startIndex
          nextIndex = mod (startIndex + rightStep) (length xs)

