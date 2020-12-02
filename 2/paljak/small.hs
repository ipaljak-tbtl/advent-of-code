import Data.List.Split

parse :: String -> (Int, Int, Char, String)
parse s = (lo, hi, c, pass)
  where
    tokens = words s
    pass = last tokens
    c = head $ tokens !! 1
    [lo, hi] = map (read::String->Int) . splitOn "-" $ head tokens

check :: (Int, Int, Char, String) -> Int
check (lo, hi, c, pass) = fromEnum $ lo <= cnt && cnt <= hi
  where
    cnt = length $ filter (== c) pass

main :: IO()
main = getContents >>= print . sum . map (check . parse) . lines
