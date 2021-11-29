import Data.Ix
import qualified Data.Set as Set

parseLines :: [String] -> Set.Set (Int, Int, Int)
parseLines ls = foldl1 (Set.union) . map (parseLine) $ zip ls [0..]
  where parseLine (l,y) = Set.fromList [(x, y, 0) | (x, c) <- zip [0..] l,
                                                    c == '#']

trans :: (Int, Int, Int) -> Set.Set (Int, Int, Int) -> Set.Set (Int, Int, Int)
trans (dx, dy, dz) active = Set.fromList [(x, y, z) | x <- [-dx..dx],
                                                      y <- [-dy..dy],
                                                      z <- [-dz..dz],
                                                      isActive (x, y, z)]
  where
    isActive p@(x, y, z)
      | p `Set.member` active = inRange (2, 3) $ actNeigh (x, y, z)
      | otherwise             = actNeigh (x, y, z) == 3
    actNeigh = length . filter (`Set.member` active) . neigh
    neigh p@(x, y, z) = [(x + x', y + y', z + z') | x' <- [-1..1],
                                                    y' <- [-1..1],
                                                    z' <- [-1..1],
                                                    x' /= 0 || y' /= 0 || z' /= 0]


solve :: (Int, Int, Int) -> Int -> Set.Set (Int, Int, Int) -> Int
solve _ 0 active           = length active
solve d@(x, y, z) n active = solve (x + 1, y + 1, z + 1) (n - 1) $ trans d active

main :: IO ()
main = getContents >>= print . solve (9, 9, 1) 6 . parseLines . lines
