import Numeric (readHex)

---------------- Parsing ---------------

parse :: String -> [(Char, Int)] 
parse = map (parse_line . words) . lines 

parse_line :: [String] -> (Char, Int)
parse_line tokens 
    | direction == '0' = ('R', value)
    | direction == '1' = ('D', value)
    | direction == '2' = ('L', value)
    | direction == '3' = ('U', value)
    | otherwise        = error $ "Unreachable!"
        where
            direction = last $ init $ last tokens
            value = fromInteger $ fst $ head $ readHex $ init $ init $ tail $ tail $ last tokens
        

----------------- Solve ----------------

solve :: [(Char, Int)] -> Int
solve input = (abs $ (first_sum - second_sum) `div` 2) + (sum $ map snd input) `div` 2 + 1
    where 
        dots = create_map input [(0,0)] 
        xs   = map fst dots
        ys   = map snd dots
        ys_by_one = tail ys ++ [head ys] 
        xs_by_one = tail xs ++ [head xs] 
        first_sum  = foldl (+) 0 $ zipWith (*) xs        ys_by_one
        second_sum = foldl (+) 0 $ zipWith (*) xs_by_one ys

create_map :: [(Char, Int)] -> [(Int, Int)] -> [(Int, Int)]
create_map []                                list           = list 
create_map ((direction, num_of_steps):steps) grid@((x, y):_) 
    | direction == 'R' =  create_map steps ((x, y + num_of_steps):grid) 
    | direction == 'L' =  create_map steps ((x, y - num_of_steps):grid)
    | direction == 'D' =  create_map steps ((x + num_of_steps, y):grid)
    | direction == 'U' =  create_map steps ((x - num_of_steps, y):grid)
        
------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

