import Data.List
import Data.List.Split

import qualified Data.Set as Set

parseLines :: [String] -> ([Int], [Int])
parseLines l = (parseDeck $ head sl, parseDeck $ last sl)
  where
    sl = splitOn [""] l
    parseDeck = map (read) . tail

play :: Set.Set ([Int], [Int]) -> ([Int], [Int]) -> (Int, [Int])
play memo state@(alice, bob)
  | state `Set.member` memo     = (1, alice)
  | alice == []                 = (2, bob)
  | bob   == []                 = (1, alice)
  | not recRound && aliceHi     = play memo' ((tail alice) ++ [head alice] ++ [head bob], tail bob)
  | not recRound && not aliceHi = play memo' (tail alice, tail bob ++ [head bob] ++ [head alice])
  | fst recResult == 1          = play memo' ((tail alice) ++ [head alice] ++ [head bob], tail bob)
  | otherwise                   = play memo' (tail alice, tail bob ++ [head bob] ++ [head alice])
  where
    recRound  = (head alice) < (length alice) && (head bob) < (length bob)
    aliceHi   = (head alice) > (head bob)
    memo'     = Set.insert (alice, bob) memo
    recResult = play Set.empty (take (head alice) $ tail alice, take (head bob) $ tail bob)

score :: [Int] -> Int
score []       = 0
score l@(x:xs) = x * (length l) + score xs

main :: IO ()
main = getContents >>= print . score . snd . play Set.empty . parseLines . lines
