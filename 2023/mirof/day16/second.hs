
import Debug.Trace
import Data.List (nub, sort, transpose)
import Data.Map (fromList, Map)
import qualified Data.Set as Sett
import qualified Data.Map as Mapp

---------------- Parsing ---------------

parse :: String -> Map (Int, Int) Char
parse input = fromList matrix 
    where
        input_lines       = lines input
        with_column_num   = map (zip [0..]) input_lines
        with_matrix_index = transpose $ map (zip [0..]) $ transpose with_column_num
        matrix            = concat $ map (map (\(i, (j, value)) -> ((i, j), value))) with_matrix_index

----------------- Solve ----------------

solve :: Map (Int, Int) Char -> Int
solve input = maximum $ from_left ++ from_right ++ from_up ++ from_down 
    where 
        from_left  = map (\start -> length $ nub $ sort $ map fst $ Sett.elems $ beam input start 'R' (Sett.fromList [])) [(x, 0  ) | x <- [0..110]]
        from_right = map (\start -> length $ nub $ sort $ map fst $ Sett.elems $ beam input start 'L' (Sett.fromList [])) [(x, 109) | x <- [0..110]]
        from_up    = map (\start -> length $ nub $ sort $ map fst $ Sett.elems $ beam input start 'D' (Sett.fromList [])) [(0, x  ) | x <- [0..110]]
        from_down  = map (\start -> length $ nub $ sort $ map fst $ Sett.elems $ beam input start 'U' (Sett.fromList [])) [(109, x) | x <- [0..110]]
    
beam :: Map (Int, Int) Char -> (Int, Int) -> Char -> Sett.Set ((Int, Int), Char) -> Sett.Set ((Int, Int), Char)
beam grid current@(x, y) direction visited
    | not $ Mapp.member current grid                 = visited
    |       Sett.member (current, direction) visited = visited

    -- just keep going in same direction
    | direction == 'R' && Mapp.lookup current grid == Just '.'  = beam grid (x, y + 1) direction (Sett.insert (current, direction) visited)
    | direction == 'L' && Mapp.lookup current grid == Just '.'  = beam grid (x, y - 1) direction (Sett.insert (current, direction) visited)
    | direction == 'U' && Mapp.lookup current grid == Just '.'  = beam grid (x - 1, y) direction (Sett.insert (current, direction) visited)
    | direction == 'D' && Mapp.lookup current grid == Just '.'  = beam grid (x + 1, y) direction (Sett.insert (current, direction) visited)

    -- slash appears
    | direction == 'R' && Mapp.lookup current grid == Just '/'  = beam grid (x - 1, y) 'U' (Sett.insert (current, direction) visited)
    | direction == 'L' && Mapp.lookup current grid == Just '/'  = beam grid (x + 1, y) 'D' (Sett.insert (current, direction) visited)
    | direction == 'U' && Mapp.lookup current grid == Just '/'  = beam grid (x, y + 1) 'R' (Sett.insert (current, direction) visited)
    | direction == 'D' && Mapp.lookup current grid == Just '/'  = beam grid (x, y - 1) 'L' (Sett.insert (current, direction) visited)

    -- backslash appears
    | direction == 'R' && Mapp.lookup current grid == Just '\\' = beam grid (x + 1, y) 'D' (Sett.insert (current, direction) visited)
    | direction == 'L' && Mapp.lookup current grid == Just '\\' = beam grid (x - 1, y) 'U' (Sett.insert (current, direction) visited)
    | direction == 'U' && Mapp.lookup current grid == Just '\\' = beam grid (x, y - 1) 'L' (Sett.insert (current, direction) visited)
    | direction == 'D' && Mapp.lookup current grid == Just '\\' = beam grid (x, y + 1) 'R' (Sett.insert (current, direction) visited)

    -- vertical appears
    | (direction == 'L' || direction == 'R') && Mapp.lookup current grid == Just '|' = beam grid (x + 1, y) 'D' (Sett.insert (current, direction) vert_set)
    | direction == 'U' && Mapp.lookup current grid == Just '|'  = beam grid (x - 1, y) 'U' (Sett.insert (current, direction) visited)
    | direction == 'D' && Mapp.lookup current grid == Just '|'  = beam grid (x + 1, y) 'D' (Sett.insert (current, direction) visited)

    -- horizontal appears
    | (direction == 'U' || direction == 'D') && Mapp.lookup current grid == Just '-' = beam grid (x, y + 1) 'R' (Sett.insert (current, direction) hor_set)
    | direction == 'L' && Mapp.lookup current grid == Just '-'  = beam grid (x, y - 1) 'L' (Sett.insert (current, direction) visited)
    | direction == 'R' && Mapp.lookup current grid == Just '-'  = beam grid (x, y + 1) 'R' (Sett.insert (current, direction) visited)

    | otherwise = error "Unreachable state"
        where 
            vert_set = beam grid (x - 1, y) 'U' (Sett.insert (current, direction) visited)
            hor_set  = beam grid (x, y - 1) 'L' (Sett.insert (current, direction) visited)

------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution
