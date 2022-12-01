import Text.Read

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

parse :: String -> [Maybe Integer]
parse = map readInteger . lines

readInteger :: String -> Maybe Integer
readInteger input = readMaybe input :: Maybe Integer

solve :: [Maybe Integer] -> Integer
solve = maximum . sum_groups

sum_groups :: [Maybe Integer] -> [Integer]
sum_groups ((Just x) : ((Just y) : list))  = sum_groups $ (Just $ x + y) : list
sum_groups ((Just x) : ((Nothing) : list)) = [x] ++ sum_groups list
sum_groups [(Just x)]                      = [x]
