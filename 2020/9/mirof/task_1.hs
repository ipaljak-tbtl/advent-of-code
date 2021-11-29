main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . findInvalid . parseInputData

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
