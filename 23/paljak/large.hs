import Data.List
import Data.Maybe

import qualified Data.Map.Strict as Map

type MapInt = Map.Map Int Int

n = 10000000

parseLines :: String -> [Int]
parseLines = map (read . (:[]))

move :: (Int, MapInt) -> (Int, MapInt)
move (i, r) = (i', r')
  where
    taken   = [r Map.! i, r Map.! (r Map.! i), r Map.! (r Map.! (r Map.! i))]
    lo      = head taken
    hi      = last taken
    dest    = fromJust . find (`notElem` taken) $ map (\d -> 1 + add i (-d)) [2..]
    rr      = Map.insert hi (-1) $! Map.insert i (r Map.! hi) r
    r'      = Map.insert hi (rr Map.! dest) $! Map.insert dest lo rr
    i'      = rr Map.! i
    add a b = (a + b + (length r)) `mod` (length r)

solve :: [Int] -> Int
solve l = eval finSt
  where
    rMap  = Map.fromList . zip full $ tail full ++ [head full]
    full  = l ++ [10..1000000]
    finSt = foldl (\st _ -> move st) (l !! 0, rMap) [1..n]
    eval (_, r) = (r Map.! 1) * (r Map.! (r Map.! 1))


main :: IO ()
main = getContents >>= print . solve . parseLines . head . lines
