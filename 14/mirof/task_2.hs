import Data.Bits
import Data.List.Split
import Data.Maybe
import qualified Data.Map as M

data Command = Mask String | Memory Int Int
               deriving Show

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . sumAllMemoryLocations . parseInputData

parseInputData :: String -> [Command]
parseInputData = map parseCommand . lines

parseCommand :: String -> Command
parseCommand ('m':'a':'s':'k':rest) = Mask mask
    where mask = words rest !! 1
parseCommand ('m':'e':'m'    :rest) = Memory location value
    where ws       = words rest
          location = read (init $ tail $ ws !! 0) :: Int
          value    = read (ws !! 2) :: Int

sumAllMemoryLocations :: [Command] -> Int
sumAllMemoryLocations commands = sumAllMemoryLocations' commands Nothing M.empty

sumAllMemoryLocations' :: [Command] -> Maybe Command -> M.Map Int Int -> Int
sumAllMemoryLocations' []                            _           stateMap = M.fold (+) 0 stateMap
sumAllMemoryLocations' ((mask @ (Mask _)):commands)  currentMask stateMap = sumAllMemoryLocations' commands (Just mask) stateMap
sumAllMemoryLocations' ((Memory key value):commands) currentMask stateMap = sumAllMemoryLocations' commands currentMask newStateMap
    where als = allLocations 0 (fromJust currentMask) key
          newStateMap = fillMap als value stateMap

fillMap :: [Int] -> Int -> M.Map Int Int -> M.Map Int Int
fillMap [] value state = state
fillMap (al:als) value state = fillMap als value newState
    where newState = M.insert al value state

allLocations :: Int -> Command -> Int -> [Int]
allLocations index (mask @ (Mask maskString)) location
    | index >= (length maskString)      = [location]
    | maskString !! reverseIndex == 'X' = (allLocations (index + 1) mask (location `setBit` index)) ++ (allLocations (index + 1) mask (location `clearBit` index))
    | maskString !! reverseIndex == '1' = allLocations (index + 1) mask (location `setBit` index)
    | maskString !! reverseIndex == '0' = allLocations (index + 1) mask location
        where reverseIndex = (length maskString - index - 1)


