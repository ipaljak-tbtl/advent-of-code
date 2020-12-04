import Data.List.Split
import qualified Data.Set as Set

requiredFields =
  Set.fromList ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"]

keys :: [String] -> [String]
keys = map (head . splitOn ":") . concatMap (words)

isValid :: [String] -> Int
isValid s = fromEnum $ requiredFields `Set.isSubsetOf` (Set.fromList $ keys s)

main :: IO()
main = getContents >>= print . sum . map (isValid) . splitOn [""] . lines
