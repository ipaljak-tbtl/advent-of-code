import Text.Read
import Data.Char

main = do
    input <- readFile "input.txt"
    let solution = solve $ lines input
    putStrLn $ show solution


solve :: [String] -> Int
solve = sum . (map to_num) . (map take_first_and_last) . (map leave_digits)

leave_digits :: String -> String
leave_digits = filter isDigit

take_first_and_last :: String -> (Char, Char) 
take_first_and_last list = (head list, last list)

to_num :: (Char, Char) -> Int
to_num (first, last) = digitToInt first * 10 + (digitToInt last)
