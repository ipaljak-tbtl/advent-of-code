import Data.List (intercalate, isPrefixOf)
import Text.Read

data Command = Addx Int  | Noop deriving (Show, Eq)

data StateMachine = StateMachine {
    cycleCounter :: Int,
    registerX    :: Int,
    screen       :: [Char]
}

initStateMachine :: StateMachine
initStateMachine = StateMachine { cycleCounter = 1, registerX = 1, screen = [] }

incrementCycle :: StateMachine -> StateMachine
incrementCycle stateMachine = stateMachine { cycleCounter = (cycleCounter stateMachine) + 1 }

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ showScreen solution

parse :: String -> [Command]
parse = foldl (++) [] . map parseCommand . lines

parseCommand :: String -> [Command]
parseCommand command
    | "addx " `isPrefixOf` command = [Noop, Addx (read (drop 5 command) :: Int)]
    | command == "noop"            = [Noop]

solve :: [Command] -> [[Char]]
solve commands = registerValueAfterCycles initStateMachine commands

registerValueAfterCycles :: StateMachine -> [Command] -> [[Char]]
registerValueAfterCycles stateMachine []                 = screenRowToMatrix $ screen stateMachine
registerValueAfterCycles stateMachine (command:commands) = registerValueAfterCycles newStateMachine commands
        where
            stateMachineAfterExecutedCommand = executeCommand stateMachine command
            condition                        = abs (((length $ screen stateMachine) `mod` 40 ) - (registerX stateMachine)) <= 1
            newStateMachine                  = stateMachineAfterExecutedCommand { screen = (screen stateMachine) ++ [if condition then '#' else '.'] }

executeCommand :: StateMachine -> Command -> StateMachine
executeCommand stateMachine Noop             = incrementCycle stateMachine
executeCommand stateMachine (Addx increment) = (incrementCycle stateMachine) { registerX = (registerX stateMachine) + increment }

screenRowToMatrix :: [Char] -> [[Char]]
screenRowToMatrix []  = []
screenRowToMatrix row = [take 40 row] ++ screenRowToMatrix (drop 40 row)

showScreen :: [[Char]] -> String
showScreen = intercalate "\n"
