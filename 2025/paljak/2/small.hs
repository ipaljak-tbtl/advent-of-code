import Data.List.Split
import Data.String.Utils

half :: String -> String
half s = take ((length s + 1) `div` 2) s

findInvalid :: String -> [Int]
findInvalid s =
  dropWhile (< read l) . takeWhile (<= read r) $ map (\x -> read $ show x ++ show x :: Int) [0..]
    where
      l = head $ splitOn "-" s
      r = last $ splitOn "-" s

solve :: [String] -> Int
solve = sum . map (sum . findInvalid)

main :: IO ()
main = getContents >>= print . solve . splitOn "," . strip
