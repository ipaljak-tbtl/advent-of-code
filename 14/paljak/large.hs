import Data.Bits
import Data.Char
import Data.List
import Data.List.Split
import Data.List.Utils

import qualified Data.Map as Map

type Memory = Map.Map Int Int
type Mask = String

data State = State Memory Mask deriving Show
data Instruction = Insert Int Int | Update Mask deriving Show

emptyState = State Map.empty "0"

fromBinary :: String -> Int
fromBinary = foldl' (\ret bit -> 2 * ret + digitToInt bit) 0

parseLines :: [String] -> [Instruction]
parseLines = map (parseLine)
  where
    parseLine l
      | "ma" `isPrefixOf` l = Update . tail . last $ eqSplit l
      | "me" `isPrefixOf` l = Insert (parseIdx . head $ eqSplit l) (read . last $ eqSplit l)
    eqSplit  = splitOn "="
    parseIdx = read . head . splitOn "]" . drop 4

allKeys :: Int -> Int -> Mask -> [Int]
allKeys i val msk
  | i == n                    = [val]
  | msk !! (n - i - 1) == '0' = allKeys (i + 1) val msk
  | msk !! (n - i - 1) == '1' = allKeys (i + 1) (setBit val i) msk
  | msk !! (n - i - 1) == 'X' = (allKeys (i + 1) (clearBit val i) msk) ++
                                (allKeys (i + 1) (setBit val i) msk)
    where n = length msk

emulate :: State -> [Instruction] -> State
emulate st = foldl' (execute) st
  where
   execute (State mem msk) (Update m)   = State mem m
   execute (State mem msk) (Insert k v) =
     State (foldl' (\mem' k' -> Map.insert  k' v mem') mem $ allKeys 0 k msk) msk

valueSum :: State -> Int
valueSum (State mem _) = sum $ Map.elems mem

main :: IO ()
main =
  getContents >>= print . valueSum . emulate emptyState . parseLines . lines
