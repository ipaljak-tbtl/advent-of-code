{-# LANGUAGE NamedFieldPuns #-}

import Text.Read
import Data.Char
import Data.List (sort, sortBy, group)
import Numeric (readHex)
import Data.Ord
import Data.Maybe
import Data.Map (fromList, Map)
import qualified Data.Map as Mapp



---------------- Parsing ---------------

parse :: String -> [(String, Maybe Int)]
parse []         = [] 
parse (',':rest) = parse rest
parse input      
    | '=' `elem` current = (takeWhile (/= '=') current, Just value ) : parse (dropWhile (/=',') input)
    | otherwise          = (takeWhile (/= '-') current, Nothing    ) : parse (dropWhile (/=',') input)
        where
            current = (takeWhile (/=',') input)
            value = (read (tail $ dropWhile (/= '=') current) :: Int)

----------------- Solve ----------------

solve :: [(String, Maybe Int)] -> Int
solve = sum . map calc . Mapp.elems . foldl update (fromList [])

calc :: [(String, Int)] -> Int
calc = sum . map (\(i, (key, value)) -> i * (1 + hash 0 key) * value) . zip [1..] 

update :: Map (Int) [(String, Int)] -> (String, Maybe Int) -> Map (Int) [(String, Int)]
update boxes entry@(key, value) 
    | isJust value && Mapp.member hashed boxes && contains key boxes = replace key (fromJust value) boxes
    | isJust value                                                   = Mapp.insert hashed (array ++ [(key, fromJust value)]) boxes
    | otherwise                                                      = Mapp.insert hashed (filter ((/=key) . fst) array)     boxes
        where
            hashed = hash 0 key
            array = fromMaybe [] (Mapp.lookup hashed boxes)

replace :: String -> Int -> Map Int [(String, Int)] -> Map Int [(String, Int)] 
replace key value boxes = Mapp.insert hashed replaced boxes
    where
        hashed   = (hash 0 key)
        array    = fromJust (Mapp.lookup hashed boxes)
        replaced = map (\(k, v) -> if k == key then (key, value) else (k, v)) array

contains :: String -> Map Int [(String, Int)] -> Bool
contains key = any ((==key) . fst) . fromJust . Mapp.lookup (hash 0 key)

hash :: Int -> String -> Int
hash acc []       = acc
hash acc (c:rest) = hash ((acc + ord c) * 17 `mod` 256 ) rest 
        
------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse $ init input -- remove endline with init
    putStrLn $ show solution

