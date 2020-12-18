import Data.List.Utils

data Algebra = Number Int | Plus | Product | OpenPar | ClosePar
               deriving Show

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . sum . calcOfAllLines . parseInputData

parseInputData :: String -> [[Algebra]]
parseInputData = map (polishNotation [] . parseLine . words) . lines . replace ")" " )" . replace "(" "( "

parseLine :: [String] -> [Algebra]
parseLine []          = []
parseLine ("(":elems) = [OpenPar]           ++ parseLine elems
parseLine (")":elems) = [ClosePar]          ++ parseLine elems
parseLine ("+":elems) = [Plus]              ++ parseLine elems
parseLine ("*":elems) = [Product]           ++ parseLine elems
parseLine (num:elems) = [Number (read num)] ++ parseLine elems

polishNotation :: [Algebra] -> [Algebra] -> [Algebra]
polishNotation []              []                         = []
polishNotation (elem:stack)    []                         = elem    : polishNotation stack []

polishNotation stack           ((num @ (Number _)):elems) = num     : polishNotation stack elems

polishNotation (Plus:stack)    elems @ (Plus:_)           = Plus    : polishNotation stack elems
polishNotation (Product:stack) elems @ (Plus:_)           = Product : polishNotation stack elems
polishNotation stack           (Plus:elems)               = polishNotation (Plus:stack) elems

polishNotation (Plus:stack)    elems @ (Product:_)        = Plus    : polishNotation stack elems
polishNotation (Product:stack) elems @ (Product:_)        = Product : polishNotation stack elems
polishNotation stack           (Product:elems)            = polishNotation (Product:stack) elems

polishNotation stack           (OpenPar:elems)            = polishNotation (OpenPar:stack) elems
polishNotation (OpenPar:stack) (ClosePar:elems)           = polishNotation stack elems
polishNotation (elem:stack)    line @ (ClosePar:elems)    = elem : polishNotation stack line

calcOfAllLines :: [[Algebra]] -> [Int]
calcOfAllLines []           = []
calcOfAllLines (line:lines) = calculate line [] ++ calcOfAllLines lines

calculate :: [Algebra] -> [Algebra] -> [Int]
calculate []                       [Number num]                  = [num]
calculate (Plus:elems)             (Number one:Number two:stack) = calculate elems (Number (one + two):stack)
calculate (Product:elems)          (Number one:Number two:stack) = calculate elems (Number (one * two):stack)
calculate (num @ (Number _):elems) stack                         = calculate elems (num:stack)
