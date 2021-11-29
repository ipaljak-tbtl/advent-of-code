import Data.List (sortBy)
import Data.Function (on)
import Data.List.Split
import Data.List
import qualified Data.Matrix as M
import qualified Data.Vector as V
import Data.Maybe

type Constraint       = (Int, Int)
type FieldConstraints = [(Constraint, Constraint)]
type TicketData       = [TicketDatum]
type TicketDatum      = [Int]

main :: IO ()
main = readFile "problem_2.txt" >>= putStrLn . show . solve . parseInputData

parseInputData :: String -> (FieldConstraints, TicketDatum, TicketData)
parseInputData input = (contrains, myTicket, nearbyTickets)
    where contrains     = (map (\(x, y) -> ((read (x !! 0), read (x !! 1)) , (read (y !! 0), read (y !! 1)))) . map (\(x, y) -> (splitOn "-" x, splitOn "-" y)) . map (\x -> ((last . init . init) x, last x)) . map words . take 20 . lines) input
          myTicket      = (map read . splitOn "," . head . drop 22 . lines) input
          nearbyTickets = (map (map read) . map (splitOn ",") . drop 25 . lines) input

validTickets :: (FieldConstraints, TicketDatum, TicketData) -> TicketData
validTickets (_, _, []) = []
validTickets (contraints, myTicket, (ticket:tickets)) = validTicket ++ validTickets (contraints, myTicket, tickets)
    where validTicket = if invalid == [] then [ticket] else []
          invalid = filter (\x -> filter (\((fl, fh), (sl, sh)) -> condition fl fh sl sh x) contraints == []) ticket
          condition fl fh sl sh y = ((fl <= y && fh >= y) || (sl <= y && sh >= y))

solve :: (FieldConstraints, TicketDatum, TicketData) -> Int
solve input @ (contraints, myTicket, allTickets) = solveProblem contraints myTicket $ M.fromLists tickets
    where tickets = validTickets input


solveProblem :: FieldConstraints -> TicketDatum -> M.Matrix Int -> Int
solveProblem constraints myTicket tickets = foldl (*) 1 $ map (\x -> myTicket !! x) $ take 6 $ map snd $ sortBy (compare `on` fst) $ take 20 $ prob states
    where states = allStates constraints tickets

prob :: [[Int]] -> [(Int, Int)]
prob states = [(index, current_index)] ++ prob (map (filter (/=current_index)) states)
    where index = fromJust $ findIndex (\x -> length x == 1) states
          current_index = states !! index !! 0

allStates :: FieldConstraints -> M.Matrix Int -> [[Int]]
allStates [] _ = []
allStates (constraint:constraints) tickets = [possibleIndex] ++ allStates constraints tickets
    where possibleIndex = map fst $ filter snd $ zip [0,1..] conditionMatrix
          condition ((fl, fh), (sl, sh)) y = ((fl <= y && fh >= y) || (sl <= y && sh >= y))
          conditionMatrix = map (\x -> filter (\y -> not $ condition constraint y) x == []) $ map (\x -> V.toList $ M.getCol x tickets) [1..20]

