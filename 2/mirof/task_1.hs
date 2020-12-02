import Data.List.Split
import Data.List

main = do
    inputData <- readFile "problem_1.txt"
    let triples = map (\line -> words line) $ lines inputData
    let parsedData = map (\(policy:(char:_):password:_) -> (map (\x -> read x :: Integer) $ splitOn "-" policy, char , password)) triples
    let result = length $ filter (==True) $ map (\x -> isCorrectPassword x) parsedData
    putStrLn $ show result

isCorrectPassword :: ([Integer], Char, String) -> Bool
isCorrectPassword ((start:end:_),char,password) = start <= charCount && end >= charCount
    where charCount = genericLength $ filter (==char) password
