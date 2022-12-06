import Text.Read

main = do
    input <- readFile "input.txt"
    let solution = solve input
    putStrLn $ show solution

solve :: String -> Integer
solve input = count_processed (take 4 input) (drop 4 input) 4

count_processed :: String -> String -> Integer -> Integer
count_processed [w1, w2, w3, w4] (new_w:stream) counter
    | w1 == w2 || w1 == w3  || w1 == w4 || w2 == w3 || w2 == w4 || w3 == w4 = count_processed [w2, w3, w4, new_w] stream (counter + 1)
    | otherwise                                                             = counter
