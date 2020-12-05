import Data.Char
import Data.List
import Data.List.Utils

fromBinary :: Char -> Char -> String -> Int
fromBinary one zero s = foldl' (\ret bit -> 2 * ret + digitToInt bit) 0 bits
  where
    bits = replace [one] "1" $ replace [zero] "0" s

seatID :: String -> Int
seatID s = 8 * (fromBinary 'B' 'F' front) + (fromBinary 'R' 'L' back)
  where
    front = take 7 s
    back  = drop 7 s

main :: IO()
main = getContents >>= print . maximum . map (seatID) . lines
