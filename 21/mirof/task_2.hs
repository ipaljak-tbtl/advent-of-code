import Data.Function (on)
import Data.Graph.MaxBipartiteMatching (matching)
import Data.List
import Data.List.Split
import Data.Maybe
import qualified Data.Map as M
import qualified Data.Set as S

main :: IO ()
main = readFile "problem_2.txt" >>= putStrLn . show . intercalate "," .  map snd . reverse . sortBy (flip compare `on` fst) . findMismatches. parseInputData

----------------------------------------------------------------------------------------------------
------------------------------------------ PARSING -------------------------------------------------
----------------------------------------------------------------------------------------------------

parseInputData :: String -> ([(String, String)], [([String], [String])])
parseInputData input = (concat $ map cartProd output, output)
    where output = map (\(xs:ys:_) -> (words xs, map init $ tail $ words ys)) $ map (splitOn "(") $ lines input
          cartProd (xs, ys) = [(x, y) | x <- xs, y <- ys]


----------------------------------------------------------------------------------------------------
------------------------------------------- LOGIC --------------------------------------------------
----------------------------------------------------------------------------------------------------

findMismatches :: ([(String, String)], [([String], [String])]) -> [(String, String)]
findMismatches ([], _) = []
findMismatches (input, allLines) = if input /= newInput then findMismatches (newInput, allLines) else matches
    where matches   = M.toList $ matching $ S.fromList input
          wrongElem = getMismatchSolution (matches, allLines)
          newInput  = if isJust wrongElem then filter (\(x, y) -> Just (y, x) /= wrongElem) input else input

getMismatchSolution :: ([(String, String)], [([String], [String])]) -> Maybe (String, String)
getMismatchSolution (input, []) = Nothing
getMismatchSolution (input, ((ingredients, allergens):other)) = element
    where filteredInput = filter (\x ->       (fst x) `elem` allergens)   input
          wrongMatches  = filter (\x -> not $ (snd x) `elem` ingredients) filteredInput
          element = if length wrongMatches == 0 then getMismatchSolution (input, other) else Just (wrongMatches !! 0)



