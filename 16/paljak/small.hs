import Data.Ix
import Data.List
import Data.List.Split

data Rule = Rule (Int, Int) (Int, Int) deriving Show
type Ticket = [Int]

parseLines :: [String] -> ([Rule], [Ticket])
parseLines ls = (parseRules $ take 20 ls, parseTickets $ drop 25 ls)
  where
    parseTickets   = map (map (read) . splitOn ",")
    parseRules     = map (parseRule)
    parseRule l    = Rule (parseRange $ ws !! (wl - 3)) (parseRange $ ws !! (wl - 1))
      where
        ws = words l
        wl = length ws
    parseRange     = tuplify . map (read) . splitOn "-"
    tuplify [x, y] = (x, y)

errorRate :: ([Rule], [Ticket]) -> Int
errorRate (rules, tickets) = sum $ map (sum . filter (invalidField)) tickets
  where
    invalidField f = not $ any (\(Rule r1 r2) -> (inRange r1 f) || (inRange r2 f)) rules

main :: IO ()
main = getContents >>= print . errorRate . parseLines . lines
