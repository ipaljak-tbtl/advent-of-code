import qualified Data.Set as S
import Data.List
import Data.Maybe

data ComputerState = ComputerState { accumulator :: Int, pointer :: Int, success :: Bool }
                     deriving (Eq, Show)

data Command = Nop Int | Acc Int | Jmp Int
               deriving (Eq, Show)

initComputerState :: ComputerState
initComputerState = ComputerState { accumulator = 0, pointer = 0, success = True }

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . runAllPrograms . parseInputData

parseInputData :: String -> [[Command]]
parseInputData = allPossiblePrograms . map (\(x:y:_) -> (parseCommand x y)) . map words . lines

parseCommand :: String -> String -> Command
parseCommand "nop" num = Nop $ parseInt num
parseCommand "acc" num = Acc $ parseInt num
parseCommand "jmp" num = Jmp $ parseInt num

parseInt :: String -> Int
parseInt ('+':xs) = read xs :: Int
parseInt ('-':xs) = negate $ read xs :: Int

allPossiblePrograms :: [Command] -> [[Command]]
allPossiblePrograms program = replaceJmpWithNop program ++ replaceNopWithJmp program

replaceJmpWithNop :: [Command] -> [[Command]]
replaceJmpWithNop program = [ start ++ [Nop y] ++ tail end | (x, Jmp y) <- zip [0,1..] program, let (start, end) = splitAt x program]

replaceNopWithJmp :: [Command] -> [[Command]]
replaceNopWithJmp program = [ start ++ [Jmp y] ++ tail end | (x, Nop y) <- zip [0,1..] program, let (start, end) = splitAt x program]

runAllPrograms :: [[Command]] -> ComputerState
runAllPrograms = fromJust . find success . map (emulateProgram initComputerState S.empty)

emulateProgramCheck :: ComputerState -> S.Set Int -> [Command] -> ComputerState
emulateProgramCheck computerState usedLines program
    | currentPointer `elem` usedLines  = computerState { success = False }
    | currentPointer >= length program = computerState
    | otherwise                        = emulateProgram computerState usedLines program
        where currentPointer   = pointer computerState

emulateProgram :: ComputerState -> S.Set Int -> [Command] -> ComputerState
emulateProgram computerState usedLines program = emulateProgramCheck newComputerState newUsedLines program
    where newComputerState = execute computerState command
          command          = program !! currentPointer
          currentPointer   = pointer computerState
          newUsedLines     = S.union usedLines $ S.singleton currentPointer


execute :: ComputerState -> Command -> ComputerState
execute computerState (Nop num) = computerState { pointer = (pointer computerState) + 1 }
execute computerState (Acc num) = computerState { accumulator = (accumulator computerState) + num, pointer = (pointer computerState) + 1 }
execute computerState (Jmp num) = computerState { pointer = (pointer computerState) + num }
