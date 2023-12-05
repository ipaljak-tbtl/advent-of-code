{-# LANGUAGE NamedFieldPuns #-}

import Text.Read
import Data.Char
import Data.List (intersect, find)
import Data.Maybe

---------------- Models ----------------

data Interval = Interval {
    from :: Integer,
    to   :: Integer
} deriving (Show)

data Mapping = Mapping {
    destination :: Interval, -- probably doesn't need to be interval at all but okay
    source      :: Interval,
    len         :: Integer
} deriving (Show)

data ItemMapping = ItemMapping {
    input    :: String,
    output   :: String,
    mappings :: [Mapping]
} deriving (Show)

data Problem = Problem {
    seeds         :: [Integer],
    item_mappings :: [ItemMapping]
} deriving (Show)

---------------- Parsing ---------------

parse :: String -> Problem 
parse input = Problem { seeds, item_mappings }
    where
        input_lines   = lines input
        seeds         = map (\seed -> read seed :: Integer) $ tail $ words $ head input_lines
        item_mappings = map parse_item_mapping $ split_by_new_line $ drop 2 input_lines -- drop seeds and empty line 

split_by_new_line :: [String] -> [[String]]
split_by_new_line []   = []
split_by_new_line list = prefix_group : split_by_new_line rest
    where
        prefix_group =                  takeWhile (/="") list
        rest         = failproof_tail $ dropWhile (/="") list -- remove newline line with tail

failproof_tail :: [a] -> [a]
failproof_tail []   = []
failproof_tail list = tail list 

parse_item_mapping :: [String] -> ItemMapping
parse_item_mapping (header:str_mappings) = ItemMapping { input, output, mappings } 
    where
        input  = header -- maybe never needed 
        output = header -- maybe never needed 
        mappings = map parse_mapping str_mappings

parse_mapping :: String -> Mapping
parse_mapping line = Mapping { destination, source, len }
    where 
        tokens = words line
        destination_num = read (tokens !! 0) :: Integer
        source_num      = read (tokens !! 1) :: Integer
        len             = read (tokens !! 2) :: Integer
        destination     = Interval { from = destination_num, to = destination_num + len - 1 }
        source          = Interval { from = source_num,      to = source_num      + len - 1 }

----------------- Solve ----------------

solve :: Problem -> Integer
solve problem = fst $ head $ filter (is_seed (seeds problem) . snd) $ zip location_values $ map (transform_location_to_seed reversed_item_mappings) location_values
    where
        reversed_item_mappings = reverse $ item_mappings problem
        location_values = [0..15880236] -- by some binary searching we came up to this value ;)

is_seed :: [Integer] -> Integer -> Bool
is_seed []               _    = False
is_seed (start:end:rest) seed 
    | seed >= start && seed <= start + end - 1 = True
    | otherwise                                = is_seed rest seed
    

transform_location_to_seed :: [ItemMapping] -> Integer -> Integer
transform_location_to_seed []                  location = location  
transform_location_to_seed (item_mapping:rest) location = transform_location_to_seed rest new_location 
    where
        found_map = find (\Mapping { destination = Interval { from, to } } -> location >= from && location <= to ) $ mappings item_mapping
        new_location = if isJust found_map then location - (from $ destination $ fromJust found_map) + (from $ source $ fromJust found_map) else location 
        
------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

