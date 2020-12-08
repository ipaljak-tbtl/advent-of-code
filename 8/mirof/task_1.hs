import qualified Data.Set as S

data ComputerState = ComputerState { accumulator :: Int, pointer :: Int }
                     deriving (Eq, Show)

data Command = Nop | Acc Int | Jmp Int
               deriving (Eq, Show)

initComputerState :: ComputerState
initComputerState = ComputerState { accumulator = 0, pointer = 0 }

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . emulateProgram initComputerState S.empty . parseInputData

parseInputData :: String -> [Command]
parseInputData = map (\(x:y:_) -> (parseCommand x y)) . map words . lines

parseCommand :: String -> String -> Command
parseCommand "nop" _   = Nop
parseCommand "acc" num = Acc $ parseInt num
parseCommand "jmp" num = Jmp $ parseInt num

parseInt :: String -> Int
parseInt ('+':xs) = read xs :: Int
parseInt ('-':xs) = negate $ read xs :: Int

emulateProgramCheck :: ComputerState -> S.Set Int -> [Command] -> ComputerState
emulateProgramCheck computerState usedLines program
    | currentPointer `elem` usedLines = computerState
    | otherwise                       = emulateProgram computerState usedLines program
        where currentPointer   = pointer computerState

emulateProgram :: ComputerState -> S.Set Int -> [Command] -> ComputerState
emulateProgram computerState usedLines program = emulateProgramCheck newComputerState newUsedLines program
    where newComputerState = execute computerState command
          command          = program !! currentPointer
          currentPointer   = pointer computerState
          newUsedLines     = S.union usedLines $ S.singleton currentPointer


execute :: ComputerState -> Command -> ComputerState
execute computerState Nop       = computerState { pointer = (pointer computerState) + 1 }
execute computerState (Acc num) = computerState { accumulator = (accumulator computerState) + num, pointer = (pointer computerState) + 1 }
execute computerState (Jmp num) = computerState { pointer = (pointer computerState) + num }
