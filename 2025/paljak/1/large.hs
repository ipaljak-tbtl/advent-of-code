rotate :: (Int, Int) -> String -> (Int, Int)
rotate (cnt, dial) (h:t) = (cnt + cnt', dial')
  where dial'
          | h == 'L' = (dial - read t + 100) `mod` 100
          | h == 'R' = (dial + read t)       `mod` 100
        cnt'
          | h == 'L' = ((100 - dial) `mod` 100 + read t) `div` 100
          | h == 'R' = (dial + read t)                   `div` 100

main :: IO ()
main = getContents >>= print . fst . foldl (rotate) (0, 50) . lines
