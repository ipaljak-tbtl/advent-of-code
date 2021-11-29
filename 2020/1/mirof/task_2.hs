import Data.List

main = do
    inputData <- readFile "problem_01.txt"
    let numbers = map (\number -> read number :: Integer) $ lines inputData
    let Just (result, _) = find (\(product, sum) -> sum == 2020) $ [ (x*y*z, x+y+z) | x <- numbers, y <- numbers, z <- numbers ]
    putStrLn $ show result
