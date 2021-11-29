import Data.List
import Data.List.Split
import Data.Maybe

import qualified Data.Set as Set
import qualified Data.Map.Strict as Map

type Node  = String
type Graph = Map.Map Node [Node]

parseLine :: Graph -> String -> Graph
parseLine adj s
  | "no other bags" `isInfixOf` s = adj
  | otherwise                     = Map.insert outerBag innerBags adj
    where
      outerBag  = unwords . take 2 $ words s
      innerBags = map (innerCol) $ splitOn "," innerSuff
      innerCol  = unwords . take 2 . tail . words
      innerSuff = unwords . drop 4 $ words s

outerBags :: Graph -> [Node]
outerBags g = filter (isOuterBag) . delete "shiny gold" $ Map.keys g
  where
    isOuterBag "shiny gold" = True
    isOuterBag bag
      | bag `Map.notMember` g = False
      | otherwise             = any (isOuterBag) $ g Map.! bag

main :: IO ()
main = getContents >>= print . length . outerBags . foldl' (parseLine) Map.empty . lines
