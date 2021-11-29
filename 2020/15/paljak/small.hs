import Data.List
import Data.List.Split

import qualified Data.Map as Map

data State = State (Map.Map Int Int) Int deriving Show

getState :: [Int] -> State
getState xs = State (history xs) (last xs)
  where
    history xs      = foldl' (insert) Map.empty $ zip (init xs) [1..]
    insert m (k, v) = Map.insert k v m

findNum :: Int -> State -> Int
findNum 2020 (State _ last) = last
findNum n    (State m last)
  | last `Map.notMember` m = findNum (n + 1) (State m' 0)
  | otherwise              = findNum (n + 1) (State m' (n - m Map.! last))
    where m' = Map.insert last n m

main :: IO ()
main =
  getContents >>= print . findNum 6 . getState .
                  map (read::String->Int) . splitOn "," . head . lines
