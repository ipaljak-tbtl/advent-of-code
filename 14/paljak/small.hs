import Data.Bits
import Data.Char
import Data.List
import Data.List.Split
import Data.List.Utils

import qualified Data.Map as Map

type Memory = Map.Map Int Int
type Mask = (Int, Int)

data State = State Memory Mask deriving Show
data Instruction = Insert Int Int | Update Mask deriving Show

emptyState = State Map.empty (0, 0)

fromBinary :: String -> Int
fromBinary = foldl' (\ret bit -> 2 * ret + digitToInt bit) 0

parseLines :: [String] -> [Instruction]
parseLines = map (parseLine)
  where
    parseLine l
      | "ma" `isPrefixOf` l = Update . parseMask . tail . last $ eqSplit l
      | "me" `isPrefixOf` l = Insert (parseIdx . head $ eqSplit l) (read . last $ eqSplit l)
    eqSplit  = splitOn "="
    parseIdx = read . head . splitOn "]" . drop 4
    parseMask mask = (fromBinary $ oneMask mask, fromBinary $ zeroMask mask)
    oneMask  = replace "X" "0"
    zeroMask = replace "X" "1"

emulate :: State -> [Instruction] -> State
emulate st = foldl' (execute) st
  where
   execute (State mem msk) (Insert k v) = State (Map.insert k (applyMask v msk) mem) msk
   execute (State mem msk) (Update m)   = State mem m
   applyMask val (m1, m0) = (val .|. m1) .&. m0

valueSum :: State -> Int
valueSum (State mem _) = sum $ Map.elems mem

main :: IO ()
main =
  getContents >>= print . valueSum . emulate emptyState . parseLines . lines
