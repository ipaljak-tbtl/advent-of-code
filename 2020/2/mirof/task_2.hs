import Data.List.Split
import Data.List
import Data.Bool

main = do
    inputData <- readFile "problem_2.txt"
    let triples = map (\line -> words line) $ lines inputData
    let parsedData = map (\(policy:(char:_):password:_) -> (map (\x -> read x :: Int) $ splitOn "-" policy, char , password)) triples
    let result = length $ filter (==True) $ map (\x -> isCorrectPassword x) parsedData
    putStrLn $ show result

isCorrectPassword :: ([Int], Char, String) -> Bool
isCorrectPassword ((start:end:_),char,password) = (firstChar == char) /= (lastChar == char)
    where firstChar = password !! (start - 1)
          lastChar  = password !! (end - 1)
