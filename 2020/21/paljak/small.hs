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
               Set.map (\x' -> (y', x')) .
               foldl1 (\a b -> Set.intersection a b) .
               map (\(Food x _) -> x) $
               filter (\(Food _ y) -> y' `Set.member` y) food

match :: [Food] -> Map.Map String String
match = matching . buildGraph

findSafe :: [Food] -> Map.Map String String -> Set.Set String
findSafe food matched = Set.filter (unknown) .
                        Set.fromList $
                        concatMap (\(Food x y) -> filter (`Map.notMember` matched) $ Set.toList x) food
  where
    unknown x' = all (\f@(Food x y) -> allMatched f || x' `Set.notMember` x) food
    allMatched (Food x y) = all (\y' -> any (\x' -> Map.lookup x' matched == Just y') x) y

solve :: [Food] -> Int
solve food = cnt . Set.toList . findSafe food $ match food
  where cnt xs = sum $ map (\x' -> sum [fromEnum $ x' `Set.member` x | (Food x y) <- food]) xs

main :: IO ()
main = getContents >>= print . solve . parseLines . lines
