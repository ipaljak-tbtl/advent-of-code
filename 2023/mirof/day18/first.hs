{-# LANGUAGE NamedFieldPuns #-}

import Text.Read
import Data.Char
import Data.List (sort, sortBy, group)
import Numeric (readHex)
import Data.Ord
import Data.Maybe
import Data.Set (fromList, Set)
import qualified Data.Map as Mapp
import qualified Data.Set as Sett 

---------------- Parsing ---------------

parse :: String -> [(Char, Int, String)] 
parse = map (parse_line . words) . lines 

parse_line :: [String] -> (Char, Int, String)
parse_line tokens = (tokens !! 0 !! 0, read (tokens !! 1) :: Int, tokens !! 2)

----------------- Solve ----------------

solve :: [(Char, Int, String)] -> Int
solve input = Sett.size digged
    where
        edge = create_map input (0, 0) (fromList [])
        smallest_x = minimum $ map fst $ Sett.elems edge
        smallest_y = minimum $ map snd $ Sett.elems edge
        largest_x  = maximum $ map fst $ Sett.elems edge
        largest_y  = maximum $ map snd $ Sett.elems edge
        digged     = dig edge [ (x, y) | x <- [smallest_x-1..largest_x+1], y <- [smallest_y-1..largest_y+1] ] False (fromList [])     

dig :: Set (Int, Int) -> [(Int, Int)] -> Bool -> Set (Int, Int) -> Set (Int, Int)
dig edge []             False     digged = Sett.union edge digged
dig edge (coord@(x, y):coords) is_inside digged 
    | not is_inside && (not $ Sett.member coord edge) = dig edge coords       is_inside   digged 
    | is_inside     && (not $ Sett.member coord edge) = dig edge coords       is_inside   (Sett.insert coord digged)

    | not is_inside && (Sett.member coord edge)       = dig edge removed_edge uois_inside digged 
    |     is_inside && (Sett.member coord edge)       = dig edge removed_edge uois_inside digged 

    | otherwise = error "Unreachable state"
    where
        removed_edge@((nx, ny):_) = dropWhile (\c -> Sett.member c edge) coords
        uois_inside = 
            if removed_edge /= coords && 
               ((Sett.member (x+1, y) edge && Sett.member (nx + 1, ny - 1) edge) || 
                (Sett.member (x-1, y) edge && Sett.member (nx - 1, ny - 1) edge)) 
            then is_inside 
            else not is_inside

create_map :: [(Char, Int, String)] -> (Int, Int) -> Set (Int, Int) -> Set (Int, Int)
create_map []                                   _      grid = grid  
create_map ((direction, num_of_steps, _):steps) (x, y) grid  
    | direction == 'R' =  create_map steps (x, y + num_of_steps) (Sett.union grid $ fromList $ zip (repeat x) ([y..y+num_of_steps])) 
    | direction == 'L' =  create_map steps (x, y - num_of_steps) (Sett.union grid $ fromList $ zip (repeat x) ([y-num_of_steps..y]))
    | direction == 'D' =  create_map steps (x + num_of_steps, y) (Sett.union grid $ fromList $ zip ([x..x+num_of_steps]) (repeat y) )
    | direction == 'U' =  create_map steps (x - num_of_steps, y) (Sett.union grid $ fromList $ zip ([x-num_of_steps..x]) (repeat y) )
        
------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

