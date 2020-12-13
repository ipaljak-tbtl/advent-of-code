import Data.List.Split
import Data.List
import Data.Ord

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . idWithMinutesDelay . parseInputData

parseInputData :: String -> (Integer, [Integer])
parseInputData input = ((read start :: Integer), map (\x -> read x :: Integer) $ filter (/="x") $ splitOn "," ids)
    where (start:ids:[]) = lines input

idWithMinutesDelay :: (Integer, [Integer]) -> Integer
idWithMinutesDelay (start, ids) = fst minimumTuple * snd minimumTuple
    where minimumTuple = minimumBy (comparing snd) $  map (\id -> (id, id - (start `mod` id))) ids
