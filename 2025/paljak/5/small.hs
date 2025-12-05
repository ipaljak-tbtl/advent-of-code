import Data.List.Split

freshCnt :: [[String]] -> Int
freshCnt (ranges:ids:[]) =
  sum . map (isFresh $ parseRanges ranges) $ parseIds ids
  where
    parseIds      = map (read :: String -> Int)
    parseRanges   = map (map (read :: String -> Int) . splitOn "-")
    isFresh rs id = fromEnum . or $ map (\(l:r:[]) -> id >= l && id <= r) rs

main :: IO ()
main = getContents >>= print . freshCnt . splitOn [""] . lines
