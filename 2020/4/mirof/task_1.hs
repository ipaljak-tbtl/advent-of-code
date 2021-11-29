import Data.List.Split
import Data.List

main = readFile "problem_1.txt" >>= putStrLn . show . countCorrectPassports

countCorrectPassports :: String -> Int
countCorrectPassports input = length $ filter (checkPassport . words) $ splitOn "\n\n" input

checkPassport :: [String] -> Bool
checkPassport fields = (length fields == 8) || (length fields == 7 && not isCidAbsent)
    where isCidAbsent = any (isPrefixOf "cid") fields
