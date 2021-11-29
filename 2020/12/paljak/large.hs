import Data.List
import Data.Maybe

rot :: (Int, Int) -> (Int, Int) -> Int -> (Int, Int)
rot (x, y) (cx, cy) 0   = (x, y)
rot (x, y) (cx, cy) deg = rot (cx * y, cy * x) (cx, cy) (deg - 90)

move :: (Int, Int, Int, Int) -> [String] -> (Int, Int, Int, Int)
move pos = foldl' (makeMove) pos
  where
    makeMove (x, y, dx, dy) ('N':a) = (x, y, dx, dy + read a)
    makeMove (x, y, dx, dy) ('E':a) = (x, y, dx + read a, dy)
    makeMove (x, y, dx, dy) ('S':a) = (x, y, dx, dy - read a)
    makeMove (x, y, dx, dy) ('W':a) = (x, y, dx - read a, dy)
    makeMove (x, y, dx, dy) ('F':a) = (x + read a * dx, y + read a * dy, dx, dy)
    makeMove (x, y, dx, dy) ('L':a) = (x, y, fst p, snd p)
      where p = rot (dx, dy) (-1, 1) (read a)
    makeMove (x, y, dx, dy) ('R':a) = (x, y, fst p, snd p)
      where p = rot (dx, dy) (1, -1) (read a)

dist :: [String] -> Int
dist moves = manhattan pos
  where
    manhattan (x, y, _, _) = abs x + abs y
    pos = move (0, 0, 10, 1) moves

main :: IO ()
main = getContents >>= print . dist . lines
