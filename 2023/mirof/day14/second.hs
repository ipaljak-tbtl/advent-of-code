{-# LANGUAGE NamedFieldPuns #-}

import Debug.Trace
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
-- find first element
-- find period
-- calculate: val = 1000000000 - index_of_first_repeated_element `mod` period
-- index_of_first_repeated_element + val is index of solution
-- print solution :)
solve grid@Grid { fields, row_size, col_size } = error $ show res
    where
        indexes   = [ (x, y) | x <- [0..row_size], y <- [0..col_size] ]
        moves     = concat $ take 400 $ repeat [move_up indexes, move_left indexes, move_down (reverse indexes), move_right (reverse indexes)]
        ufields   = foldl (\fs@((f, _):_) move -> (move f, sum $ values $ move f) : fs) [(fields, 1)] moves
        values x  = map (\((x, y), value) -> if value == 'O' then (row_size - x) else 0) $ Mapp.assocs x
        powers    = zip [1..] $ reverse $ leave_every_forth $ map snd ufields
        dup_index = find_first_dup powers
        period    = take 2 $ filter (\(i, v) -> v == (snd $ powers !! (dup_index - 1))) powers
        res       = powers !! (122 + 20 - 1)

find_first_dup :: [(Int, Int)] -> Int
find_first_dup ((i, v):rest)
    | elem v $ map snd rest = i
    | otherwise  = find_first_dup rest

leave_every_forth :: [Int] -> [Int]
leave_every_forth (a:_:_:_:rest) = a : leave_every_forth rest
leave_every_forth _ = [] 

move_up :: [(Int, Int)] -> Map (Int, Int) Char -> Map (Int, Int) Char
move_up []                   fields = fields
move_up (coord@(x,y):coords) fields 
    | Mapp.lookup (x - 1, y) fields == Just '.' && Mapp.lookup coord fields == Just 'O' = move_up ((x - 1, y):coords) ufields 
    | otherwise = move_up coords fields 
    where
        ufields = Mapp.insert (x - 1, y) 'O' (Mapp.insert coord '.' fields)

move_down :: [(Int, Int)] -> Map (Int, Int) Char -> Map (Int, Int) Char
move_down []                   fields = fields
move_down (coord@(x,y):coords) fields 
    | Mapp.lookup (x + 1, y) fields == Just '.' && Mapp.lookup coord fields == Just 'O' = move_down ((x + 1, y):coords) ufields 
    | otherwise = move_down coords fields 
    where
        ufields = Mapp.insert (x + 1, y) 'O' (Mapp.insert coord '.' fields)

move_left :: [(Int, Int)] -> Map (Int, Int) Char -> Map (Int, Int) Char
move_left []                   fields = fields
move_left (coord@(x,y):coords) fields 
    | Mapp.lookup (x, y - 1) fields == Just '.' && Mapp.lookup coord fields == Just 'O' = move_left ((x, y - 1):coords) ufields 
    | otherwise = move_left coords fields 
    where
        ufields = Mapp.insert (x, y - 1) 'O' (Mapp.insert coord '.' fields)

move_right :: [(Int, Int)] -> Map (Int, Int) Char -> Map (Int, Int) Char
move_right []                   fields = fields
move_right (coord@(x,y):coords) fields 
    | Mapp.lookup (x, y + 1) fields == Just '.' && Mapp.lookup coord fields == Just 'O' = move_right ((x, y + 1):coords) ufields 
    | otherwise = move_right coords fields 
    where
        ufields = Mapp.insert (x, y + 1) 'O' (Mapp.insert coord '.' fields)

------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

