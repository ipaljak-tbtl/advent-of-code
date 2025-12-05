import Data.List.Split
import Data.List (sortOn)

type Interval = (Int, Int)

unionSize :: [Interval] -> Int
unionSize = sum . map intervalSize . mergeIntervals . sortOn fst
  where
    intervalSize (l, r) = r - l + 1

mergeIntervals :: [Interval] -> [Interval]
mergeIntervals []     = []
mergeIntervals (x:xs) = reverse (foldl step [x] xs)
  where
    step [] i = [i]
    step acc@((l1, r1) : rest) (l2, r2)
      | l2 > r1 + 1 = (l2, r2) : acc
      | otherwise   = (l1, max r1 r2) : rest

parseRanges :: [String] -> [Interval]
parseRanges = map (toTuple . map (read :: String -> Int) . splitOn "-")
  where
    toTuple [l, r] = (l, r)

freshCnt :: [[String]] -> Int
freshCnt (ranges:_) = unionSize $ parseRanges ranges

main :: IO ()
main = getContents >>= print . freshCnt . splitOn [""] . lines
