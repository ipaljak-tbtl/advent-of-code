import Data.Char (isDigit)
import Data.List (transpose)

evalProblem :: [String] -> Integer
evalProblem cols =
  foldl1 op (map readCol cols)
  where
    op = case head [c | c <- map last cols, c /= ' '] of
           '+' -> (+)
           '*' -> (*)
    readCol col =
      let digits = filter isDigit (init col)
      in read digits :: Integer

splitProblems :: [String] -> [[String]]
splitProblems [] = []
splitProblems cs =
  case dropWhile blank cs of
    []  -> []
    cs' -> let (p, rest) = span (not . blank) cs'
           in p : splitProblems rest
    where blank = all (== ' ')


homework :: [String] -> Integer
homework l = sum (map evalProblem $ splitProblems cols)
  where
    pad s = take (maximum $ map length l) (s ++ repeat ' ')
    cols  = transpose $ map pad l

main :: IO ()
main = getContents >>= print . homework . lines
