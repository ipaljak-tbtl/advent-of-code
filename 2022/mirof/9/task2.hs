import qualified Data.Set as Set
import Text.Read

data Rope = Rope {
    nodes       :: [(Int, Int)],
    tailHistory :: [(Int, Int)]
} deriving (Show)

initRope :: Rope
initRope = Rope { nodes = (take 10 . repeat) (0, 0), tailHistory = [] }

main = do
    input <- readFile "input.txt"
    let solution = (solve . parse) input
    putStrLn $ show solution

parse :: String -> [(Char, Int)]
parse = map (\(c:' ':num) -> (c, readInt num)) . lines

readInt :: String -> Int
readInt input = read input :: Int

solve :: [(Char, Int)] -> Int
solve directions = length $ Set.fromList $ tailHistory $ foldl moveHead initRope directions

moveHead :: Rope -> (Char, Int) -> Rope
moveHead rope (_, 0)             = rope
moveHead rope (direction, steps)
    | direction == 'U' = moveHead (updateRope rope incY) (direction, steps - 1)
    | direction == 'D' = moveHead (updateRope rope decY) (direction, steps - 1)
    | direction == 'L' = moveHead (updateRope rope decX) (direction, steps - 1)
    | direction == 'R' = moveHead (updateRope rope incX) (direction, steps - 1)

updateRope :: Rope -> ((Int, Int) -> (Int, Int)) -> Rope
updateRope Rope { nodes = (node:nodes), tailHistory = tailHistory } operator = Rope { nodes = newNode : newNodes, tailHistory = newTailHistory }
    where
        newNode        = operator node
        newNodes       = updateNodes node newNode nodes
        newTailHistory = (last newNodes) : tailHistory

updateNodes :: (Int, Int) -> (Int, Int) -> [(Int, Int)] -> [(Int, Int)]
updateNodes _            _            []           = []
updateNodes oldFrontNode newFrontNode (node:nodes)
    | connected newFrontNode node = node    : updateNodes node node    nodes
    | otherwise                   = newNode : updateNodes node newNode nodes
        where
            newNode = (fst node + (signum (fst newFrontNode - fst node)), snd node + (signum (snd newFrontNode - snd node)))

connected :: (Int, Int) -> (Int, Int) -> Bool
connected (x1, y1) (x2, y2) = (abs (x1 - x2) <= 1) && (abs (y1 - y2) <= 1)

incX :: (Int, Int) -> (Int, Int)
incX (x, y) = (x + 1, y    )

incY :: (Int, Int) -> (Int, Int)
incY (x, y) = (x    , y + 1)

decX :: (Int, Int) -> (Int, Int)
decX (x, y) = (x - 1, y    )

decY :: (Int, Int) -> (Int, Int)
decY (x, y) = (x    , y - 1)

