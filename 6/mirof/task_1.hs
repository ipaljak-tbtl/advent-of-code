import Data.List.Split
import qualified Data.Set as S

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . sumOfGroupPositiveAnswers . parseInputData

parseInputData :: String -> [[String]]
parseInputData = map words . splitOn "\n\n"

sumOfGroupPositiveAnswers :: [[String]] -> Int
sumOfGroupPositiveAnswers = sum . map (length . setOfGroupAnswers)

setOfGroupAnswers :: [String] -> S.Set Char
setOfGroupAnswers = S.fromList . concat

