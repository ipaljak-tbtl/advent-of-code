import Data.List
import Data.List.Split
import Data.Maybe

import qualified Data.Set as Set
import qualified Data.Map.Strict as Map

type Node  = String
type Graph = Map.Map Node [(Node, Int)]

root = "shiny gold"

parseLine :: Graph -> String -> Graph
parseLine adj s
  | "no other bags" `isInfixOf` s = adj
  | otherwise                     = Map.insert outerBag innerBags adj
    where
      outerBag  = unwords . take 2 $ words s
      innerBags = map (\x -> (innerCol x, innerCnt x)) $ splitOn "," innerSuff
      innerCol  = unwords . take 2 . tail . words
      innerCnt  = read . head . words
      innerSuff = unwords . drop 4 $ words s

bagCount :: Node -> Graph -> Int
bagCount bag g
  | bag `Map.notMember` g = 0
  | otherwise = sum . map (\(n, c) -> c * (1 + bagCount n g)) $ g Map.! bag

main :: IO ()
main =
  getContents >>= print . bagCount root . foldl' (parseLine) Map.empty . lines
