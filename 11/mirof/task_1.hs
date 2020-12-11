import Data.List.Split
import Data.Maybe

main :: IO ()
main = readFile "problem_1.txt" >>= getOccupiedSeats . parseInputData >>= putStrLn . show

parseInputData :: String -> [[String]]
parseInputData = map (filter (/="") . splitOn "") . lines

getOccupiedSeats :: [[String]] -> IO Int
getOccupiedSeats matrix
    | newMatrix == matrix = print "a" >> return (countOccupiedSeats matrix)
    | otherwise           = print "a" >> getOccupiedSeats newMatrix
        where newMatrix = getNewMatrix matrix

countOccupiedSeats :: [[String]] -> Int
countOccupiedSeats = length . filter (=="#") . concat

getNewMatrix :: [[String]] -> [[String]]
getNewMatrix matrix = newMatrix
    where rowLength     = length matrix
          columnLength  = length (matrix !! 0)
          newMatrixList = getNewMatrix' matrix [(i, j) | i <- [0,1..(rowLength - 1)], j <- [0,1..(columnLength - 1)]]
          newMatrix = listToMatrix newMatrixList rowLength

listToMatrix :: [String] -> Int -> [[String]]
listToMatrix [] _ = []
listToMatrix list rowLength = [take rowLength list] ++ (listToMatrix (drop rowLength list) rowLength)

getNewMatrix' :: [[String]] -> [(Int, Int)] -> [String]
getNewMatrix' matrix []                = []
getNewMatrix' matrix ((i, j):indecies)
    | element == "L" && conditionFreeToTaken matrix i j = ["#"] ++ getNewMatrix' matrix indecies
    | element == "#" && conditionTakenToFree matrix i j = ["L"] ++ getNewMatrix' matrix indecies
    | otherwise = [element] ++ getNewMatrix' matrix indecies
        where element = ((matrix !! i) !! j)

getAdjcentElements :: [[String]] -> Int -> Int -> [String]
getAdjcentElements matrix i j = map fromJust $ filter (/=Nothing) [upLeft, up, upRight, middleLeft, middleRight, downLeft, down, downRight]
    where upLeft      = getElem matrix (i-1) (j-1)
          up          = getElem matrix (i-1) (j)
          upRight     = getElem matrix (i-1) (j+1)
          middleLeft  = getElem matrix (i) (j-1)
          middleRight = getElem matrix (i) (j+1)
          downLeft    = getElem matrix (i+1) (j-1)
          down        = getElem matrix (i+1) (j)
          downRight   = getElem matrix (i+1) (j+1)

getElem :: [[String]] -> Int -> Int -> Maybe String
getElem matrix i j
    |  i >= 0 && j >= 0 && i < length matrix && j < length (matrix !! i) = Just ((matrix !! i) !! j)
    | otherwise                                      = Nothing

conditionFreeToTaken matrix i j = ((length $ filter (=="#") $ getAdjcentElements matrix i j) == 0)
conditionTakenToFree matrix i j = ((length $ filter (=="#") $ getAdjcentElements matrix i j) >= 4)


