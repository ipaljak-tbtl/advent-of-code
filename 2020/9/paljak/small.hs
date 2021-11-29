import Data.List
import Data.Maybe

windows :: Int -> [Int] -> [[Int]]
windows n l@(x:xs)
  | length w < n = []
  | otherwise    = w : windows n xs
  where
    w = take n l

isCorrupt :: [Int] -> Bool
isCorrupt l = last l `notElem` (sums $ init l)
  where
    sums xs = [a + b | a <- xs, b <- xs, a /= b]

solve :: [Int] -> Int
solve xs = last . fromJust . find (isCorrupt) $ windows 26 xs

main :: IO ()
main = getContents >>= print . solve . map (read::String->Int) . lines
