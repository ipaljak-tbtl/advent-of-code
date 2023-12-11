import Data.List (find, transpose, maximum)
import Data.Map (Map, fromList, lookup)
import Data.Maybe (fromJust, isJust, isNothing)
import Data.Set (Set)
import Text.Read
import qualified Data.Map as Mapp
import qualified Data.Set as Sett

---------------- Models ----------------

data Game = Game {
    fields :: Map (Int, Int) Char,
    start  :: (Int, Int)
} deriving (Show)

---------------- Parsing ---------------

parse :: String -> Game
parse input = Game { 
    fields = fromList matrix, 
    start = fst $ fromJust $ find ((==) 'S' . snd) matrix 
}
    where
        input_lines       = lines input
        with_column_num   = map (zip [0..]) input_lines
        with_matrix_index = transpose $ map (zip [0..]) $ transpose with_column_num
        matrix            = concat $ map (map (\(i, (j, value)) -> ((i, j), value))) with_matrix_index

----------------- Solve ----------------

solve :: Game -> Int
-- We start from just below start (not because it's correct to do so, but because we can!)
solve game = largest_cycle_size game (row + 1, col) (Sett.fromList [starting]) `div` 2
    where
        starting@(row, col) = start game

largest_cycle_size :: Game -> (Int, Int) -> Set (Int, Int)  -> Int
largest_cycle_size game current@(row, col) visited
    | Sett.member current visited             = Sett.size visited
    | not $ Mapp.member current (fields game) = 0 
    | direction == '.'                        = 0 

    | direction == '-'                        = maximum $ map combo_fun [(row, col + 1), (row, col - 1)]
    | direction == '|'                        = maximum $ map combo_fun [(row + 1, col), (row - 1, col)]

    | direction == 'L'                        = maximum $ map combo_fun [(row - 1, col), (row, col + 1)] 
    | direction == 'F'                        = maximum $ map combo_fun [(row + 1, col), (row, col + 1)] 
    | direction == 'J'                        = maximum $ map combo_fun [(row - 1, col), (row, col - 1)] 
    | direction == '7'                        = maximum $ map combo_fun [(row + 1, col), (row, col - 1)] 
    | otherwise = error $ "Invalid state! " ++ (show direction)
        where
            direction = fromJust $ Mapp.lookup current (fields game) 
            uvisited  = Sett.insert current visited 
            combo_fun = \coord -> largest_cycle_size game coord uvisited

------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

