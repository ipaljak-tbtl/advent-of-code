import Data.List.Split
import Data.Maybe
import Data.Matrix

main :: IO ()
main = readFile "problem_2.txt" >>= putStrLn . show . getOccupiedSeats . fromLists . lines

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
    where upLeft      = getIfExist (i-1) (j-1) (-1) (-1) matrix
          up          = getIfExist (i-1) (j)   (-1) (0)    matrix
          upRight     = getIfExist (i-1) (j+1) (-1) (1) matrix
          middleLeft  = getIfExist (i) (j-1)   (0) (-1)matrix
          middleRight = getIfExist (i) (j+1)   (0) (1) matrix
          downLeft    = getIfExist (i+1) (j-1) (1) (-1) matrix
          down        = getIfExist (i+1) (j)   (1) (0) matrix
          downRight   = getIfExist (i+1) (j+1) (1) (1) matrix

getIfExist :: Int -> Int -> Int -> Int -> Matrix Char -> Maybe Char
getIfExist i j di dj matrix
    | safeGet i j matrix == Just '#' = Just '#'
    | safeGet i j matrix == Just 'L' = Just 'L'
    | safeGet i j matrix == Nothing  = Nothing
    | otherwise               = getIfExist (i + di) (j + dj) di dj matrix

conditionFreeToTaken matrix i j = ((length $ filter (=='#') $ getAdjcentElements matrix i j) == 0)
conditionTakenToFree matrix i j = ((length $ filter (=='#') $ getAdjcentElements matrix i j) >= 5)

