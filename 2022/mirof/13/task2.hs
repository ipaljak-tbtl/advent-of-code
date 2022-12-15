import Data.Char (isDigit)
import Data.List (sortBy)
import Data.Maybe (fromJust, isJust)
import Data.Ord
import Text.Read

main = do
    input <- readFile "input.txt"
    let solution = foldl (*) 1 $ map fst $ filter (\(i, x) -> x == "[[2]]" || x == "[[6]]") $ zip [1..] $ sortBy (\x y -> if solve x y then LT else GT)  $ parse $ lines input
    putStrLn $ show solution

data Node = Child [Node] | Leaf Int deriving (Show)

parse :: [String] -> [String]
parse (line1:line2:[])           = [line1, line2] ++ ["[[2]]", "[[6]]"]
parse (line1:line2:_:otherLines) = [line1, line2] ++ parse otherLines

solve :: String -> String -> Bool
solve left right
    | isJust result     = fromJust result
    | result == Nothing = True
    where
        result = check (makeTree (Child []) left) (makeTree (Child []) right)

check :: Node -> Node -> Maybe Bool
check (Child (_:_))      (Child [])         = Just False
check (Child [])         (Child (_:_))      = Just True
check (Child [])         (Child [])         = Nothing
check (Child (c1:list1)) (Child (c2:list2))
    | isJust result = result
    | otherwise     = check (Child list1) (Child list2)
        where
            result = check c1 c2

check leaf@(Leaf _)      node@(Child _)     = check (Child [leaf]) node
check node@(Child _)     leaf@(Leaf _)      = check node           (Child [leaf])
check (Leaf num1)        (Leaf num2)
    | num1 == num2 = Nothing
    | num1 <  num2 = Just True
    | num1 >  num2 = Just False

makeTree :: Node -> String -> Node
makeTree node              []       = node
makeTree node@(Child list) (c:line)
    | c == ','  = makeTree node line
    | c == '['  = makeTree (Child $ list ++ [newChild]) lineWithoutNewChild
    | c == ']'  = node
    | isDigit c = makeTree (Child $ list ++ [Leaf (read (takeWhile isDigit (c:line)) :: Int)]) (dropWhile isDigit line)
        where
            newChildLine        = takeWhileDiffNumOfBrackets line 1 0 -- we are starting with one left bracket off
            newChild            = makeTree (Child []) newChildLine
            lineWithoutNewChild = drop ((length newChildLine) + 1) line

takeWhileDiffNumOfBrackets :: String -> Int -> Int -> String
takeWhileDiffNumOfBrackets [] lb rb = if lb == rb then [] else error "unreachable!!!"
takeWhileDiffNumOfBrackets (c:line) lb rb
    | lb == rb  = []
    | c == '['  = c : takeWhileDiffNumOfBrackets line (lb+1) rb
    | c == ']'  = c : takeWhileDiffNumOfBrackets line lb     (rb+1)
    | otherwise = c : takeWhileDiffNumOfBrackets line lb     rb
