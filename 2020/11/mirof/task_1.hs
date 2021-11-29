import Data.List.Split
import Data.Maybe
import Data.Matrix

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . getOccupiedSeats . fromLists . lines

getOccupiedSeats :: Matrix Char -> Int
getOccupiedSeats matrix
    | newMatrix == matrix = countOccupiedSeats matrix
    | otherwise           = getOccupiedSeats newMatrix
        where newMatrix = getNewMatrix matrix

countOccupiedSeats :: Matrix Char -> Int
countOccupiedSeats = length . filter (=='#') . toList

getNewMatrix :: Matrix Char -> Matrix Char
getNewMatrix matrix = fromList rowLength columnLength newMatrixList
    where rowLength = length $ getCol 1 matrix
          columnLength = length $ getRow 1 matrix
          newMatrixList = getNewMatrix' matrix [(i, j) | i <- [1,2..(rowLength)], j <- [1,2..(columnLength)]]

getNewMatrix' :: Matrix Char -> [(Int, Int)] -> String
getNewMatrix' _ []                = []
getNewMatrix' matrix ((i, j):indices)
    | element == 'L' && conditionFreeToTaken matrix i j = '#' : getNewMatrix' matrix indices
    | element == '#' && conditionTakenToFree matrix i j = 'L' : getNewMatrix' matrix indices
    | otherwise = element : getNewMatrix' matrix indices
        where element = getElem i j matrix

getAdjcentElements :: Matrix Char -> Int -> Int -> String
getAdjcentElements matrix i j = map fromJust $ filter (/=Nothing) [upLeft, up, upRight, middleLeft, middleRight, downLeft, down, downRight]
    where upLeft      = safeGet (i-1) (j-1) matrix
          up          = safeGet (i-1) (j)   matrix
          upRight     = safeGet (i-1) (j+1) matrix
          middleLeft  = safeGet (i) (j-1)   matrix
          middleRight = safeGet (i) (j+1)   matrix
          downLeft    = safeGet (i+1) (j-1) matrix
          down        = safeGet (i+1) (j)   matrix
          downRight   = safeGet (i+1) (j+1) matrix

conditionFreeToTaken matrix i j = ((length $ filter (=='#') $ getAdjcentElements matrix i j) == 0)
conditionTakenToFree matrix i j = ((length $ filter (=='#') $ getAdjcentElements matrix i j) >= 4)

