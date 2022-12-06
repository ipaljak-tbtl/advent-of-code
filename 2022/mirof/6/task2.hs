import Text.Read
import Data.Set (fromList)

main = do
    input <- readFile "input.txt"
    let solution = solve input
    putStrLn $ show solution

solve :: String -> Int
solve input = count_processed (take 14 input) (drop 14 input) 14

count_processed :: String -> String -> Int -> Int
count_processed window (new_w:stream) counter
    | distinct_elements_len == 14 = counter
    | otherwise                   = count_processed (tail window ++ [new_w]) stream (counter + 1)
    where
        distinct_elements_len = (length . fromList) window
