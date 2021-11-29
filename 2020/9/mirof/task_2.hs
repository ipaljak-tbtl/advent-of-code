import Data.List

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . findRange . parseInputData

windowSize  = 25

parseInputData :: String -> [Integer]
parseInputData = map (\x -> read x :: Integer) . lines

findInvalid :: [Integer] -> Integer
findInvalid numbers
    | condition = findInvalid $ tail numbers
    | otherwise = number
        where condition = isWindowSum window number
              number    = numbers !! windowSize
              window    = take windowSize numbers

isWindowSum :: [Integer] -> Integer -> Bool
isWindowSum window number = number `elem` [ x + y | (i, x) <- iWindow, (j, y) <- iWindow ]
    where iWindow = zip [0,1..] window


findRange :: [Integer] -> Integer
findRange numbers =  (fst result) + (snd result)
    where result = findRange' numbers 0 0 (findInvalid numbers)

findRange' :: [Integer] -> Integer -> Integer -> Integer -> (Integer, Integer)
findRange' numbers start end number
    | res == number = (head sortedSol , last sortedSol)
    | res > number  = findRange' numbers (start + 1) end number
    | res < number  = findRange' numbers start (end + 1) number
        where res       = sumRange numbers start end
              sortedSol = sort [x | (i, x) <- zip [0,1..] numbers, i >= start,  i < end]


sumRange :: [Integer] -> Integer -> Integer -> Integer
sumRange numbers start end = sum [x | (i, x) <- zip [0,1..] numbers, i >= start,  i < end]
