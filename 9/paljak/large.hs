import Data.List
import Data.Maybe

target = 1038347917

findInterval :: [Int] -> (Int, Int)
findInterval xs =
  head [(i - 1, j - 1) | (i, pi) <- pref, (j, pj) <- pref, pj - pi == target, j - i > 1]
    where
      pref = scanl1 (\(_, p) (i, xi) -> (i, p + xi)) $ zip [0..] ([0] ++ xs)

solve :: [Int] -> Int
solve xs = extremeSum interval
  where
    (lo, hi)     = findInterval xs
    interval     = drop lo $ take hi xs
    extremeSum l = (maximum l) + (minimum l)

main :: IO ()
main = getContents >>= print . solve  . map (read::String->Int) . lines
