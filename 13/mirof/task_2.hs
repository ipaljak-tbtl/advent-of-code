import Data.List.Split
import Data.List
import Data.Ord
import Math.NumberTheory.Moduli.Chinese

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . getStartTime . parseInputData

parseInputData :: String -> [(Integer, Integer)]
parseInputData input = map (\(x, y) -> (x, read y :: Integer)) $ filter (\x -> (snd x) /="x") $ zip [0,1..] $ splitOn "," ids
    where (start:ids:[]) = lines input

getStartTime :: [(Integer, Integer)] -> Maybe Integer
getStartTime = chineseRemainder . map (\(x, y) -> ((y - x) `mod` y, y))

