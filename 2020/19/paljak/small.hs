import Data.List
import Data.List.Split

import qualified Data.Map as Map

type RuleId = Int
data Rule   = Leaf String | Concat [RuleId] | Any [Rule] deriving Show

parseRule :: String -> (Int, Rule)
parseRule s = (ruleId, rule)
  where
    ruleId = read . head $ splitOn ":" s
    rhs    = tail . last $ splitOn ":" s
    rule
     | '"' `elem` rhs = Leaf $ read rhs
     | '|' `elem` rhs = Any . map (Concat . parseConcat) $ splitOn "|" rhs
     | otherwise      = Concat $ parseConcat rhs
     where parseConcat = map (read) . words

parseRules :: [String] -> Map.Map Int Rule
parseRules = foldl' (\m (k, v) -> Map.insert k v m) Map.empty . map (parseRule)

parseLines :: [String] -> (Map.Map Int Rule, [String])
parseLines l = (parseRules ruleLines, wordLines)
  where
    ruleLines = take 134 l
    wordLines = drop 135 l

maxLen :: Map.Map Int Rule -> Rule -> Int
maxLen m (Leaf _)     = 1
maxLen m (Concat ids) = sum $ map (\i -> maxLen m (m Map.! i)) ids
maxLen m (Any rs)     = maximum $ map (maxLen m) rs

match :: Map.Map Int Rule -> String -> Rule -> Bool
match m t (Leaf s)     = s == t
match m t r@(Any rs)   = length t <= maxLen m r && any (match m t) rs
match m "" (Concat []) = True
match m "" (Concat _)  = False
match m t (Concat [])  = False
match m t (Concat (i:[])) = match m t $ m Map.! i
match m t r@(Concat ids)  = length t <= maxLen m r && any (matchPref) [0..length t]
  where matchPref i = (match m (take (i + 1) t) $ m Map.! (head ids)) &&
                      (match m (drop (i + 1) t) (Concat $ tail ids))

matching :: (Map.Map Int Rule, [String]) -> [String]
matching (rules, ts) = filter (\t -> match rules t (rules Map.! 0)) ts

main :: IO ()
main = getContents >>= print . length . matching . parseLines . lines
