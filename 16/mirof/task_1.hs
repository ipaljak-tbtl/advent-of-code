import Data.List.Split
import Data.List

type Constraint       = (Int, Int)
type FieldConstraints = [(Constraint, Constraint)]
type TicketData       = [TicketDatum]
type TicketDatum      = [Int]

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . sum . invalidFields . parseInputData

parseInputData :: String -> (FieldConstraints, TicketDatum, TicketData)
parseInputData input = (contrains, myTicket, nearbyTickets)
    where contrains     = (map (\(x, y) -> ((read (x !! 0), read (x !! 1)) , (read (y !! 0), read (y !! 1)))) . map (\(x, y) -> (splitOn "-" x, splitOn "-" y)) . map (\x -> ((last . init . init) x, last x)) . map words . take 20 . lines) input
          myTicket      = (map read . splitOn "," . head . drop 22 . lines) input
          nearbyTickets = (map (map read) . map (splitOn ",") . drop 25 . lines) input

invalidFields :: (FieldConstraints, TicketDatum, TicketData) -> [Int]
invalidFields (_, _, []) = []
invalidFields (contraints, myTicket, (ticket:tickets)) = invalid ++ invalidFields (contraints, myTicket, tickets)
    where invalid = filter (\x -> filter (\((fl, fh), (sl, sh)) -> condition fl fh sl sh x) contraints == []) ticket
          condition fl fh sl sh y = ((fl <= y && fh >= y) || (sl <= y && sh >= y))


