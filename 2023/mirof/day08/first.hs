{-# LANGUAGE NamedFieldPuns #-}

import Text.Read
import Data.Char
import Data.List (sort, sortBy, group)
import Numeric (readHex)
import Data.Ord
import Data.Maybe
import Data.Map (fromList, Map)
import qualified Data.Map as Mapp

---------------- Models ----------------

data Game = Game {
    user_moves     :: String,
    possible_moves :: Map String (String, String)
} deriving (Show)

---------------- Parsing ---------------

parse :: String -> Game 
parse input = Game {
    user_moves,
    possible_moves 
}
    where   
        input_lines    = lines input
        user_moves     = head input_lines
        possible_moves = (fromList . map parse_line . drop 2) input_lines 

parse_line :: String -> (String, (String, String))
parse_line line = (tokens !! 0, (init $ tail $ tokens !! 2, init $ tokens !! 3))
    where   
        tokens = words line
        

----------------- Solve ----------------

solve :: Game -> Int
solve game = play "AAA" (concat $ repeat $ user_moves game) game

play :: String -> String -> Game -> Int
play "ZZZ"   _            _  = 0
play current (step:steps) game  
    | step == 'L'            = 1 + play left_step  steps game
    | step == 'R'            = 1 + play right_step steps game
        where
            (left_step, right_step) = fromJust $ Mapp.lookup current (possible_moves game)
            
        
------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

