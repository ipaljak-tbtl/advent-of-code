import Data.List.Split
import Data.List
import Data.Maybe
import qualified Data.Map as M

type Pattern = String
type Rule = [Pattern]

main :: IO ()
main = readFile "problem_2.txt" >>= putStrLn . show . solve . parseInputData

tuplify2 :: Show a => [a] -> (a,a)
tuplify2 (x:y:_) = (x,y)

parseInputData :: String -> (M.Map String [[String]], [String])
parseInputData input = (rules, lines values)
    where rules = M.fromList $ map (\(x, y) -> (x, map words $ splitOn "|" $ filter (/='"') y)) $ map (tuplify2 . splitOn ":") $ lines rulesStr
          (rulesStr, values) = tuplify2 $ splitOn "\n\n" input

solve :: (M.Map String [[String]], [String]) -> Int
solve (_, []) = 0
solve (allRules, (value:values)) = num + solve (allRules, values)
    where result = patternPrefix allRules ["0"] "" value
          num = if Just [value] `elem` result then  1 else 0

patternPrefix :: M.Map String [[String]] -> Rule -> String -> String -> [Maybe [String]]
patternPrefix _        ["a"]          acc input
  | isPrefixOf "a" input  = [Just ["a"]]
  | otherwise             = [Nothing]

patternPrefix _        ["b"]          acc input
  | isPrefixOf "b" input  = [Just ["b"]]
  | otherwise             = [Nothing]

patternPrefix _        []             acc input = [Just [acc]]
patternPrefix allRules (pattern:rule) acc input
    | length acc >= 200 = [Just [acc]]
    | otherwise        = result
    where fewRules    = fromJust $ M.lookup pattern allRules
          fewPrefixes = concat $ map (\oneRule -> patternPrefix allRules oneRule "" input) fewRules
          fewResults  = concat $ map (\prefixes -> if isJust prefixes then patternPrefix allRules rule (acc ++ (head $ fromJust prefixes)) (drop (lengthJust prefixes) input) else [Nothing]) fewPrefixes
          result      = filter (/=Nothing) fewResults

lengthJust (Just l) = length $ head l
lengthJust Nothing  = 0

