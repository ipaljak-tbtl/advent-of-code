import Data.List

main = do
    inputData <- readFile "problem_01.txt"
    let numbers = map (\number -> read number :: Integer) $ lines inputData
    let Just (result, _) = find (\(product, sum) -> sum == 2020) $ [ (x*y, x+y) | x <- numbers, y <- numbers]
    putStrLn $ show result
