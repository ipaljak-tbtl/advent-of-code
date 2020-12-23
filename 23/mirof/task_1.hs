import Data.List
import Data.Maybe

main = putStrLn $ show (calcualateLastState $ input)

steps = 100
-- problem_1
input = [2, 1, 5, 6, 9, 4, 7, 8, 3]
-- example
-- input = [3, 8, 9, 1, 2, 5, 4, 6, 7]

calcualateLastState :: [Int] -> [Int]
calcualateLastState input = calcualateLastState' 0 steps input

calcualateLastState' :: Int -> Int -> [Int] -> [Int]
calcualateLastState' c            0              input = input
calcualateLastState' currentIndex remainingSteps input = calcualateLastState' ((newCurrentIndex + 1) `mod` (length input)) (remainingSteps - 1) newInput
    where triple             = take 3 $ drop (currentIndex + 1) $ input ++ input
          inputWithoutTriple = input \\ triple
          destination        = calculateDestination triple (input !! currentIndex) (length input)
          newInput           = insertSublist inputWithoutTriple triple destination
          newCurrentIndex    = fromJust $ findIndex (==(input !! currentIndex)) newInput

insertSublist [] triple destination = error $ show triple ++ " adsf"
insertSublist (i:input) triple destination
    | i /= destination = i : insertSublist input triple destination
    | otherwise        = i : triple ++ input


calculateDestination triple index max
  | (index - 1) <= 0          = calculateDestination triple (max + 1)   max
  | (index - 1) `elem` triple = calculateDestination triple (index - 1) max
  | otherwise                 = index - 1
