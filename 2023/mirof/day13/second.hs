{-# LANGUAGE NamedFieldPuns #-}

import Debug.Trace
import Text.Read
import Data.Char
import Data.List (sort, sortBy, group, findIndex, transpose)
import Numeric (readHex)
import Data.Ord
import Data.Maybe
import Data.Map (fromList, Map)
import qualified Data.Map as Mapp

---------------- Models ----------------

data Grid = Grid {
    fields :: [[Char]]
} deriving (Show)

---------------- Parsing ---------------

parse :: String -> [Grid] 
parse input = parse_grids input_lines
    where
        input_lines = lines input
        
parse_grids :: [String] -> [Grid]
parse_grids []           = []
parse_grids ([]:rest)    = parse_grids rest
parse_grids input        = Grid { fields = takeWhile (/= []) input } : (parse_grids (dropWhile (/= []) input))

----------------- Solve ----------------

-- solution between 32235 is too low
solve :: [Grid] -> Int
solve grids = sum $ zipWith max cols_reverse $ zipWith max cols $ zipWith max rows rows_reverse
    where
        rows         = (map (*100) . map (solve_grid)      .               map (zip [0..])                 . map fields) grids
        rows_reverse = (map (*100) . map (solve_grid_rev ) . map reverse . map (zip [0..])                 . map fields) grids
        cols         = (             map (solve_grid)      .               map (zip [0..]) . map transpose . map fields) grids
        cols_reverse = (             map (solve_grid_rev ) . map reverse . map (zip [0..]) . map transpose . map fields) grids

solve_grid :: [(Int, [Char])] -> Int -- return index where mirror edge is found
solve_grid [] = -1 
solve_grid grid 
    | (length grid) `mod` 2 /= 0 = solve_grid $ tail grid
    | matches grid               = (fst $ head grid) + (length grid `div` 2)
    | otherwise                  = solve_grid $ tail grid

solve_grid_rev :: [(Int, [Char])] -> Int -- return index where mirror edge is found
solve_grid_rev [] = -1
solve_grid_rev grid 
    | (length grid) `mod` 2 /= 0 = solve_grid_rev $ tail grid
    | matches grid               = ceiling $ (fromIntegral $ fst $ head grid) / 2.0
    | otherwise                  = solve_grid_rev $ tail grid

matches :: [(Int, [Char])] -> Bool
matches grid = matches' grid False

matches' :: [(Int, [Char])] -> Bool -> Bool
matches' []           bool = bool 
matches' (line:rgrid) bool
    | (snd line) == (snd $ last rgrid)                          = matches' (init rgrid) bool
    | bool == False && off_by_one (snd line) (snd $ last rgrid) = matches' (init rgrid) True
    | otherwise                                                 = False

off_by_one :: Eq a => [a] -> [a] -> Bool
off_by_one l1 l2 = off_by_one' l1 l2 False

off_by_one' :: Eq a => [a] -> [a] -> Bool -> Bool
off_by_one' []      []      bool = bool
off_by_one' (e1:l1) (e2:l2) bool
    | e1 == e2 = off_by_one' l1 l2 bool
    | e1 /= e2 && bool == False = off_by_one' l1 l2 True 
    | e1 /= e2 && bool          = False
        
------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

