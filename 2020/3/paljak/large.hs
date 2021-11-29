slopes = [(1, 1), (1, 3), (1, 5), (1, 7), (2, 1)]

checkTree :: (Int, Int) -> [String] -> Int
checkTree (r, s) grid = fromEnum $ (grid !! r !! s') == '#'
  where s' = s `mod` (length $ head grid)

trees :: [String] -> (Int, Int) -> (Int, Int) -> Int
trees grid (r, s) (dr, ds)
  | r >= length grid = 0
  | otherwise        = (checkTree (r, s) grid) + trees grid (r + dr, s + ds) (dr, ds)

checkSlopes :: [String] -> Int
checkSlopes grid = foldl1 (*) $ map (trees grid (0, 0)) slopes

main :: IO()
main = getContents >>= print . checkSlopes . lines
