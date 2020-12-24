import Data.List
import Data.Maybe

n = 100

parseLines :: String -> [Int]
parseLines = map (read . (:[]))

move :: (Int, [Int]) -> (Int, [Int])
move (i, xs) = (i', xs')
  where
    taken   = [xs !! (add 1 i), xs !! (add 2 i), xs !! (add 3 i)]
    rest    = filter (`notElem` taken) xs
    dest    = fromJust . find (`notElem` taken) $ map (\d -> 1 + add (xs !! i) (-d)) [2..]
    destId  = fromJust $ find (\i -> (rest !! i) == dest) [0..]
    left    = take (destId + 1) rest
    right   = drop (destId + 1) rest
    xs'     = left ++ taken ++ right
    i'      = fromJust $ find (\j -> (xs' !! j) == (xs !! (add 4 i))) [0..]
    add a b = (a + b + (length xs)) `mod` (length xs)

solve :: [Int] -> [Int]
solve l = snd $ iterate (move) (0, l) !! n

main :: IO ()
main = getContents >>= print . solve . parseLines . head . lines
