import Data.List
import Data.Maybe

import qualified Data.Set as Set

data Instruction = Acc Int | Jmp Int | Nop Int deriving Show
data State = State Int Int
data Exit = Ok Int | Inf Int | Invalid deriving Show

isOk :: Exit -> Bool
isOk (Ok _) = True
isOk _      = False

parseLine :: String -> Instruction
parseLine s
  | "jmp" `isPrefixOf` s = Jmp . readInt . last $ words s
  | "acc" `isPrefixOf` s = Acc . readInt . last $ words s
  | otherwise            = Nop . readInt . last $ words s
  where
    readInt ('+':x) = read x::Int
    readInt x       = read x::Int

apply :: State -> Instruction -> State
apply (State ip acc) (Acc x) = State (ip + 1) (acc + x)
apply (State ip acc) (Jmp x) = State (ip + x) acc
apply (State ip acc) (Nop _) = State (ip + 1) acc

execute :: State -> Set.Set Int -> [Instruction] -> Exit
execute state@(State ip acc) s prog
  | ip `elem` s = Inf acc
  | ip == length prog = Ok acc
  | ip < 0 || ip > length prog = Invalid
  | otherwise = execute (apply state $ prog !! ip) (Set.insert ip s) prog

fix :: [Instruction] -> Exit
fix prog = fromJust $ find (isOk) allExecs
  where
    allExecs = map (execute (State 0 0) Set.empty . applyFix prog) [0..]
    applyFix prog ip = case (prog !! ip) of
      (Acc _) -> prog
      (Nop x) -> take ip prog ++ [Jmp x] ++ drop (ip + 1) prog
      (Jmp x) -> take ip prog ++ [Nop x] ++ drop (ip + 1) prog

main :: IO ()
main = getContents >>= print . fix . map (parseLine) . lines
