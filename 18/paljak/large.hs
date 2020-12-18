import Data.List
import Data.Maybe

slice :: (Int, Int) -> [a] -> [a]
slice (l, r) = drop (l - 1) . take r

interleave :: [a] -> [a] -> [a]
interleave xs ys = concat $ transpose [xs, ys]

parenDiff :: String -> [(Int, Int)]
parenDiff = tail . scanl (diff) (0, -1)
  where
    diff (cnt, i) '(' = (cnt + 1, i + 1)
    diff (cnt, i) ')' = (cnt - 1, i + 1)
    diff (cnt, i)  _  = (cnt    , i + 1)

evalClean :: [Int] -> String -> Int
evalClean operands operators
  | plus == Nothing = product operands
  | otherwise       = evalClean operands' operators'
  where
    plus       = find (\(_, c) -> c == '+') $ zip [0..] operators
    plusId     = fst $ fromJust plus
    operators' = take plusId operators ++ drop (plusId + 1) operators
    operands'  = take plusId operands ++
                 [(operands !! plusId) + operands !! (plusId + 1)] ++
                 drop (plusId + 2) operands

eval :: String -> Int
eval s
  | '+' `notElem` s && '*' `notElem` s = read s
  | operatorIds == []                  = eval . init $ tail s
  | otherwise                          = evalClean operands operators
    where
      operands    = map (eval) extract
      extract     = map (\(l, r) -> slice (l + 3, r - 1) s) .
                    zip operIdsExt $ tail operIdsExt
      operators   = map (\i -> s !! i) operatorIds
      operIdsExt  = [-2] ++ operatorIds ++ [length s + 1]
      operatorIds = map (snd) . filter (balancedOp) $ parenDiff s
        where balancedOp (c, i) = c == 0 && (s !! i) `elem` "*+"

main :: IO ()
main = getContents >>= print . sum . map (eval) . lines
