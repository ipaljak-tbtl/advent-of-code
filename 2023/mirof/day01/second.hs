import Text.Read
import Data.Char

main = do
    input <- readFile "input.txt"
    let solution = solve $ lines input
    putStrLn $ show solution


solve :: [String] -> Int
solve = sum . (map to_num) . (map take_first_and_last) . (map leave_digits) . (map convert_word_to_digit)

convert_word_to_digit :: String -> String 
convert_word_to_digit []                           = []
convert_word_to_digit list@('o':'n':'e':_)         = '1' : (convert_word_to_digit $ tail list)
convert_word_to_digit list@('t':'w':'o':_)         = '2' : (convert_word_to_digit $ tail list)
convert_word_to_digit list@('t':'h':'r':'e':'e':_) = '3' : (convert_word_to_digit $ tail list)
convert_word_to_digit list@('f':'o':'u':'r':_)     = '4' : (convert_word_to_digit $ tail list)
convert_word_to_digit list@('f':'i':'v':'e':_)     = '5' : (convert_word_to_digit $ tail list)
convert_word_to_digit list@('s':'i':'x':_)         = '6' : (convert_word_to_digit $ tail list)
convert_word_to_digit list@('s':'e':'v':'e':'n':_) = '7' : (convert_word_to_digit $ tail list)
convert_word_to_digit list@('e':'i':'g':'h':'t':_) = '8' : (convert_word_to_digit $ tail list)
convert_word_to_digit list@('n':'i':'n':'e':_)     = '9' : (convert_word_to_digit $ tail list)
convert_word_to_digit (c:list)                     =  c  : convert_word_to_digit         list

leave_digits :: String -> String
leave_digits = filter isDigit

take_first_and_last :: String -> (Char, Char) 
take_first_and_last list = (head list, last list)

to_num :: (Char, Char) -> Int
to_num (first, last) = digitToInt first * 10 + (digitToInt last)
