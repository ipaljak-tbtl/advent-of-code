import Data.List.Split
import Data.List
import Data.Maybe
import qualified Data.Set as S
import qualified Data.Map as M

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . playGame . parseInputData

----------------------------------------------------------------------------------------------------
------------------------------------------ PARSING -------------------------------------------------
----------------------------------------------------------------------------------------------------

parseInputData :: String -> ([Int], [Int])
parseInputData = toTuple . map (tail . lines) . splitOn "\n\n"
    where toTuple (xs:ys:[]) = (map (\x -> read x :: Int) xs, map (\y -> read y :: Int) ys)

----------------------------------------------------------------------------------------------------
------------------------------------------- LOGIC --------------------------------------------------
----------------------------------------------------------------------------------------------------

playGame :: ([Int], [Int]) -> Int
playGame ([], ys) = sum $ zipWith (*) [1,2..] (reverse ys)
playGame (xs, []) = sum $ zipWith (*) [1,2..] (reverse xs)
playGame ((x:xs), (y:ys))
    | x > y     = playGame (xs ++ [x, y], ys)
    | otherwise = playGame (xs, ys ++ [y, x])


