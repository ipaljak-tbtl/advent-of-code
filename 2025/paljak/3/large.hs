import Data.Char
import Data.List

joltage :: String -> Int
joltage = (!! 12) . foldr dpStep (replicate 13 0) . map digitToInt
  where
    dpStep x memo =
      0 : zipWith (\skip take -> max skip (prepend x take)) (tail memo) memo
      where
        prepend d 0 = d
        prepend d n = d * 10 ^ length (show n) + n

main :: IO ()
main = getContents >>= print . sum . map (joltage) . lines
