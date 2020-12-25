import Data.List
import Data.Maybe

import Math.NumberTheory.Powers.Modular

m = 20201227

solve :: (Int, Int) -> Int
solve (cpub, dpub) = powMod dpub cloop m
  where
    cloop = snd . fromJust . find (\(x, _) -> x == cpub) $
            scanl' (\(x, i) _ -> (x * 7 `mod` m, i + 1)) (7, 1) [1..]

parseLines :: [String] -> (Int, Int)
parseLines [a, b] = (read a, read b)

main :: IO ()
main = getContents >>= print . solve . parseLines . lines
