import Data.List
import Data.List.Split

parseLines :: [String] -> ([Int], [Int])
parseLines l = (parseDeck $ head sl, parseDeck $ last sl)
  where
    sl = splitOn [""] l
    parseDeck = map (read) . tail

play :: ([Int], [Int]) -> Int
play (alice, bob)
  | alice == []               = score bob
  | bob   == []               = score alice
  | (head alice) > (head bob) = play ((tail alice) ++ [head alice] ++ [head bob], tail bob)
  | otherwise                 = play (tail alice, tail bob ++ [head bob] ++ [head alice])
  where
    score []       = 0
    score l@(x:xs) = x * (length l) + score xs


main :: IO ()
main = getContents >>= print . play . parseLines . lines
