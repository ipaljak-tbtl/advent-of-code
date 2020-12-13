import Data.List
import Data.List.Split
import Data.Maybe

ceil :: Int -> Int -> Int
ceil a b = (a + b - 1) `div` b

parseLines :: [String] -> [(Int, Int)]
parseLines =
  map (\(i, xi) -> (read xi, i)) . filter ((/= "x") . snd) . zip [0..] . splitOn "," . last

solve :: [(Int, Int)] -> [(Int, Int)]
solve ids = scanl' f  (head ids) $ tail ids
  where
    f (p, off) (a, b) = (p * a, (p * (fromJust $ find (checkTime) [1..])) + off `mod` (p * a))
      where checkTime coef = (coef * p + off + b) `mod` a == 0

main :: IO ()
main = getContents >>= print . solve . parseLines . lines
