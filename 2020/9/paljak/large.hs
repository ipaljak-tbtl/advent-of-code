import Data.List
import Data.Maybe

target = 1038347917

findInterval :: [Int] -> [Int]
findInterval xs = drop lo $ take hi xs
  where
    (lo, hi) = head [(i - 1, j - 1) | (i, pi) <- pref,
                                      (j, pj) <- pref,
                                      pj - pi == target,
                                      j - i > 1]
    pref     = scanl1 (\(_, p) (i, xi) -> (i, p + xi)) $ zip [0..] ([0] ++ xs)

solve :: [Int] -> Int
solve = extremeSum . findInterval
  where
    extremeSum l = (maximum l) + (minimum l)

main :: IO ()
main = getContents >>= print . solve . map (read::String->Int) . lines
