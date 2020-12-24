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

move :: (Int, Int) -> Direction -> (Int, Int)
move (x, y) E  = (x + 1, y)
move (x, y) SE = (x + 1, y - 1)
move (x, y) SW = (x, y - 1)
move (x, y) W  = (x - 1, y)
move (x, y) NW = (x - 1, y + 1)
move (x, y) NE = (x, y + 1)

getNeigh :: (Int, Int) -> [(Int, Int)]
getNeigh t = [move t E, move t SE, move t SW,
              move t W, move t NW, move t NE]

getTile :: [Direction] -> (Int, Int)
getTile = foldl' (move) (0, 0)

keepBlack :: Map.Map a Int -> Map.Map a Int
keepBlack = Map.filter (== 1)

dayState :: Int -> Map.Map (Int, Int) Int -> Map.Map (Int, Int) Int
dayState 0 m = m
dayState n m = dayState (n - 1) m'
  where
    neigh   = concatMap (getNeigh) $ Map.keys m
    extMap  = foldl' (addW) m neigh
    addW m k
      | k `Map.member` m = m
      | otherwise        = Map.insert k 0 m
    flipped = Map.filterWithKey (mustFlip) extMap
    flipMap = foldl' (\m' k -> Map.insert k (1 - (extMap Map.! k)) m') extMap $ Map.keys flipped
    m'      = keepBlack flipMap
    mustFlip t _
      | t `Map.member` m = (blackN t) == 0 || (blackN t) > 2
      | otherwise        = (blackN t) == 2
    blackN t = length . filter (`Map.member` m) $ getNeigh t

solve :: [[Direction]] -> Int
solve dirs = length . dayState 100 $ keepBlack flip
  where
    tiles = map (getTile) dirs
    flip  = foldl' (updateMap) Map.empty tiles
    updateMap m t@(x, y)
      | t `Map.member` m = Map.insert t (1 - (m Map.! t)) m
      | otherwise        = Map.insert t 1 m

main :: IO ()
main = getContents >>= print . solve . parseLines . lines
