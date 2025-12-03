import Data.Char
import Data.List

joltage :: String -> Int
joltage = maximum . map (\(x:xs) -> x * 10 + maximum xs) . init . init . tails . map (digitToInt)

main :: IO ()
main = getContents >>= print . sum . map (joltage) . lines
