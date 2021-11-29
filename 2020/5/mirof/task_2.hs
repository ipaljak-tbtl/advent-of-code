import Data.List
import Data.List.Split
import Data.Maybe

main = readFile "problem_2.txt" >>= putStrLn . show . mySeatId . lines

mySeatId :: [String] -> Int
mySeatId allLines = (+1) $ fromJust $ pure fst <*> (find (\(x, y) -> y - x == 2) $ zip seatIds (tail seatIds))
    where seatIds = sortedSeatIds allLines

sortedSeatIds :: [String] -> [Int]
sortedSeatIds = sort . map (\(x, y) -> x * 8 + y) . map (\x -> calcSeatId ((take 7 x), (drop 7 x)))


calcSeatId :: (String, String) -> (Int, Int)
calcSeatId (row, column) = (convertToInt 'B' row, convertToInt 'R' column)

convertToInt :: Char -> String -> Int
convertToInt char = bitStringToInteger . reverse. map (==char)

bitStringToInteger :: [Bool] -> Int
bitStringToInteger [] = 0
bitStringToInteger (x:xs)
    | x == True  = 1 + 2 * bitStringToInteger xs
    | x == False = 2 * bitStringToInteger xs

