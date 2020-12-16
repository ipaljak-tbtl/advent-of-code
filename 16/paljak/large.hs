import Data.Ix
import Data.List
import Data.List.Split

import qualified Data.Set as Set
import qualified Data.Map as Map

import MaxMatching

type Ticket = [Int]

data Rule = Rule (Int, Int) (Int, Int) deriving Show

isValid :: Int -> Rule -> Bool
isValid x (Rule r1 r2) = (inRange r1 x) || (inRange r2 x)

parseLines :: [String] -> ([Rule], Ticket, [Ticket])
parseLines ls = (parseRules $ take 20 ls,
                 parseTicket (ls !! 22),
                 parseTickets $ drop 25 ls)
  where
    parseTickets   = map (parseTicket)
    parseTicket    = map (read) . splitOn ","
    parseRules     = map (parseRule)
    parseRule l    = Rule (parseRange $ ws !! (wl - 3)) (parseRange $ ws !! (wl - 1))
      where
        ws = words l
        wl = length ws
    parseRange     = tuplify . map (read) . splitOn "-"
    tuplify [x, y] = (x, y)

filterValid :: ([Rule], Ticket, [Ticket]) -> ([Rule], Ticket, [Ticket])
filterValid (rules, myTicket, tickets) =
  (rules, myTicket, filter (validTicket) tickets)
    where
      validTicket = all (validField)
      validField f = any (\r-> isValid f r) rules

buildGraph :: ([Rule], [Ticket]) -> Set.Set (Int, Int)
buildGraph (rules, tickets) = Set.fromList [(i, j) | i <- [0..rlen - 1],
                                                     j <- [0..rlen - 1],
                                                     check i j]
  where
    rlen = length $ rules
    check i j = all (\t -> isValid (t !! i) (rules !! j)) tickets

solve :: ([Rule], Ticket, [Ticket]) -> Int
solve (rules, myTicket, tickets) =
  calc . MaxMatching.matching $ buildGraph (rules, tickets)
    where calc match = product $ map (\x -> myTicket !! (match Map.! x)) [0..5]

main :: IO ()
main = getContents >>= print . solve . filterValid . parseLines . lines
