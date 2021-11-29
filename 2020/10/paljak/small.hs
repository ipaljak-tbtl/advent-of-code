import Data.Sort

count :: Int -> [Int] -> Int
count x = length . filter (==x)

solve :: [Int] -> Int
solve l = (count 1 diffs) * (count 3 diffs)
  where
    sorted = reverse $ sort (l ++ [0] ++ [(maximum l) + 3])
    diffs  = zipWith (-) sorted (tail sorted)

main :: IO ()
main = getContents >>= print . solve . map (read::String->Int) . lines
