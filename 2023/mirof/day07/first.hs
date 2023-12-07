{-# LANGUAGE NamedFieldPuns #-}

import Text.Read
import Data.Char
import Data.List (sort, sortBy, group)
import Numeric (readHex)
import Data.Ord

---------------- Models ----------------

data Hand = Hand {
    cards        :: String,
    power        :: Integer, -- power of card combination
    second_power :: Integer,
    value        :: Integer
        
} deriving (Eq, Show)

instance Ord Hand where
    (<=) h1 h2 
        | power h1 == power h2 = second_power h1 < second_power h2
        | otherwise = power h1 < power h2

---------------- Parsing ---------------

parse :: String -> [Hand] 
parse input = hands
    where   
        input_lines = map words $ lines input
        hands = map parse_line input_lines

parse_line :: [String] -> Hand
parse_line [cards, value] = Hand {
    cards        = hex_cards,
    power        = calc_power cards,
    second_power = fst $ head $ readHex hex_cards,
    value        = read value :: Integer
} 
    where
        hex_cards = map card_to_hex cards

card_to_hex :: Char -> Char
card_to_hex 'A' = 'E'
card_to_hex 'K' = 'D'
card_to_hex 'Q' = 'C'
card_to_hex 'J' = 'B'
card_to_hex 'T' = 'A'
card_to_hex  x  =  x 

calc_power :: String -> Integer 
calc_power cards 
    | any (== 5) grouped                       = 6
    | any (== 4) grouped                       = 5
    | any (== 3) grouped && any (== 2) grouped = 4
    | any (== 3) grouped                       = 3
    | length (filter (==2) grouped) == 2       = 2
    | any (== 2) grouped                       = 1
    | otherwise                                = 0
        where
            grouped = map length $ group $ sort cards  

----------------- Solve ----------------

solve :: [Hand] -> Integer
solve = sum . map (\(index, value) -> index * value) . zip [1..] . map value . sort 
        
------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

