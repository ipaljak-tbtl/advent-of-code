{-# LANGUAGE NamedFieldPuns #-}

import Data.Char
import qualified Data.Map as Mapp
import qualified Data.Set as Sett
import Debug.Trace

----------------- Solve ----------------

data Direction = N | U | R | D | L deriving (Show, Eq)

data Dfs a = Dfs {
    dir :: Direction,
    consecutive_dir :: Int,
    current_state :: a,
    current_heat :: Int,
    states :: Mapp.Map a Int,
    final_state :: a,
    visited_states :: Sett.Set a
} deriving (Show)

listWithIndexes :: [[Int]] -> Mapp.Map (Int, Int) Int
listWithIndexes xs = Mapp.fromList [((i, j), val) | (i, row) <- zip [0..] xs, (j, val) <- zip [0..] row]

solve :: [[(Int)]] -> Maybe Int
solve grid = solve' inital_state
    where
        inital_state = Dfs N 0 (0, 0) 0 (listWithIndexes grid) (length grid - 1, length grid - 1) (Sett.fromList [])

solve' :: Dfs (Int, Int) -> Maybe Int
solve' dfs@Dfs { current_state, consecutive_dir, states, current_heat, final_state, visited_states }
    | current_state == final_state                                    = Just (current_heat + (states Mapp.! current_state) - (states Mapp.! (0, 0)))
    | current_state `elem` visited_states                             = Just 100000000000000
    | current_state `Mapp.member` states && consecutive_dir <= 3      = min (solve' dfsU) $ min (solve' dfsD) $ min (solve' dfsL) (solve' dfsR)
    | otherwise                                                       = Just 100000000000000
    where
        trace = traceShowId current_state
        dfsU = step dfs U
        dfsR = step dfs R
        dfsD = step dfs D
        dfsL = step dfs L

step :: Dfs (Int, Int) -> Direction -> Dfs (Int, Int)
-- first state, when there is still no direction
step dfs@Dfs { dir = N } d = dfs { dir = d }
-- following states, when we are moving through the map
step dfs@Dfs { visited_states, current_heat, states, current_state, consecutive_dir, dir } d = dfs { visited_states = (current_state `Sett.insert` visited_states), current_heat = current_heat + states Mapp.! current_state, current_state = (coordinate_update current_state dir), dir = d, consecutive_dir = if d == dir then consecutive_dir + 1 else 0 }

coordinate_update :: (Int, Int) -> Direction -> (Int, Int)
coordinate_update coord  N = coord
coordinate_update (x, y) U = (x - 1, y    )
coordinate_update (x, y) R = (x    , y + 1)
coordinate_update (x, y) D = (x + 1, y    )
coordinate_update (x, y) L = (x    , y - 1)

------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ map (map (digitToInt)) $ lines input
    putStrLn $ show solution
