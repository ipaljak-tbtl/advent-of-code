import Data.List
import Data.Maybe
import qualified Data.HashMap.Strict as M

main = putStrLn $ show (calcualateLastState $ input)

steps   = 10000000
allNums = [2, 1, 5, 6, 9, 4, 7, 8, 3] ++ [10..1000000]

max :: Int
max = length allNums

input :: M.HashMap Int Int
input = M.insert (last allNums) (head allNums) numsWithNeighbour
    where numsWithNeighbour = M.fromList $ zip allNums (tail allNums)

calcualateLastState :: M.HashMap Int Int -> Int
calcualateLastState input = numToOne * numOneFromOne
    where lastState     = calcualateLastState' (head allNums) steps input
          numToOne      = fromJust $ M.lookup 1        lastState
          numOneFromOne = fromJust $ M.lookup numToOne lastState

calcualateLastState' :: Int -> Int -> M.HashMap Int Int -> M.HashMap Int Int
calcualateLastState' _           0              input = input
calcualateLastState' currentElem remainingSteps input = calcualateLastState' (fromJust $ M.lookup currentElem newInput) (remainingSteps - 1) newInput
    where newInput = calculation currentElem remainingSteps input

calculation currentElem remainingSteps input = newInput
    where firstElemOfTriple  = fromJust $ M.lookup currentElem        input
          secondElemOfTriple = fromJust $ M.lookup firstElemOfTriple  input
          thirdElemOfTriple  = fromJust $ M.lookup secondElemOfTriple input
          triple             = [firstElemOfTriple, secondElemOfTriple, thirdElemOfTriple]
          destinationElem    = calculateDestination triple currentElem
          inputWithoutTriple = foldl (\acc x -> M.delete x acc) (M.insert currentElem (fromJust $ M.lookup thirdElemOfTriple input) input) triple

          inputWithThirdInserted  = M.insert thirdElemOfTriple  (fromJust $ M.lookup destinationElem inputWithoutTriple) inputWithoutTriple
          inputWithSecondInserted = M.insert secondElemOfTriple thirdElemOfTriple  inputWithThirdInserted
          inputWithFirstInserted  = M.insert firstElemOfTriple  secondElemOfTriple inputWithSecondInserted
          newInput                = M.insert destinationElem    firstElemOfTriple  inputWithFirstInserted

calculateDestination triple index
  | (index - 1) <= 0          = calculateDestination triple (Main.max + 1)
  | (index - 1) `elem` triple = calculateDestination triple (index - 1)
  | otherwise                 = index - 1


