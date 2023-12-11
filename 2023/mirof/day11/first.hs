{-# LANGUAGE NamedFieldPuns #-}

import Data.List (transpose)
import Data.Set (toList, Set)
import qualified Data.Set as Sett 

---------------- Models ----------------

data State = State {
    nodes      :: Set (Int, Int),
    empty_rows :: [Int],
    empty_cols :: [Int]
} deriving (Show)

---------------- Parsing ---------------

parse :: String -> State 
parse input = State {
    nodes,
    empty_rows,
    empty_cols
}
    where
        input_lines       = lines input
        with_column_num   = map (zip [0..]) input_lines
        with_matrix_index = transpose $ map (zip [0..]) $ transpose with_column_num

        empty_rows        = map (\(i, _)      -> i) $ map head $ filter (\row -> all (\(_, (_, x)) -> x == '.') row)             with_matrix_index
        empty_cols        = map (\(_, (j, _)) -> j) $ map head $ filter (\col -> all (\(_, (_, x)) -> x == '.') col) $ transpose with_matrix_index

        filtered          = map (filter ((== '#') . snd . snd)) with_matrix_index
        matrix            = concat $ map (map (\(i, (j, _)) -> (i, j))) filtered 
        nodes             = Sett.fromList matrix

----------------- Solve ----------------

solve :: State -> Int
solve state = sum $ map (\(c1, c2) -> distance c1 c2) $ toList pairs 
    where
        adjusted = adjusted_coords state
        elements = Sett.elems adjusted
        pairs    = Sett.fromList [(elements !! i, elements !! j) | i <- [0..(length elements - 1)], j <- [i+1..(length elements - 1)]]

distance :: (Int, Int) -> (Int, Int) -> Int
distance (x1, y1) (x2, y2) = (abs (x2 - x1)) + (abs (y2 - y1))

adjusted_coords :: State -> Set (Int, Int)
adjusted_coords state = adjusted
    where   
        adjusted_row = Sett.map (\(i, j) -> (i + adjust_row state i, j)) (nodes state) 
        adjusted     = Sett.map (\(i, j) -> (i, j + adjust_col state j)) adjusted_row

adjust_row :: State -> Int -> Int
adjust_row state current = length $ filter (< current) (empty_rows state)

adjust_col :: State -> Int -> Int
adjust_col state current = length $ filter (< current) (empty_cols state)

------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

