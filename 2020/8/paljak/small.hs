import Data.List

import qualified Data.Set as Set

data Instruction = Acc Int | Jmp Int | Nop deriving Show
data State = State Int Int

parseLine :: String -> Instruction
parseLine s
  | "jmp" `isPrefixOf` s = Jmp . readInt . last $ words s
  | "acc" `isPrefixOf` s = Acc . readInt . last $ words s
  | otherwise            = Nop
  where
    readInt ('+':x) = read x::Int
    readInt x       = read x::Int

apply :: State -> Instruction -> State
apply (State ip acc) (Acc x) = State (ip + 1) (acc + x)
apply (State ip acc) (Jmp x) = State (ip + x) acc
apply (State ip acc) (Nop)   = State (ip + 1) acc

execute :: State -> Set.Set Int -> [Instruction] -> Int
execute state@(State ip acc) s prog
  | ip `elem` s = acc
  | otherwise   = execute (apply state $ prog !! ip) (Set.insert ip s) prog

main :: IO ()
main =
  getContents >>= print . execute (State 0 0) Set.empty . map (parseLine) . lines
