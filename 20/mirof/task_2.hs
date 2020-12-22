import Data.List
import Data.List.Split
import Data.Maybe
import qualified Data.Map as M
import qualified Data.Matrix as Mat
import qualified Data.Vector as V

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . findMonsters . flipImage . rotateLeftImage . rotateLeftImage . rotateLeftImage . imageMatrix . map (\(x, y, z) -> (y, z)) . makeImage . parseInputData

-- example
-- firstTile    = 1951
-- imageSize    = 3
-- fragmentSize = 10

-- problem_2
-- [2161,2753,2927,1201]
firstTile    = 2161
imageSize    = 12
fragmentSize = 10
-- rightDownCorner = 2927

----------------------------------------------------------------------------------------------------
------------------------------------------ PARSING -------------------------------------------------
----------------------------------------------------------------------------------------------------

parseInputData :: String -> M.Map Int (Mat.Matrix Char)
parseInputData = M.fromList . map parseMatrix . map lines . splitOn "\n\n"

parseMatrix :: [String] -> (Int, Mat.Matrix Char)
parseMatrix matrixLines = (read $ init $ last $ words $ head matrixLines, Mat.fromLists $ tail matrixLines)

----------------------------------------------------------------------------------------------------
------------------------------------------- LOGIC --------------------------------------------------
----------------------------------------------------------------------------------------------------

findMonsters :: Mat.Matrix Char -> Int -- Mat.Matrix Char
findMonsters input = otherPos - monsterPos
    where indicies = [(x, y) | x <- [0..120], y <- [0..120]]
          numberOfMonsters = length $ filter (==True) $ map (\x -> isMonster x input) indicies
          monsterPos = numberOfMonsters * 15
          otherPos   = length $ filter (=='#') $ Mat.toList input

isMonster :: (Int, Int) -> Mat.Matrix Char -> Bool
isMonster (x, y) input = (length $ filter (==(Just '#')) elems) == 15
    where elem1  = Mat.safeGet (x) (y) input
          elem2  = Mat.safeGet (x+1) (y+1) input
          elem3  = Mat.safeGet (x+1) (y+4) input
          elem4  = Mat.safeGet (x) (y+5) input
          elem5  = Mat.safeGet (x) (y+6) input
          elem6  = Mat.safeGet (x+1) (y+7) input
          elem7  = Mat.safeGet (x+1) (y+10) input
          elem8  = Mat.safeGet (x) (y+11) input
          elem9  = Mat.safeGet (x) (y+12) input
          elem10 = Mat.safeGet (x+1) (y+13) input
          elem11 = Mat.safeGet (x+1) (y+16) input
          elem12 = Mat.safeGet (x) (y+17) input
          elem13 = Mat.safeGet (x) (y+18) input
          elem14 = Mat.safeGet (x-1) (y+18) input
          elem15 = Mat.safeGet (x) (y+19) input
          elems = [elem1,elem2,elem3,elem4,elem5,elem6,elem7,elem8,elem9,elem10,elem11,elem12,elem13,elem14,elem15]



imageMatrix :: [((Int, Int), Mat.Matrix Char)] -> Mat.Matrix Char
imageMatrix input = Mat.fromLists $ map (\(x, y) -> makeLine input x y) [(x, y) | y <- [0..11], x <- [1..8]]

makeLine input smallLine bigLine  = concat $ map (\x -> init $ tail $ (x !! smallLine)) $  map (\(_, x) -> Mat.toLists x) $ filter (\(x, _) -> fst x == (bigLine)) input


makeImage :: M.Map Int (Mat.Matrix Char) -> [(Int, (Int, Int), Mat.Matrix Char)]
makeImage inputMatricies = (nub solution) ++ [(2927, (11, 11), fromJust $ M.lookup 2927 inputMatricies)]
    where currentMatrix = Main.flip $ fromJust $ M.lookup firstTile inputMatricies
          solution      = (firstTile, (0, 0), currentMatrix) : makeImage' (0, 0) (filter ((/=firstTile) . fst) $ M.toList inputMatricies) currentMatrix

makeImage' :: (Int, Int) -> [(Int, Mat.Matrix Char)] -> Mat.Matrix Char -> [(Int, (Int, Int), Mat.Matrix Char)]
makeImage' (11, _) _         _             = []
makeImage' (_, 11) _         _             = []
makeImage' (x, y) matricies currentMatrix = solution ++ recSolution
    where (rTile, rightN) = fromJust $ head $ filter (/=Nothing) $ map (rightNeighbour currentMatrix) matricies
          (dTile, downN)  = fromJust $ head $ filter (/=Nothing) $ map (downNeighbour  currentMatrix) matricies
          newMatricies    = filter ((/=dTile) . fst) $ filter ((/=rTile) . fst) matricies
          solution        = [(rTile, (x, y+1), rightN), (dTile, (x+1, y), downN)]
          recRight        = if x == 0 && y < fragmentSize then makeImage' (x, y+1) newMatricies rightN else []
          recDown         = makeImage' (x+1, y) newMatricies downN
          recSolution     = recDown ++ recRight

rightNeighbour :: Mat.Matrix Char -> (Int, Mat.Matrix Char) -> Maybe (Int, Mat.Matrix Char)
rightNeighbour currentMatrix (tile, potentialNeighbour) = if length neighbours == 1 then Just (head neighbours) else Nothing
    where rotationsTransformations     = [id, rotateLeft, rotateLeft . rotateLeft, rotateLeft . rotateLeft . rotateLeft]
          rotationsFlipTransfomrations = [Main.flip, Main.flip . rotateLeft, Main.flip . rotateLeft . rotateLeft, Main.flip . rotateLeft . rotateLeft . rotateLeft]
          transformations              = rotationsTransformations ++ rotationsFlipTransfomrations
          allMatricies                 = map (\f -> (tile, f potentialNeighbour)) transformations
          neighbours                   = filter (\(_, matrix) -> Mat.getCol fragmentSize currentMatrix == Mat.getCol 1 matrix) allMatricies

downNeighbour :: Mat.Matrix Char -> (Int, Mat.Matrix Char) -> Maybe (Int, Mat.Matrix Char)
downNeighbour currentMatrix (tile, potentialNeighbour) = if length neighbours == 1 then Just (head neighbours) else Nothing
    where rotationsTransformations     = [id, rotateLeft, rotateLeft . rotateLeft, rotateLeft . rotateLeft . rotateLeft]
          rotationsFlipTransfomrations = [Main.flip, Main.flip . rotateLeft, Main.flip . rotateLeft . rotateLeft, Main.flip . rotateLeft . rotateLeft . rotateLeft]
          transformations              = rotationsTransformations ++ rotationsFlipTransfomrations
          allMatricies                 = map (\f -> (tile, f potentialNeighbour)) transformations
          neighbours                   = filter (\(_, matrix) -> Mat.getRow fragmentSize currentMatrix == Mat.getRow 1 matrix) allMatricies

----------------------------------------------------------------------------------------------------
------------------------------------- MATRIX OPERATIONS --------------------------------------------
----------------------------------------------------------------------------------------------------

rotateLeftImage :: Mat.Matrix Char -> Mat.Matrix Char
rotateLeftImage = Mat.fromLists . rotateLeftImage' 96

rotateLeftImage' :: Int -> Mat.Matrix Char -> [[Char]]
rotateLeftImage' 0   matrix = []
rotateLeftImage' col matrix = [(V.toList (Mat.getCol col matrix))] ++ rotateLeftImage' (col - 1) matrix


rotateLeft :: Mat.Matrix Char -> Mat.Matrix Char
rotateLeft = Mat.fromLists . rotateLeft' fragmentSize

rotateLeft' :: Int -> Mat.Matrix Char -> [[Char]]
rotateLeft' 0   matrix = []
rotateLeft' col matrix = [(V.toList (Mat.getCol col matrix))] ++ rotateLeft' (col - 1) matrix

flipImage :: Mat.Matrix Char ->  Mat.Matrix Char
flipImage = rotateLeftImage . rotateLeftImage . rotateLeftImage . Mat.transpose

flip :: Mat.Matrix Char ->  Mat.Matrix Char
flip = rotateLeft . rotateLeft . rotateLeft . Mat.transpose

