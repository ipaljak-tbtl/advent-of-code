import Data.List

dr = [-1, -1, -1, 0, 1, 1, 1, 0]
ds = [-1, 0, 1, 1, 1, 0, -1, -1]

accessible :: [String] -> (Int, Int) -> Bool
accessible grid (r, s) = isRoll (r, s) && cntNeigh < 4
  where
    cntNeigh = length $ filter (isRoll) [(r + r', s + s') | (r', s') <- zip dr ds]
    isRoll (r', s') = r' >= 0 && r' < length grid &&
                      s' >= 0 && s' < length (head grid) &&
                      grid !! r' !! s' == '@'

cntRolls :: [String] -> Int
cntRolls grid = length $ filter (accessible grid) indices
  where
    indices = [(i - 1, j - 1) | i <- [1..length grid], j <- [1..length $ head grid]]

main :: IO ()
main = getContents >>= print . cntRolls . lines
