import Data.List

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . productCountOfOnesAndThrees . parseInputData

parseInputData :: String -> [Int]
parseInputData input = sort $ [0] ++ (map (\x -> read x :: Int) $ lines input)

productCountOfOnesAndThrees :: [Int] -> Int
productCountOfOnesAndThrees numbers = (fst counts) * (snd counts + 1)
    where counts = foldl (incCountForOnesOrThrees) (0, 0) $ zipWith (-) (tail numbers) numbers

incCountForOnesOrThrees :: (Int, Int) -> Int -> (Int, Int)
incCountForOnesOrThrees (x, y) 1 = (x + 1, y)
incCountForOnesOrThrees (x, y) 3 = (x, y + 1)
