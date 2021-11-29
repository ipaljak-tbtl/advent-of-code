import Data.Char (isSpace, digitToInt)
import Data.List
import Data.Maybe
import Data.List.Split
import Data.List.Utils (replace)
import qualified Data.Set as S

main :: IO ()
main = readFile "problem_2.txt" >>= putStrLn . show . countBags "shiny gold bag" . parseInputData

parseInputData :: String -> [(String, [(Int, String)])]
parseInputData = map parseLine . map init . lines

parseLine :: String -> (String, [(Int, String)])
parseLine line = ( bag , bags )
    where splitted = splitOn "contain" line
          bag = init $ (f . f) $ splitted !! 0
          bags = map (\(x, y) -> if last y == 's' then (x, init y) else (x, y)) $ map (\x -> ( (digitToInt $ head x), (f . f . tail) x)) $ map (replace "no" "0") $ map (f . f) $ splitOn "," (splitted !! 1)
          f = reverse . dropWhile isSpace

countBags :: String -> [(String, [(Int, String)])] -> Int
countBags currentBag allBags =  foldl (+) 0 $ map (\(x, y) -> x + x * countBags y allBags) $ filter (\(_, x) -> x /= "other bag") otherBags
    where currentCount = sum $ map fst $ snd $ fromJust $ find (\(x, _) -> x == currentBag) allBags
          otherBags    = snd $ fromJust $ find (\(x, _) -> x == currentBag) allBags

