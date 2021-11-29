import Data.List

import qualified Data.Map as Map

data Direction = E | SE | SW | W | NW | NE deriving Show

parseLines :: [String] -> [[Direction]]
parseLines = map (parseLine)
  where
    parseLine s
      | s == ""             = []
      | "e"  `isPrefixOf` s = E  : (parseLine $ tail s)
      | "se" `isPrefixOf` s = SE : (parseLine $ drop 2 s)
      | "sw" `isPrefixOf` s = SW : (parseLine $ drop 2 s)
      | "w"  `isPrefixOf` s = W  : (parseLine $ tail s)
      | "nw" `isPrefixOf` s = NW : (parseLine $ drop 2 s)
      | "ne" `isPrefixOf` s = NE : (parseLine $ drop 2 s)

getTile :: [Direction] -> (Int, Int)
getTile = foldl' (move) (0, 0)
  where
    move (x, y) E  = (x + 1, y)
    move (x, y) SE = (x + 1, y - 1)
    move (x, y) SW = (x, y - 1)
    move (x, y) W  = (x - 1, y)
    move (x, y) NW = (x - 1, y + 1)
    move (x, y) NE = (x, y + 1)

solve :: [[Direction]] -> Int
solve dirs = sum $ Map.elems flip
  where
    tiles = map (getTile) dirs
    flip  = foldl' (updateMap) Map.empty tiles
    updateMap m t@(x, y)
      | t `Map.member` m = Map.insert t (1 - (m Map.! t)) m
      | otherwise        = Map.insert t 1 m

main :: IO ()
main = getContents >>= print . solve . parseLines . lines
