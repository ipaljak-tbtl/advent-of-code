checkTree :: (Int, Int) -> [String] -> Int
checkTree (r, s) grid = fromEnum $ (grid !! r !! s') == '#'
  where s' = s `mod` (length $ head grid)

trees :: (Int, Int) -> (Int, Int) -> [String] -> Int
trees (r, s) (dr, ds) grid
  | r >= length grid = 0
  | otherwise        = (checkTree (r, s) grid) + trees (r + dr, s + ds) (dr, ds) grid

main :: IO()
main = getContents >>= print . trees (0, 0) (1, 3) . lines
