import Data.Ix
import qualified Data.Set as Set

parseLines :: [String] -> Set.Set (Int, Int, Int, Int)
parseLines ls = foldl1 (Set.union) . map (parseLine) $ zip ls [0..]
  where parseLine (l, y) = Set.fromList [(x, y, 0, 0) | (x, c) <- zip [0..] l,
                                                        c == '#']

trans :: (Int, Int, Int, Int) -> Set.Set (Int, Int, Int, Int) -> Set.Set (Int, Int, Int, Int)
trans (dx, dy, dz, dw) active = Set.fromList [(x, y, z, w) | x <- [-dx..dx],
                                                             y <- [-dy..dy],
                                                             z <- [-dz..dz],
                                                             w <- [-dw..dw],
                                                             isActive (x, y, z, w)]
  where
    isActive p@(x, y, z, w)
      | p `Set.member` active = inRange (2, 3) $ actNeigh (x, y, z, w)
      | otherwise             = actNeigh (x, y, z, w) == 3
    actNeigh = length . filter (`Set.member` active) . neigh
    neigh p@(x, y, z, w) = [(x + x', y + y', z + z', w + w') | x' <- [-1..1],
                                                               y' <- [-1..1],
                                                               z' <- [-1..1],
                                                               w' <- [-1..1],
                                                               x' /= 0 || y' /= 0 || z' /= 0 || w' /= 0]


solve :: (Int, Int, Int, Int) -> Int -> Set.Set (Int, Int, Int, Int) -> Int
solve _ 0 active              = length active
solve d@(x, y, z, w) n active = solve (x + 1, y + 1, z + 1, w + 1) (n - 1) $ trans d active

main :: IO ()
main = getContents >>= print . solve (9, 9, 1, 1) 6 . parseLines . lines
