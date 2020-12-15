import Data.List.Split
import Data.List
import qualified Data.Map as M
import Data.Maybe

main :: IO ()
main = readFile "problem_2.txt" >>= putStrLn . show . findNumber 30000000 . parseInputData

parseInputData :: String -> [(Int, Int)]
parseInputData input = zip (map read $ filter (/="") $ splitOn "," input) [0,1..]

findNumber :: Int -> [(Int, Int)] -> Int
findNumber limit list = findNumber' limit (length list) (fst $ last list) (M.fromList list) (M.fromList $ init list)

findNumber' :: Int -> Int -> Int -> M.Map Int Int -> M.Map Int Int -> Int
findNumber' limit currentIndex currentElem map oldMap
  | limit == currentIndex = currentElem
  | isJust elem    = findNumber' limit (currentIndex + 1) (currentIndex - fromJust elem - 1) (M.insert (currentIndex - fromJust elem - 1) currentIndex map) map
  | isNothing elem = findNumber' limit (currentIndex + 1) 0                                  (M.insert 0 currentIndex map)                                  map
        where elem = M.lookup currentElem oldMap
