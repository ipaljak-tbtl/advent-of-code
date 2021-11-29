import Data.Char
import Data.List
import Data.List.Split

main = readFile "problem_1.txt" >>= putStrLn . show . countCorrectPassports

countCorrectPassports :: String -> Int
countCorrectPassports = length . validFields . validNumberOfFields

validFields :: [String] -> [String]
validFields = filter (validateFields . map (splitOn ":") . words)

validateFields :: [[String]] -> Bool
validateFields [] = True
validateFields ((field:value:_):fields)
    | "byr" == field && byrCondition value = validateFields fields
    | "iyr" == field && iyrCondition value = validateFields fields
    | "eyr" == field && eyrCondition value = validateFields fields
    | "hgt" == field && hgtCondition value = validateFields fields
    | "hcl" == field && hclCondition value = validateFields fields
    | "ecl" == field && eclCondition value = validateFields fields
    | "pid" == field && pidCondition value = validateFields fields
    | "cid" == field                       = validateFields fields
    | otherwise                            = False

byrCondition :: String -> Bool
byrCondition value = number >= 1920 && number <= 2002
    where number = read value :: Integer

iyrCondition :: String -> Bool
iyrCondition value = number >= 2010 && number <= 2020
    where number = read value :: Integer

eyrCondition :: String -> Bool
eyrCondition value = number >= 2020 && number <= 2030
    where number = read value :: Integer

hgtCondition :: String -> Bool
hgtCondition value
    | isSuffixOf "cm" value = checkCm $ init $ init value
    | isSuffixOf "in" value = checkIn $ init $ init value
    | otherwise             = False

checkCm :: String -> Bool
checkCm value = height >= 150 && height <= 193
    where height = read value :: Integer

checkIn :: String -> Bool
checkIn value = height >= 59 && height <= 76
    where height = read value :: Integer

hclCondition :: String -> Bool
hclCondition value = length value == 7 && isPrefixOf "#" value && (all (\x -> isDigit x || isLower x) $ tail value)

eclCondition :: String -> Bool
eclCondition value = any (==value) ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]

pidCondition :: String -> Bool
pidCondition value = length value == 9 && (all isDigit value)

validNumberOfFields :: String -> [String]
validNumberOfFields = filter (checkPassport . words) . splitOn "\n\n"

checkPassport :: [String] -> Bool
checkPassport fields = (length fields == 8) || (length fields == 7 && not isCidAbsent)
    where isCidAbsent = any (isPrefixOf "cid") fields
