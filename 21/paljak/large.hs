import Data.List
import Data.List.Split
import Data.Maybe

import qualified Data.Set as Set
import qualified Data.Map as Map

import MaxMatching

data Food = Food (Set.Set String) (Set.Set String) deriving (Eq, Show)

parseLines :: [String] -> [Food]
parseLines = map (parseLine)
  where
    parseLine s = Food (Set.fromList . head $ parts s)
                       (Set.fromList . map (init) . last $ parts s)
    parts = splitOn ["(contains"] . words

buildGraph :: [Food] -> Set.Set (String, String)
buildGraph food = Set.fromList $ concatMap (edges) alerg
  where
    alerg    = Set.fromList $ concatMap (\(Food _ y) -> Set.toList y) food
    edges y' = Set.toList .
               Set.map (\x' -> (x', y')) .
               foldl1 (\a b -> Set.intersection a b) .
               map (\(Food x _) -> x) $
               filter (\(Food _ y) -> y' `Set.member` y) food

match :: [Food] -> Map.Map String String
match = matching . buildGraph

solve :: [Food] -> String
solve = danger . match
  where
    danger = concat . intersperse "," . Map.elems

main :: IO ()
main = getContents >>= print . solve . parseLines . lines
