import Data.List
import Data.Maybe

turn :: Char -> Int -> Int -> Char
turn heading coef deg = "NESW" !! j
  where
    i = fromJust $ find (\x -> "NESW" !! x == heading) [0..3]
    j = (i + coef * ((deg `div` 90) `mod` 4) + 4) `mod` 4

move :: (Int, Int, Char) -> [String] -> (Int, Int, Char)
move pos = foldl' (makeMove) pos
  where
    makeMove (x, y, dir) ('N':a) = (x, y + read a, dir)
    makeMove (x, y, dir) ('E':a) = (x + read a, y, dir)
    makeMove (x, y, dir) ('S':a) = (x, y - read a, dir)
    makeMove (x, y, dir) ('W':a) = (x - read a, y, dir)
    makeMove (x, y, dir) ('F':a) = makeMove (x, y, dir) (dir:a)
    makeMove (x, y, dir) ('L':a) = (x, y, turn dir (-1) $ read a)
    makeMove (x, y, dir) ('R':a) = (x, y, turn dir 1 $ read a)

dist :: [String] -> Int
dist moves = manhattan pos
  where
    manhattan (x, y, _) = abs x + abs y
    pos = move (0, 0, 'E') moves

main :: IO ()
main = getContents >>= print . dist . lines
