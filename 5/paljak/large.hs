import Data.Char
import Data.List
import Data.List.Utils
import Data.Maybe

fromBinary :: Char -> Char -> String -> Int
fromBinary one zero s = foldl' (\ret bit -> 2 * ret + digitToInt bit) 0 bits
  where
    bits = replace [one] "1" $ replace [zero] "0" s

seatID :: String -> Int
seatID s = 8 * (fromBinary 'B' 'F' front) + (fromBinary 'R' 'L' back)
  where
    front = take 7 s
    back  = drop 7 s

findMySeat :: [Int] -> Int
findMySeat ids = fromJust $ find (isMySeat) [0..]
  where
    isMySeat x = x `notElem` ids && (x - 1) `elem` ids && (x + 1) `elem` ids


main :: IO()
main = getContents >>= print . findMySeat . map (seatID) . lines
