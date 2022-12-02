import Data.Char

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

parse :: String -> [(Int, Int)]
parse = map str_to_tuple . lines

str_to_tuple :: String -> (Int, Int)
str_to_tuple (opponent_move:space:my_move:_) = (ord opponent_move - ord 'A', ord my_move - ord 'X')

solve :: [(Int, Int)] -> Int
solve = sum . map play_game

play_game :: (Int, Int) -> Int
play_game (opponent, me)
    -- Draw
    | opponent               == me = me + 1 + 3
    -- Win
    | (opponent + 1) `mod` 3 == me = me + 1 + 6
    -- Lose
    | (opponent - 1) `mod` 3 == me = me + 1
