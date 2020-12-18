import Data.List
import Data.Maybe

getOper :: String -> (Int -> Int -> Int)
getOper "+" = (+)
getOper  _  = (*)

stripOper :: String -> ((Int -> Int -> Int), String)
stripOper s
  | ws == []  = ((+), "")
  | otherwise = (getOper $ head ws, unwords $ tail ws)
    where ws = words s

stripOperand :: String -> (String,  String)
stripOperand ('(':s) = (take nextId s, drop (nextId + 1) s)
  where
    nextId = snd . fromJust . find (balanced) $ scanl (diff) (1, -1) s
    diff (cnt, i) '(' = (cnt + 1, i + 1)
    diff (cnt, i) ')' = (cnt - 1, i + 1)
    diff (cnt, i)  _  = (cnt    , i + 1)
    balanced (cnt, _) = cnt == 0
stripOperand s = (head $ words s, unwords . tail $ words s)

eval :: Int -> (Int -> Int -> Int) -> String -> Int
eval val oper "" = val
eval val oper s
  | '+' `notElem` s && '*' `notElem` s = oper val $ read s
  | otherwise = eval (oper val $ eval 0 (+) nextOperand) nextOper rest
    where
      (nextOperand, afterOperand) = stripOperand s
      (nextOper, rest) = stripOper afterOperand

main :: IO ()
main = getContents >>= print . sum . map (eval 0 (+)) . lines
