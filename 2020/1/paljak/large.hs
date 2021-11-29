import qualified Data.Set as Set

solve :: [Int] -> Int
solve l = head [x * y * z | (i, x) <- l', (j, y) <- l', (k, z) <- l',
                            x + y + z == 2020 && unique [i, j, k] == 3]
  where
    l' = zip[0..] l
    unique = length . Set.fromList

main :: IO()
main = getContents >>= print . solve . map (read::String->Int) . lines
