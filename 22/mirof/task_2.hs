import Data.List
import Data.List.Split
import Data.Maybe
import qualified Data.Map as M
import qualified Data.Set as S

main :: IO ()
main = readFile "example.txt" >>= putStrLn . show . fst . playGame S.empty M.empty . parseInputData

----------------------------------------------------------------------------------------------------
------------------------------------------ PARSING -------------------------------------------------
----------------------------------------------------------------------------------------------------

parseInputData :: String -> ([Int], [Int])
parseInputData = toTuple . map (tail . lines) . splitOn "\n\n"
    where toTuple (xs:ys:[]) = (map (\x -> read x :: Int) xs, map (\y -> read y :: Int) ys)

----------------------------------------------------------------------------------------------------
------------------------------------------- LOGIC --------------------------------------------------
----------------------------------------------------------------------------------------------------

playGame :: S.Set ([Int], [Int]) -> M.Map ([Int], [Int]) Int -> ([Int], [Int]) -> (Int, M.Map ([Int], [Int]) Int)
playGame _ memo (xs, []) = (   sum $ zipWith (*) [1,2..] $ reverse $ xs, memo)
playGame _ memo ([], ys) = (negate $ sum $ zipWith (*) [1,2..] $ reverse $ ys, memo)
playGame set memo input @ (x:xs, y:ys)
    | input `S.member` set             = (sum $ zipWith (*) [1,2..] $ reverse $ xs, memo)
    | isJust $ M.lookup input memo     = (fromJust $ M.lookup input memo, memo)
    | length xs >= x && length ys >= y = if subResult > 0 then playGame newSet newMemo (xs ++ [x, y], ys) else playGame newSet newMemo (xs, ys ++ [y, x])
    | x > y                            = (resultXGTY, M.insert input resultXGTY newMemoXGTY)
    | otherwise                        = (resultYGTX, M.insert input resultYGTX newMemoYGTX)
        where (subResult, newMemo) = playGame S.empty memo (take x xs, take y ys)
              newSet = S.insert input set
              (resultXGTY, newMemoXGTY) = playGame newSet memo (xs ++ [x, y], ys)
              (resultYGTX, newMemoYGTX) = playGame newSet memo (xs, ys ++ [y, x])

