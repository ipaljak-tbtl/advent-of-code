import Data.Sort
import Data.Function(fix)

import qualified Data.Vector as Vector

dp :: [Int] -> Int -> Int
dp l = dpMemo
  where
   dpMemo = (map (dp' dpMemo) [0..] !!)
   dp' memo i
    | i == (length l) - 1 = 1
    | i >= length l       = 0
    | otherwise           = sum $ map (memo) trans
      where
        li    = l !! i
        trans = filter (\j -> j < length l && (l !! j) - li <= 3) [(i + 1)..(i + 3)]

solve :: [Int] -> Int
solve l = dp sorted 0
  where
    sorted = sort (l ++ [0] ++ [(maximum l) + 3])

main :: IO ()
main = getContents >>= print . solve . map (read::String->Int) . lines
