import Data.List
import Data.Maybe

import qualified Data.Set as Set

type State = (Set.Set (Int, Int), Set.Set (Int, Int))

dir = [(-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1)]

emptyState = (Set.empty, Set.empty)

getOccupied :: State -> Int
getOccupied (_, occupied) = length occupied

nextState :: State -> State
nextState (empty, occupied) = (newEmpty, Set.difference allSeats newEmpty)
  where
    allSeats  = Set.union empty occupied
    newEmpty  = Set.filter (isEmpty) allSeats
    isEmpty x = x `Set.member` empty && occupiedNeigh x > 0 ||
                x `Set.member` occupied && occupiedNeigh x >= 5
    occupiedNeigh x   = length . filter (`Set.member` occupied) $ neighbours x
    neighbours (r, s) = [findNeighbour (r + dr, s + ds) d | d@(dr, ds) <- dir]
    findNeighbour (r, s) (dr, ds)
      | (r, s) `Set.member` allSeats         = (r, s)
      | r < 0 || r > 100 || s < 0 || s > 100 = (r, s)
      | otherwise = findNeighbour (r + dr, s + ds) (dr, ds)

solve :: State -> Int
solve root =
  getOccupied . fst . fromJust . find (repeating) . zip states $ tail states
    where
      states = [emptyState, root] ++ tail (scanl1 (\_ s -> nextState s) states)
      repeating (s1, s2) = s1 == s2

parseGrid :: [String] -> State
parseGrid grid = (empty, occupied)
  where
    occupied = Set.empty
    empty    = Set.fromList $ [(r, s) | r <- [0..length grid - 1],
                                        s <- [0..(length $ head grid) - 1],
                                        grid !! r !! s == 'L']

main :: IO ()
main = getContents >>= print . solve . parseGrid . lines
