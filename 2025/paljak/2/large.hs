import Data.List
import Data.List.Split
import Data.String.Utils

isPeriodic :: String -> Bool
isPeriodic s = s `isInfixOf` (drop 1 . init $ s ++ s)

findInvalid :: String -> [Int]
findInvalid s = filter (isPeriodic . show) [l..r]
  where
    l = read . head $ splitOn "-" s :: Int
    r = read . last $ splitOn "-" s :: Int

solve :: [String] -> Int
solve = sum . map (sum . findInvalid)

main :: IO ()
main = getContents >>= print . solve . splitOn "," . strip
