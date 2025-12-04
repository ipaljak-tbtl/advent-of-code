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

getRolls :: [String] -> [(Int, Int)]
getRolls grid = filter (accessible grid) indices
  where
    indices = [(i - 1, j - 1) | i <- [1..length grid], j <- [1..length $ head grid]]

removeRolls :: [String] -> [(Int, Int)] -> [String]
removeRolls grid coords =
  [[if (r, c) `elem` coords then '.' else ch | (c, ch) <- zip [0..] row] | (r, row) <- zip [0..] grid]

cntRolls :: [String] -> Int
cntRolls grid
  | length rolls == 0 = 0
  | otherwise         = length rolls + cntRolls (removeRolls grid rolls)
    where rolls = getRolls grid

main :: IO ()
main = getContents >>= print . cntRolls . lines
