import qualified Data.Matrix as M
import qualified Data.Map as Map
import qualified Data.Set as S
import Data.Maybe

type Path      = [Direction]
data Direction = E | W | SE | SW | NE | NW
    deriving (Show, Eq, Ord)

main :: IO ()
main = readFile "problem_2.txt" >>= putStrLn . show . countBlack . parseInputData

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
    where startMatrix   = fillMatrix (M.zero 1000 1000) paths
          startMap      = Map.fromList $ map (\(x, _) -> (((x `div` 1000) + 1, (x `mod` 1000) + 1), 1)) $ filter ((==1) . snd) $ zip [0,1..] (M.toList startMatrix)
          dayPassMatrix = changes 100 startMap
          count         = length $ Map.toList dayPassMatrix

changes :: Int -> Map.Map (Int, Int) Int -> Map.Map (Int, Int) Int
changes 0     matrix = matrix
changes count matrix = changes (count - 1) $ ch matrix

ch matrix = newMatrix
    where blackPositions = allBlackPositions matrix
          needToChange   = S.toList $ S.fromList $ filter (\pos -> checkRule pos matrix) blackPositions
          newMatrix      = foldl removeOrAdd matrix needToChange

removeOrAdd mapa key
  | key `Map.member` mapa = Map.delete key mapa
  | otherwise = Map.insert key 1 mapa

checkRule :: (Int, Int) -> Map.Map (Int, Int) Int -> Bool
checkRule (x, y) matrix
  | Map.lookup (x, y) matrix == Just 1 = (black == 0) || (black > 2)
  | otherwise                 = black == 2
    where neighbours = [(x+1, y),(x-1, y),(x+1, y-1),(x, y+1),(x, y-1),(x-1, y+1)]
          black      = length $ filter (\(pos) -> Map.member pos matrix) neighbours


allBlackPositions :: Map.Map (Int, Int) Int -> [(Int, Int)]
allBlackPositions matrix = concat $ map (neighbours) $ map fst (Map.toList matrix)
    where neighbours (x, y) = [(x, y),(x+1, y),(x-1, y),(x+1, y-1),(x, y+1),(x, y-1),(x-1, y+1)]

fillMatrix :: M.Matrix Int -> [Path] -> M.Matrix Int
fillMatrix matrix []           = matrix
fillMatrix matrix (path:paths) = fillMatrix (flipField matrix path (500, 500)) paths

flipField :: M.Matrix Int -> Path -> (Int, Int) -> M.Matrix Int
flipField matrix []        (x, y) = M.setElem (1 - (M.getElem x y matrix)) (x, y) matrix
flipField matrix (E:path)  (x, y) = flipField matrix path (x+1, y  )
flipField matrix (W:path)  (x, y) = flipField matrix path (x-1, y  )
flipField matrix (SE:path) (x, y) = flipField matrix path (x+1, y-1)
flipField matrix (NE:path) (x, y) = flipField matrix path (x,   y+1)
flipField matrix (SW:path) (x, y) = flipField matrix path (x,   y-1)
flipField matrix (NW:path) (x, y) = flipField matrix path (x-1, y+1)

