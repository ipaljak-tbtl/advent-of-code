{-# LANGUAGE NamedFieldPuns #-}

import Data.Maybe
import Data.Map (Map)
import Data.Set (Set)
import qualified Data.Map as Mapp
import qualified Data.Set as Sett 

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
        possible_moves = (Mapp.fromList . map parse_line . drop 2) input_lines 

parse_line :: String -> (String, (String, String))
parse_line line = (tokens !! 0, (init $ tail $ tokens !! 2, init $ tokens !! 3))
    where   
        tokens = words line

----------------- Solve ----------------

solve :: Game -> Int
solve game = foldl lcm 1 cycles_sizes
    where   
        starting_nodes = (filter ((== 'A') . last) . Mapp.keys . possible_moves) game -- find starting nodes 
        last_nodes     = map (find_z     game (Sett.fromList [])) starting_nodes      -- use last nodes as they are of our interest
        cycles_sizes   = map (cycle_size game (Sett.fromList [])) last_nodes          -- find size of cycles
        
find_z :: Game -> Set (String, String) -> String -> String
find_z game@Game { user_moves = user_moves@(step:steps) } visited current  
    | last current == 'Z' = current
    | otherwise           = find_z game { user_moves = steps ++ [step] } (Sett.insert (current, user_moves) visited) (make_move game current)

cycle_size :: Game -> Set (String, String) -> String -> Int
cycle_size game@Game { user_moves = user_moves@(step:steps) } visited current  
    | Sett.member (current, user_moves) visited = 0
    | otherwise                                 = 1 + cycle_size game { user_moves = steps ++ [step] } (Sett.insert (current, user_moves) visited) (make_move game current)

make_move :: Game -> String -> String
make_move Game { user_moves = (step:_), possible_moves } state = new_state
    where
        (left_step, right_step) = fromJust $ Mapp.lookup state possible_moves 
        new_state               = if step == 'L' then left_step else right_step

------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

