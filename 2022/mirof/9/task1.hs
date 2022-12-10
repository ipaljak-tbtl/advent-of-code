import qualified Data.Set as Set
import Text.Read

data Rope = Rope {
    headPosition :: (Int, Int),
    tailPosition :: (Int, Int),
    tailPositionHistory :: [(Int, Int)]
}

initRope :: Rope
initRope = Rope { headPosition = (0, 0), tailPosition = (0, 0), tailPositionHistory = [(0, 0)] }

moveHead :: Rope -> (Char, Int) -> Rope
moveHead rope (_, 0) = rope

moveHead rope ('L', steps) = moveHead Rope { headPosition = newHeadPosition, tailPosition = newTailPosition, tailPositionHistory = newTailPosition : (tailPositionHistory rope) } ('L', steps - 1)
    where
        newHeadPosition = app1 (\x -> x - 1) (headPosition rope)
        newTailPosition = if connected newHeadPosition (tailPosition rope) then tailPosition rope else headPosition rope

moveHead rope ('R', steps) = moveHead Rope { headPosition = newHeadPosition, tailPosition = newTailPosition, tailPositionHistory = newTailPosition : (tailPositionHistory rope) } ('R', steps - 1)
    where
        newHeadPosition = app1 (+1) (headPosition rope)
        newTailPosition = if connected newHeadPosition (tailPosition rope) then tailPosition rope else headPosition rope

moveHead rope ('U', steps) = moveHead Rope { headPosition = newHeadPosition, tailPosition = newTailPosition, tailPositionHistory = newTailPosition : (tailPositionHistory rope) } ('U', steps - 1)
    where
        newHeadPosition = app2 (+1) (headPosition rope)
        newTailPosition = if connected newHeadPosition (tailPosition rope) then tailPosition rope else headPosition rope

moveHead rope ('D', steps) = moveHead Rope { headPosition = newHeadPosition, tailPosition = newTailPosition, tailPositionHistory = newTailPosition : (tailPositionHistory rope) } ('D', steps - 1)
    where
        newHeadPosition = app2 (\x -> x - 1) (headPosition rope)
        newTailPosition = if connected newHeadPosition (tailPosition rope) then tailPosition rope else headPosition rope

app1 :: (Int -> Int) -> (Int, Int) -> (Int, Int)
app1 operator (x, y)  = (operator x, y)

app2 :: (Int -> Int) -> (Int, Int) -> (Int, Int)
app2 operator (x, y)  = (x, operator y)

connected :: (Int, Int) -> (Int, Int) -> Bool
connected (x1, y1) (x2, y2) = (abs (x1 - x2) <= 1) && (abs (y1 - y2) <= 1)

main = do
    input <- readFile "input.txt"
    let solution = (solve . parse) input
    putStrLn $ show solution

parse :: String -> [(Char, Int)]
parse = map (\(c:' ':num) -> (c, readInt num)) . lines

readInt :: String -> Int
readInt input = read input :: Int

solve :: [(Char, Int)] -> Int
solve directions = length $ Set.fromList $ tailPositionHistory $ foldl moveHead initRope directions

