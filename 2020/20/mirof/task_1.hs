import Data.List.Split
import Data.List
import qualified Data.Matrix as M
import qualified Data.Vector as V

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . solve . parseInputData

imageSize    = 12
fragmentSize = 10

----------------------------------------------------------------------------------------------------
------------------------------------------ PARSING -------------------------------------------------
----------------------------------------------------------------------------------------------------

parseInputData :: String -> [(String, M.Matrix Char)]
parseInputData = map parseMatrix . map lines . splitOn "\n\n"

parseMatrix :: [String] -> (String, M.Matrix Char)
parseMatrix matrixLines = (head matrixLines, M.fromLists $ tail matrixLines)

----------------------------------------------------------------------------------------------------
------------------------------------------- LOGIC --------------------------------------------------
----------------------------------------------------------------------------------------------------

solve :: [(String, M.Matrix Char)] -> [Int]
solve = map read . map (\x -> init $ (words x) !! 1)  . map (fst . fst . head) . filter (\(l) -> length l == 2) . checkAll (imageSize * imageSize)

checkAll :: Int -> [(String, M.Matrix Char)] -> [[((String, String), ([([Bool], (Int, Bool))]))]]
checkAll 0         _ = []
checkAll remaining input @ (matrix:matricies) = allTilePairs input : checkAll (remaining - 1) (matricies ++ [matrix])

allTilePairs :: [(String, M.Matrix Char)] -> [((String, String), ([([Bool], (Int, Bool))]))]
allTilePairs (matrix:matricies) = filteredAllBorders
    where allBorders = countAllMatchingBorders matrix matricies
          filteredAllBorders = filter (not . null . snd) $ map (\(ss, l) -> (ss, filter (\(bools, _) -> any (==True) bools) l)) allBorders

countAllMatchingBorders :: (String, M.Matrix Char) -> [(String, M.Matrix Char)] -> [((String, String), [([Bool], (Int, Bool))])]
countAllMatchingBorders _           []                        = []
countAllMatchingBorders (fixedTile, fixedMatrix) ((currentTile, currentMatrix):matricies) = ((fixedTile, currentTile), countMatches fixedMatrix currentMatrix) : countAllMatchingBorders (fixedTile, fixedMatrix) matricies

countMatches :: M.Matrix Char -> M.Matrix Char -> [([Bool], (Int, Bool))]
countMatches fixedMatrix matrix = countMatches' (0, False) fixedMatrix matrix

countMatches' :: (Int, Bool) -> M.Matrix Char -> M.Matrix Char -> [([Bool], (Int, Bool))]
countMatches' (8, True)         _           _        = []
countMatches' (rotations, isFlip) fixedMatrix matrix = (matches, (rotations `mod` 4, isFlip)) : countMatches' (rotations + 1, (rotations + 1) >= 4) fixedMatrix matrix
    where matches = doesMatch (rotations `mod` 4, isFlip) fixedMatrix matrix

-- [Up, Left, Down, Right] from fixedMatrix after transformations
doesMatch :: (Int, Bool) -> M.Matrix Char -> M.Matrix Char -> [Bool]
doesMatch (0, False)         fixedMatrix matrix = [up, left, down, right]
    where up    = if M.getCol 1 fixedMatrix ==  M.getCol fragmentSize matrix      then True else False
          left  = if M.getRow 1 fixedMatrix ==  M.getRow fragmentSize matrix      then True else False
          down  = if M.getCol 1 matrix      ==  M.getCol fragmentSize fixedMatrix then True else False
          right = if M.getRow 1 matrix      ==  M.getRow fragmentSize fixedMatrix then True else False
doesMatch (rotations, True)  fixedMatrix matrix = doesMatch (rotations,     False) (Main.flip fixedMatrix)  matrix
doesMatch (rotations, False) fixedMatrix matrix = doesMatch (rotations - 1, False) (rotateLeft fixedMatrix) matrix

----------------------------------------------------------------------------------------------------
------------------------------------- MATRIX OPERATIONS --------------------------------------------
----------------------------------------------------------------------------------------------------
rotateLeft :: M.Matrix Char -> M.Matrix Char
rotateLeft = M.fromLists . rotateLeft' fragmentSize

rotateLeft' :: Int -> M.Matrix Char -> [[Char]]
rotateLeft' 0   matrix = []
rotateLeft' col matrix = [(V.toList (M.getCol col matrix))] ++ rotateLeft' (col - 1) matrix

flip :: M.Matrix Char ->  M.Matrix Char
flip = rotateLeft . rotateLeft . rotateLeft . M.transpose

