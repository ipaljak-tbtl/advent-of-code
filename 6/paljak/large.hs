import Data.List.Split

import qualified Data.Set as Set

countAnswers :: [String] -> Int
countAnswers = length . foldl1 (Set.intersection) . map (Set.fromList)

main :: IO ()
main = getContents >>= print . sum . map (countAnswers) . splitOn [""] . lines
