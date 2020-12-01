solve :: [Int] -> Int
solve l = head [x * y | (i, x) <- l', (j, y) <- l', x + y == 2020 && i /= j]
  where
    l' = zip[0..] l

main :: IO()
main = getContents >>= print . solve . map (read::String->Int) . lines
