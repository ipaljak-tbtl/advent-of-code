{-# LANGUAGE NamedFieldPuns #-}

import Text.Read
import Data.Char
import Data.List (intersect)

---------------- Models ----------------

data Game = Game {
    winning_numbers :: [Integer],
    player_numbers  :: [Integer]
} deriving (Eq, Show)

---------------- Parsing ---------------

parse :: String -> [Game]
parse = map parse_line . lines

parse_line :: String -> Game
parse_line line = Game { winning_numbers, player_numbers }
    where  
        tokens          = (drop 2 . words) line
        winning_numbers = map (\num -> read num :: Integer) $        takeWhile (/= "|") tokens 
        player_numbers  = map (\num -> read num :: Integer) $ tail $ dropWhile (/= "|") tokens  -- drop '|' from numbers

----------------- Solve ----------------

solve :: [Game] -> Int
solve = sum . map pow_winner_nums

pow_winner_nums :: Game -> Int
pow_winner_nums game = if power == 0 then 0 else 2 ^ (power - 1)
    where   
        power = (length $ intersect (winning_numbers game) (player_numbers game))

------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

