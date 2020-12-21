import Data.List

pattern = ["..................#.",
           "#....##....##....###",
           ".#..#..#..#..#..#..."]

cntPattern :: [String] -> Int
cntPattern grid = sum [fromEnum $ check r s | r <- [0..93], s <- [0..76]]
  where
    check i j = and [checkChar (grid !! (i + i') !! (j + j')) $ pattern !! i' !! j' | i' <- [0..2],
                                                                                      j' <- [0..19]]
    checkChar '#' '#' = True
    checkChar  _  '#' = False
    checkChar  _   _  = True

solve :: [String] -> Int
solve grid = cntHash - 15 * (cntPattern grid)
  where cntHash = sum $ map (sum . map (\c -> fromEnum $ c == '#')) grid

main :: IO ()
main = getContents >>= print . solve . lines
