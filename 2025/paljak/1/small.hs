rotate :: (Int, Int) -> String -> (Int, Int)
rotate (cnt, dial) (h:t) = (cnt + fromEnum (dial' == 0), dial')
  where dial' | h == 'L' = (dial - read t + 100) `mod` 100
              | h == 'R' = (dial + read t)       `mod` 100

main :: IO ()
main = getContents >>= print . fst . foldl (rotate) (0, 50) . lines
