{-# LANGUAGE NamedFieldPuns #-}

import Debug.Trace
import Data.List (sortBy)
import Data.Set (fromList, size, Set, union, difference)

---------------- Models ----------------

data Block = Block {
    x :: (Int, Int),
    y :: (Int, Int),
    z :: (Int, Int)
} deriving (Show, Eq, Ord)

area_intersect :: (Int, Int) -> (Int, Int) -> (Int, Int) -> (Int, Int) -> Bool
area_intersect (xs1, xe1) (ys1, ye1) (xs2, xe2) (ys2, ye2) 
    -- any part of first is inside of the second 
    | xs1 >= xs2 && xs1 <= xe2 && ys1 >= ys2 && ys1 <= ye2 = True
    | xs1 >= xs2 && xs1 <= xe2 && ye1 >= ys2 && ye1 <= ye2 = True
    | xe1 >= xs2 && xe1 <= xe2 && ye1 >= ys2 && ye1 <= ye2 = True
    | xe1 >= xs2 && xe1 <= xe2 && ys1 >= ys2 && ys1 <= ye2 = True

    -- any part of second is inside of the first 
    | xs2 >= xs1 && xs2 <= xe1 && ys2 >= ys1 && ys2 <= ye1 = True
    | xs2 >= xs1 && xs2 <= xe1 && ye2 >= ys1 && ye2 <= ye1 = True
    | xe2 >= xs1 && xe2 <= xe1 && ye2 >= ys1 && ye2 <= ye1 = True
    | xe2 >= xs1 && xe2 <= xe1 && ys2 >= ys1 && ys2 <= ye1 = True

    -- rectangles make cross
    | xs1 <= xs2 && xe1 >= xe2 && ys2 <= ys1 && ye2 >= ye1 = True 
    | xs2 <= xs1 && xe2 >= xe1 && ys1 <= ys2 && ye1 >= ye2 = True 

    | otherwise                                            = False

can_fall :: Block -> Block -> Bool
can_fall higher lower 
    | (snd (z lower)) == (fst (z higher) - 1) && (area_intersect (x lower) (y lower) (x higher) (y higher)) = False
    | otherwise                                                                                             = True

---------------- Parsing ---------------

parse :: String -> [Block]
parse = map parse_line . lines 

parse_line :: String -> Block
parse_line line = Block { x = (start_x, end_x), y = (start_y, end_y), z = (start_z, end_z) }
    where
        [first_part, second_part]   = words $ map (\x -> if x == '~' then ' ' else x) line
        [start_x, start_y, start_z] = map (\x -> read x :: Int) $ words $ map (\x -> if x == ',' then ' ' else x) first_part 
        [end_x,   end_y,   end_z  ] = map (\x -> read x :: Int) $ words $ map (\x -> if x == ',' then ' ' else x) second_part

----------------- Solve ----------------

solve :: [Block] -> Int
solve blocks = result  
    where
        sorted_blocks  = sortBy (\b1 b2 -> compare (fst $ z b1) (fst $ z b2)) blocks
        result = stack_blocks (fromList []) (fromList []) [] sorted_blocks 

stack_blocks :: Set Block -> Set Block -> [Block] -> [Block] -> Int
stack_blocks non_removable_blocks removable_blocks stacked_blocks []             = size (difference removable_blocks non_removable_blocks) + (roof_size [] stacked_blocks)
stack_blocks non_removable_blocks removable_blocks stacked_blocks (higher:blocks) 
    | (fst $ z higher) == 1                = stack_blocks non_removable_blocks  removable_blocks (higher:stacked_blocks) blocks
    | all (can_fall higher) stacked_blocks = stack_blocks non_removable_blocks  removable_blocks stacked_blocks (higher { z = ((fst $ z higher) - 1, (snd $ z higher) - 1) } : blocks) 
    | otherwise                            = stack_blocks unon_removable_blocks uremovable_blocks (higher:stacked_blocks) blocks
    where
        new_removable_blocks  = filter (not . can_fall higher) stacked_blocks
        uremovable_blocks     = if length new_removable_blocks > 1  then union removable_blocks $ fromList new_removable_blocks     else removable_blocks
        unon_removable_blocks = if length new_removable_blocks == 1 then union non_removable_blocks $ fromList new_removable_blocks else non_removable_blocks

roof_size :: [Block] -> [Block] -> Int
roof_size _           []                     = 0
roof_size done_blocks (block:stacked_blocks)
    | not $ any (\oblock -> (snd (z block) + 1) == (fst (z oblock)) && (area_intersect (x block) (y block) (x oblock) (y oblock))) all_blocks = 1 + roof_size (block:done_blocks) stacked_blocks
    | otherwise                                                                                                                               =     roof_size (block:done_blocks) stacked_blocks
        where
            all_blocks = done_blocks ++ stacked_blocks

------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution
