homework :: [[String]] -> Int
homework l
  | head l == [] = 0
  | otherwise    = foldl1 (op) (map (readInt . head) $ init l) + (homework $ map (tail) l)
  where
    readInt = read :: String -> Int
    op = case (head $ last l) of
           "+" -> (+)
           "*" -> (*)

main :: IO ()
main = getContents >>= print . homework . map (words) . lines
