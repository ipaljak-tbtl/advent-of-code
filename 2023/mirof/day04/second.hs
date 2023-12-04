{-# LANGUAGE NamedFieldPuns #-}

import Text.Read
import Data.Char
import Data.List (intersect)

---------------- Models ----------------

data Game = Game {
    iden            ::  Integer ,
    winning_numbers :: [Integer],
    player_numbers  :: [Integer]
} deriving (Eq, Show)

---------------- Parsing ---------------

parse :: String -> [Game]
parse = map parse_line . lines

parse_line :: String -> Game
parse_line line = Game { iden, winning_numbers, player_numbers }
    where  
        tokens          = (drop 2 . words) line
        iden            = read $ init $ (head . tail) tokens :: Integer
        winning_numbers = map (\num -> read num :: Integer) $        takeWhile (/= "|") tokens 
        player_numbers  = map (\num -> read num :: Integer) $ tail $ dropWhile (/= "|") tokens  -- drop '|' from numbers

----------------- Solve ----------------

solve :: [Game] -> Int
solve = count_scratches . zip [1,1..] . map num_of_won_scrathes -- zip with starting number of cards

num_of_won_scrathes :: Game -> Int
num_of_won_scrathes game = (length $ intersect (winning_numbers game) (player_numbers game))

count_scratches :: [(Int, Int)] -> Int
count_scratches []                         = 0
count_scratches ((current, won):remaining) = current + count_scratches (iterate (add_won won) remaining !! current) -- iterate will do task `current` times and return result

add_won :: Int -> [(Int, Int)] -> [(Int, Int)]
add_won 0    scratches                  = scratches 
add_won left ((current, won):scratches) = (current + 1, won) : add_won (left - 1) scratches

------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

