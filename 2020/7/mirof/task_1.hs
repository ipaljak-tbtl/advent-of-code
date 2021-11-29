import Data.List.Split
import qualified Data.Set as S
import Data.Char (isSpace)
import Data.List

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . length . S.fromList . numberOfBagsWithShinyGoldBag "shiny gold bag" . parseInputData

parseInputData :: String -> [(String, [String])]
parseInputData = map parseLine . map init . lines

parseLine :: String -> (String, [String])
parseLine line = ( bag , map (f . f) bags )
    where splitted = splitOn "contain" line
          bag = init $ (f . f) $ splitted !! 0
          bags = map (\x -> if last x == 's' then init x else x) $ map (tail . f . f) $ splitOn "," (splitted !! 1)
          f = reverse . dropWhile isSpace

numberOfBagsWithShinyGoldBag :: String -> [(String, [String])]  -> [String]
numberOfBagsWithShinyGoldBag currentBag allBags = [currentBag] ++ (foldl (++) [] $ (map (\x -> numberOfBagsWithShinyGoldBag x allBags) bagsWithShinyGoldBag))
    where bagsWithShinyGoldBag = map fst $ filter (\(_, bags) -> currentBag `elem` bags) allBags


