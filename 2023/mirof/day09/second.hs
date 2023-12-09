import Text.Read

---------------- Parsing ---------------

parse :: String -> [[Integer]]
parse = map (map (\num -> read num :: Integer) . words) . lines

----------------- Solve ----------------

solve :: [[Integer]] -> Integer
solve = sum . map interpolate_new_value 

interpolate_new_value :: [Integer] -> Integer
interpolate_new_value numbers
    | all (== 0) numbers = 0
    | otherwise          = (head numbers) - (interpolate_new_value . diffs) numbers

diffs :: [Integer] -> [Integer]
diffs [last]                     = []
diffs (num1:rest@(num2:numbers)) = (num2 - num1) : diffs rest
        
------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

