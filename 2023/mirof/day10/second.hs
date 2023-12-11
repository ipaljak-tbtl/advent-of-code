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
    start  :: (Int, Int),
    raw    :: [[((Int, Int), Char)]]
} deriving (Show)

---------------- Parsing ---------------

parse :: String -> Game
parse input = Game { 
    fields = fromList matrix, 
    start  = fst $ fromJust $ find ((==) 'S' . snd) matrix,
    raw    = raw
}
    where
        input_lines       = lines input
        with_column_num   = map (zip [0..]) input_lines
        with_matrix_index = transpose $ map (zip [0..]) $ transpose with_column_num
        raw               = map (map (\(i, (j, value)) -> ((i, j), value))) with_matrix_index
        matrix            = concat raw 

----------------- Solve ----------------

solve :: Game -> Int
-- We start from just below start (not because it's correct to do so, but because we can!)
solve game = sum $ map (row_count edge False) (raw game)
    where
        starting@(row, col) = start game
        edge                = largest_cycle_size game (row + 1, col) (Sett.fromList [starting])

row_count :: Set (Int, Int) -> Bool -> [((Int, Int), Char)] -> Int
row_count edge is_inside ((coord@(x, y), '|'):rest)
    | Sett.member coord edge =     row_count edge (not is_inside) rest
    | is_inside              = 1 + row_count edge      is_inside  rest
    | otherwise              =     row_count edge      is_inside  rest

row_count edge is_inside ((coord@(x, y), 'S'):rest)
    | Sett.member coord edge =     row_count edge (not is_inside) rest
    | is_inside              = 1 + row_count edge      is_inside  rest
    | otherwise              =     row_count edge      is_inside  rest

row_count edge is_inside ((coord@(x, y), 'L'):rest)
    | Sett.member coord edge && (snd $ head urest) == 'J' =     row_count edge      is_inside  (tail urest)
    | Sett.member coord edge && (snd $ head urest) == '7' =     row_count edge (not is_inside) (tail urest)
    | is_inside                                           = 1 + row_count edge      is_inside         rest
    | otherwise                                           =     row_count edge      is_inside         rest
        where
            urest = dropWhile (\(_, val) -> val == '-') rest

row_count edge is_inside ((coord@(x, y), 'F'):rest)
    | Sett.member coord edge && (snd $ head urest) == '7' =     row_count edge      is_inside  (tail urest)
    | Sett.member coord edge && (snd $ head urest) == 'J' =     row_count edge (not is_inside) (tail urest)
    | is_inside                                           = 1 + row_count edge      is_inside         rest
    | otherwise                                           =     row_count edge      is_inside         rest
        where
            urest = dropWhile (\(_, val) -> val == '-') rest

row_count edge is_inside (a@(coord@(x, y), val):rest) 
    | Sett.member coord edge = error $ show a
    | is_inside              = 1 + row_count edge      is_inside   rest
    | otherwise              =     row_count edge      is_inside   rest
    
row_count _  _ [] = 0

largest_cycle_size :: Game -> (Int, Int) -> Set (Int, Int) -> Set (Int, Int) 
largest_cycle_size game current@(row, col) visited
    | Sett.member current visited             = visited
    | not $ Mapp.member current (fields game) = visited 
    | direction == '.'                        = visited 

    | direction == '-'                        = ret_bigger $ map combo_fun [(row, col + 1), (row, col - 1)]
    | direction == '|'                        = ret_bigger $ map combo_fun [(row + 1, col), (row - 1, col)]

    | direction == 'L'                        = ret_bigger $ map combo_fun [(row - 1, col), (row, col + 1)] 
    | direction == 'F'                        = ret_bigger $ map combo_fun [(row + 1, col), (row, col + 1)] 
    | direction == 'J'                        = ret_bigger $ map combo_fun [(row - 1, col), (row, col - 1)] 
    | direction == '7'                        = ret_bigger $ map combo_fun [(row + 1, col), (row, col - 1)] 
    | otherwise = error $ "Invalid state! " ++ (show direction)
        where
            direction = fromJust $ Mapp.lookup current (fields game) 
            uvisited  = Sett.insert current visited 
            combo_fun = \coord -> largest_cycle_size game coord uvisited

ret_bigger :: [Set (Int, Int)] -> Set (Int, Int)
ret_bigger [set1, set2] = if length set1 > length set2 then set1 else set2

------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

