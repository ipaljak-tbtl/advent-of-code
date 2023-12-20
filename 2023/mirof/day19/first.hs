{-# LANGUAGE NamedFieldPuns #-}

import Debug.Trace
import Text.Read
import Data.Char
import Data.List (sort, sortBy, group)
import Numeric (readHex)
import Data.Ord
import Data.Maybe
import Data.Map (fromList, Map)
import qualified Data.Map as Mapp

---------------- Models ----------------

data Problem = Problem {
    states :: Map String [(Int, Char, Int, String)], -- first is index of input used, second is < or >, third is next state
    inputs :: [[Int]]
} deriving (Show)

---------------- Parsing ---------------

parse :: String -> Problem 
parse input = Problem {
    states = fromList $ parse_states first_part,
    inputs = parse_inputs second_part
}
    where   
        input_lines = lines input
        first_part  =        takeWhile (/="") input_lines
        second_part = tail $ dropWhile (/="") input_lines

parse_states :: [String] -> [(String, [(Int, Char, Int, String)])]
parse_states []           = []
parse_states (line:lines) = (key, state) : parse_states lines
    where
        key = takeWhile (/='{') line 
        state = parse_state $ tail $ dropWhile (/='{') line

parse_state :: String -> [(Int, Char, Int, String)]
parse_state ('x':'>':rest) = (0, '>', read (takeWhile (/=':') rest) :: Int, takeWhile (/=',') $ tail $ (dropWhile (/=':') rest)) : (parse_state $ tail $ dropWhile (/=',') rest)
parse_state ('x':'<':rest) = (0, '<', read (takeWhile (/=':') rest) :: Int, takeWhile (/=',') $ tail $ (dropWhile (/=':') rest)) : (parse_state $ tail $ dropWhile (/=',') rest)

parse_state ('m':'>':rest) = (1, '>', read (takeWhile (/=':') rest) :: Int, takeWhile (/=',') $ tail $ (dropWhile (/=':') rest)) : (parse_state $ tail $ dropWhile (/=',') rest)
parse_state ('m':'<':rest) = (1, '<', read (takeWhile (/=':') rest) :: Int, takeWhile (/=',') $ tail $ (dropWhile (/=':') rest)) : (parse_state $ tail $ dropWhile (/=',') rest)

parse_state ('a':'>':rest) = (2, '>', read (takeWhile (/=':') rest) :: Int, takeWhile (/=',') $ tail $ (dropWhile (/=':') rest)) : (parse_state $ tail $ dropWhile (/=',') rest)
parse_state ('a':'<':rest) = (2, '<', read (takeWhile (/=':') rest) :: Int, takeWhile (/=',') $ tail $ (dropWhile (/=':') rest)) : (parse_state $ tail $ dropWhile (/=',') rest)

parse_state ('s':'>':rest) = (3, '>', read (takeWhile (/=':') rest) :: Int, takeWhile (/=',') $ tail $ (dropWhile (/=':') rest)) : (parse_state $ tail $ dropWhile (/=',') rest)
parse_state ('s':'<':rest) = (3, '<', read (takeWhile (/=':') rest) :: Int, takeWhile (/=',') $ tail $ (dropWhile (/=':') rest)) : (parse_state $ tail $ dropWhile (/=',') rest)

parse_state rest = [(4, '.', 0, init rest)]

parse_inputs :: [String] -> [[Int]]
parse_inputs []           = []
parse_inputs (line:lines) = values : (parse_inputs lines)
    where
        without_brackets = init $ tail line
        tokens           = words $ map (\x -> if x == ',' then ' ' else x) without_brackets
        values           = map (\x -> read (tail $ tail x) :: Int) tokens

----------------- Solve ----------------

solve :: Problem -> Int
solve Problem { states, inputs } = sum $ map (\input -> solve_inputs states input "in") inputs 

solve_inputs :: Map String [(Int, Char, Int, String)] -> [Int] -> String -> Int 
solve_inputs _      [x, m, a, s] "A"         = (x + m + a + s)
solve_inputs _      _            "R"         = 0
solve_inputs states current      current_key = solve_inputs states current (solve_state state current)
    where
        state = fromJust $ Mapp.lookup current_key states

solve_state :: [(Int, Char, Int, String)] -> [Int] -> String
solve_state ((index, operator, value, state):rest) xmas
    | index == 4                                 = state
    | operator == '<' && (xmas !! index) < value = state 
    | operator == '>' && (xmas !! index) > value = state 
    | otherwise                                  = solve_state rest xmas
        
------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

