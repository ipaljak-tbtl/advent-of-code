import Data.List.Split

ceil :: Int -> Int -> Int
ceil a b = (a + b - 1) `div` b

parseLines :: [String] -> (Int, [Int])
parseLines lines = (timestamp, ids)
  where
    timestamp = read $ head lines
    ids       = map (read) . filter (/= "x") . splitOn "," $ last lines

solve :: (Int, [Int]) -> Int
solve (time, ids) = (fst minTime - time) * snd minTime
  where
    findTime t = (t * (ceil time t), t)
    minTime    = minimum $ map (findTime) ids

main :: IO ()
main = getContents >>= print . solve . parseLines . lines
