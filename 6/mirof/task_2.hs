import Data.List.Split
import qualified Data.Set as S

possibleAnswers :: [Char]
possibleAnswers = ['a'..'z']

main :: IO ()
main = readFile "problem_2.txt" >>= putStrLn . show . sumOfGroupPositiveAnswers . parseInputData

parseInputData :: String -> [[String]]
parseInputData = map words . splitOn "\n\n"

sumOfGroupPositiveAnswers :: [[String]] -> Int
sumOfGroupPositiveAnswers = sum . map (length . interesctionsOfAnswers)

interesctionsOfAnswers :: [String] -> S.Set Char
interesctionsOfAnswers = foldl S.intersection (S.fromList possibleAnswers) . map (S.fromList)

