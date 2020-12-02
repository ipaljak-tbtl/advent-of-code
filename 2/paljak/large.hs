import Data.Bits
import Data.List.Split

parse :: String -> (Int, Int, Char, String)
parse s = (lo, hi, c, pass)
  where
    tokens = words s
    pass = last tokens
    c = head $ tokens !! 1
    [lo, hi] = map ((+) (-1) . read::String->Int) . splitOn "-" $ head tokens

check :: (Int, Int, Char, String) -> Int
check (lo, hi, c, pass) = fromEnum $ (pass !! lo == c) `xor` (pass !! hi == c)

main :: IO()
main = getContents >>= print . sum . map (check . parse) . lines
