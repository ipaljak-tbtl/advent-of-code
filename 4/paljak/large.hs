import Data.Char
import Data.Ix
import Data.List
import Data.List.Split

import qualified Data.Set as Set

requiredFields =
  Set.fromList ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"]

eyeColor = ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]

hexdig = ['0'..'9'] ++ ['a'..'f']

kvPairs :: [String] -> [String]
kvPairs = concatMap (words)

keys :: [String] -> [String]
keys = map (head . splitOn ":") . kvPairs

checkHeight :: String -> Bool
checkHeight s
  | "cm" `isSuffixOf` s = inRange (150, 193) val
  | "in" `isSuffixOf` s = inRange (59, 76) val
  | otherwise           = False
    where val = read (init $ init s)::Int

isValidPair :: String -> Bool
isValidPair s
  | "byr" `isPrefixOf` s = inRange (1920, 2002) intVal
  | "iyr" `isPrefixOf` s = inRange (2010, 2020) intVal
  | "eyr" `isPrefixOf` s = inRange (2020, 2030) intVal
  | "hgt" `isPrefixOf` s = checkHeight val
  | "hcl" `isPrefixOf` s = head val == '#' && (all (`elem` hexdig) $ tail val)
  | "ecl" `isPrefixOf` s = val `elem` eyeColor
  | "pid" `isPrefixOf` s = length val == 9 && all (isDigit) val
  | otherwise            = True
  where
    val           = last $ splitOn ":" s
    intVal        = read val :: Int

isValid :: [String] -> Int
isValid s = fromEnum $ checkRequired && checkValidity
  where
    checkRequired = requiredFields `Set.isSubsetOf` (Set.fromList $ keys s)
    checkValidity = and . map (isValidPair) $ kvPairs s

main :: IO()
main = getContents >>= print . sum . map (isValid) . splitOn [""] . lines
