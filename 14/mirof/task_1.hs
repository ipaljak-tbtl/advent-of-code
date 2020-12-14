import Data.Bits
import Data.List.Split
import Data.Maybe
import qualified Data.Map as M

data Command = Mask String | Memory String Int
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
          location = ws !! 0
          value    = read (ws !! 2) :: Int

sumAllMemoryLocations :: [Command] -> Int
sumAllMemoryLocations commands = sumAllMemoryLocations' commands Nothing M.empty

sumAllMemoryLocations' :: [Command] -> Maybe Command -> M.Map String Int -> Int
sumAllMemoryLocations' []                            _           stateMap = M.fold (+) 0 stateMap
sumAllMemoryLocations' ((mask @ (Mask _)):commands)  currentMask stateMap = sumAllMemoryLocations' commands (Just mask) stateMap
sumAllMemoryLocations' ((Memory key value):commands) currentMask stateMap = sumAllMemoryLocations' commands currentMask newStateMap
    where newStateMap = M.insert key maskedValue stateMap
          maskedValue = maskValue 0 (fromJust currentMask) value

maskValue :: Int -> Command -> Int -> Int
maskValue index (mask @ (Mask maskString)) value
    | index >= (length maskString) = value
    | maskString !! reverseIndex == 'X'   = maskValue (index + 1) mask value
    | maskString !! reverseIndex == '1'   = maskValue (index + 1) mask (value `setBit` index)
    | maskString !! reverseIndex == '0'   = maskValue (index + 1) mask (value `clearBit` index)
        where reverseIndex = (length maskString - index - 1)


