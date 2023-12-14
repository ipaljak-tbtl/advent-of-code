{-# LANGUAGE NamedFieldPuns #-}

import Data.List (find, transpose, maximum)
import Data.Map (Map, fromList, lookup)
import Data.Maybe (fromJust, isJust, isNothing)
import Data.Set (Set)
import Text.Read
import qualified Data.Map as Mapp
import qualified Data.Set as Sett

---------------- Models ----------------

data Grid = Grid {
    fields   :: Map (Int, Int) Char,
    row_size :: Int,
    col_size :: Int
} 

instance Show Grid where
    show Grid { fields, row_size, col_size } = foldl (++) "" $ map (\coord@(_, j) -> if j == 0 then "\n" ++ (show $ fromJust $ Mapp.lookup coord fields) else show $ fromJust $ Mapp.lookup coord fields) [ (x, y) | x <- [0..row_size-1], y <- [0..col_size-1] ] 

---------------- Parsing ---------------

parse :: String -> Grid
parse input = Grid { 
    fields = fromList matrix,
    row_size = length (input_lines !! 0),
    col_size = length input_lines

}
    where
        input_lines       = lines input
        with_column_num   = map (zip [0..]) input_lines
        with_matrix_index = transpose $ map (zip [0..]) $ transpose with_column_num
        matrix            = concat $ map (map (\(i, (j, value)) -> ((i, j), value))) with_matrix_index

----------------- Solve ----------------

solve :: Grid -> Int
solve grid@Grid { fields, row_size, col_size } = sum values
    where
        ufields =  move_up fields [ (x, y) | x <- [0..row_size], y <- [0..col_size] ]
        values  = map (\((x, y), value) -> if value == 'O' then (row_size - x) else 0) $ Mapp.assocs ufields

move_up :: Map (Int, Int) Char -> [(Int, Int)] -> Map (Int, Int) Char
move_up fields []                   = fields
move_up fields (coord@(x,y):coords) 
    | Mapp.lookup (x - 1, y) fields == Just '.' && Mapp.lookup coord fields == Just 'O' = move_up ufields ((x - 1, y):coords)
    | otherwise = move_up fields coords
    where
        ufields = Mapp.insert (x - 1, y) 'O' (Mapp.insert coord '.' fields)

------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

