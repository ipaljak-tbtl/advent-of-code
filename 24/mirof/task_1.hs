import qualified Data.Matrix as M
import Data.Maybe

type Path      = [Direction]
data Direction = E | W | SE | SW | NE | NW
    deriving (Show, Eq, Ord)

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . countBlack . parseInputData

----------------------------------------------------------------------------------------------------
------------------------------------------ PARSING -------------------------------------------------
----------------------------------------------------------------------------------------------------

parseInputData :: String -> [Path]
parseInputData = map toDirectionList . lines

toDirectionList :: String -> Path
toDirectionList []             = []
toDirectionList ('s':'e':rest) = SE : toDirectionList rest
toDirectionList ('s':'w':rest) = SW : toDirectionList rest
toDirectionList ('n':'e':rest) = NE : toDirectionList rest
toDirectionList ('n':'w':rest) = NW : toDirectionList rest
toDirectionList ('e'    :rest) = E  : toDirectionList rest
toDirectionList ('w'    :rest) = W  : toDirectionList rest

----------------------------------------------------------------------------------------------------
------------------------------------------- LOGIC --------------------------------------------------
----------------------------------------------------------------------------------------------------

countBlack :: [Path] -> Int
countBlack paths = count
    where matrix = fillMatrix (M.zero 200 200) paths
          count  = length $ filter odd $ filter (/=0) $ M.toList matrix

fillMatrix :: M.Matrix Int -> [Path] -> M.Matrix Int
fillMatrix matrix []           = matrix
fillMatrix matrix (path:paths) = fillMatrix (flipField matrix path (100, 100)) paths

flipField :: M.Matrix Int -> Path -> (Int, Int) -> M.Matrix Int
flipField matrix []        (x, y) = M.setElem ((M.getElem x y matrix) + 1) (x, y) matrix
flipField matrix (E:path)  (x, y) = flipField matrix path (x+1, y  )
flipField matrix (W:path)  (x, y) = flipField matrix path (x-1, y  )
flipField matrix (SE:path) (x, y) = flipField matrix path (x+1, y-1)
flipField matrix (NE:path) (x, y) = flipField matrix path (x,   y+1)
flipField matrix (SW:path) (x, y) = flipField matrix path (x,   y-1)
flipField matrix (NW:path) (x, y) = flipField matrix path (x-1, y+1)


