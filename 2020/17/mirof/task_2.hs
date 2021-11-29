import Data.List.Split
import Data.List
import qualified Data.Set as S

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . countActiveSquares 6 . parseInputData

----------------------------------------------------------------------------------------------------
------------------------------------------ PARSING -------------------------------------------------
----------------------------------------------------------------------------------------------------

parseInputData :: String -> S.Set (Int, Int, Int, Int)
parseInputData = S.fromList . map tupleToQuad . concat . map listToTupleIndex . zip [0,1..] . map (matchIndeces '#') . lines
    where tupleToQuad (x, y) = (x, y, 0, 0)
          singleToTuple x y    = (x, y)
          listToTupleIndex (x, ys) = map (singleToTuple x) ys


matchIndeces :: Char -> [Char] -> [Int]
matchIndeces char chars = matchIndeces' 0 char chars

matchIndeces' :: Int -> Char -> [Char] -> [Int]
matchIndeces' _     _    []               = []
matchIndeces' index char (currChar:chars)
    | char == currChar = [index] ++ matchIndeces' (index + 1) char chars
    | otherwise        =            matchIndeces' (index + 1) char chars

----------------------------------------------------------------------------------------------------
------------------------------------------- LOGIC --------------------------------------------------
----------------------------------------------------------------------------------------------------

countActiveSquares :: Int -> S.Set (Int, Int, Int, Int) -> Int
countActiveSquares 0      activeSquares = length activeSquares
countActiveSquares cycles activeSquares = countActiveSquares (cycles - 1) newAllActiveSquares
    where newAllActiveSquares    = S.union remainingActiveSquares newActiveSquares
          remainingActiveSquares = findRemainingActiveSquares activeSquares
          newActiveSquares       = findNewActiveSquares activeSquares

neighbourIndices :: (Int, Int, Int, Int) -> S.Set (Int, Int, Int, Int)
neighbourIndices (i, j, k, l) = S.fromList [(x, y, z, t) | x <- [i-1, i, i+1],
                                                     y <- [j-1, j, j+1],
                                                     z <- [k-1, k, k+1],
                                                     t <- [l-1, l, l+1],
                                                     (x, y, z, t) /= (i, j, k, l)]

findRemainingActiveSquares :: S.Set (Int, Int, Int, Int) -> S.Set (Int, Int, Int, Int)
findRemainingActiveSquares activeSquares = S.filter (neighbourActivityCondition) activeSquares
    where neighbourActivityCondition square = activeNeighbours square == 2 || activeNeighbours square == 3
          activeNeighbours square = length $ S.filter (\x -> S.member x activeSquares) (neighbourIndices square)

findNewActiveSquares :: S.Set (Int, Int, Int, Int) -> S.Set (Int, Int, Int, Int)
findNewActiveSquares activeSquares = S.filter neighbourActivityCondition inactiveSquares
    where inactiveSquares = S.filter (\x -> not $ S.member x activeSquares) $ S.foldl S.union S.empty $ S.map neighbourIndices activeSquares
          neighbourActivityCondition square = activeNeighbours square == 3
          activeNeighbours square = length $ S.filter (\x -> S.member x activeSquares) (neighbourIndices square)

