import Data.List
import Data.List.Split

import Debug.Trace

data Tile = Tile Int [String] deriving (Eq, Show)

n = 12

remove :: (Eq a) => a -> [a] -> [a]
remove x = filter (/= x)

removeTile :: Tile -> [Tile] -> [Tile]
removeTile (Tile id _) = filter (\(Tile id' _) -> id /= id')

parseLines :: [String] -> [Tile]
parseLines = map (parseTile) . splitOn [""]
  where
    parseTile ls = Tile (read . drop 5 . init $ head ls) $ tail ls

rotL :: Tile -> Tile
rotL (Tile id grid) = Tile id $ reverse $ transpose grid

flipY :: Tile -> Tile
flipY (Tile id grid) = Tile id $ reverse grid

flipX :: Tile -> Tile
flipX (Tile id grid) = Tile id $ map (reverse) grid

ways :: Tile -> [Tile]
ways tile =
  map (\f -> f tile) [rotL, rotL . rotL, rotL . rotL . rotL,
                      rotL . flipY, rotL . rotL . flipY, rotL . rotL . rotL . flipY,
                      rotL . flipX, rotL . rotL . flipX, rotL . rotL . rotL . flipX,
                      rotL . flipX . flipY, rotL . rotL . flipX . flipY, rotL . rotL . rotL . flipX . flipY]

fitD :: Tile -> Tile -> Bool
fitD (Tile _ a) (Tile _ b) = (last a) == (head b)

fitR :: Tile -> Tile -> Bool
fitR (Tile _ a) (Tile _ b) = all (\(x, y) -> (last x) == (head y)) $ zip a b

corners :: [Tile] -> [Tile]
corners tiles = filter (f) $ concatMap (ways) tiles
  where
    f t = (filter (\x -> fitD t x || fitR t x) . concatMap (ways) $ removeTile t tiles) == []

solve :: [Tile] -> [Tile] -> [Tile]
solve puzzle [] = puzzle
solve puzzle tiles
  | remove [] rekMatched == [] = []
  | otherwise                  = head $ remove [] rekMatched
  where
    r = (length puzzle) `div` n
    s = (length puzzle) `mod` n
    getTile i j = puzzle !! (i * n + j)
    match tile  = (r == 0 || fitD (getTile (r - 1) s) tile) &&
                  (s == 0 || fitR (getTile r (s - 1)) tile)
    rekMatched  = map (\tile -> solve (puzzle ++ [tile]) $ removeTile tile tiles) .
                  filter (match) $ concatMap (ways) tiles

main :: IO ()
main = getContents >>= print . solve [] . parseLines . lines
