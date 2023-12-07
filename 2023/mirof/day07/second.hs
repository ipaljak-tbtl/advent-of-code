{-# LANGUAGE NamedFieldPuns #-}

import Text.Read
import Data.Char
import Data.List (sort, sortBy, group)
import Numeric (readHex)
import Data.Ord

---------------- Models ----------------

data Hand = Hand {
    cards        :: String,
    power        :: Int, -- power of card combination
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
card_to_hex 'J' = '1'
card_to_hex 'T' = 'A'
card_to_hex  x  =  x 

calc_power :: String -> Int 
calc_power ['J','J','J','J','J']                   = 6
calc_power cards 
    | any (== 5) updated_g                         = 6 
    | any (== 4) updated_g                         = 5 
    | any (== 3) updated_g && any (== 2) updated_g = 4 
    | any (== 3) updated_g                         = 3 
    | length (filter (==2) updated_g) == 2         = 2 
    | any (== 2) updated_g                         = 1 
    | otherwise                                    = 0 
        where
            num_of_js = length $ filter (=='J') cards
            grouped   = sort $ map length $ group $ sort $ filter (/='J') cards  
            updated_g = init grouped ++ [last grouped + num_of_js]

----------------- Solve ----------------

solve :: [Hand] -> Integer
solve = sum . map (\(index, value) -> index * value) . zip [1..] . map value . sort 
        
------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

