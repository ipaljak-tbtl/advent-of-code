import Data.List (isPrefixOf)
import Text.Read

data Command = Addx Int  | Noop deriving (Show, Eq)

data StateMachine = StateMachine {
    cycleCounter :: Int,
    registerX    :: Int
}

initStateMachine :: StateMachine
initStateMachine = StateMachine { cycleCounter = 1, registerX = 1 }

incrementCycle :: StateMachine -> StateMachine
incrementCycle stateMachine = stateMachine { cycleCounter = (cycleCounter stateMachine) + 1 }

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

parse :: String -> [Command]
parse = foldl (++) [] . map parseCommand . lines

parseCommand :: String -> [Command]
parseCommand command
    | "addx " `isPrefixOf` command = [Noop, Addx (read (drop 5 command) :: Int)]
    | command == "noop"            = [Noop]

solve :: [Command] -> Int
solve commands = sum $ map (\limitCycles -> limitCycles * (registerValueAfterCycles limitCycles initStateMachine commands)) wantedLimitCycles
    where wantedLimitCycles = [20, 60, 100, 140, 180, 220]

registerValueAfterCycles :: Int -> StateMachine -> [Command] -> Int
registerValueAfterCycles _           _            []                 = error "There shouldn't be lack of commands!!!"
registerValueAfterCycles limitCycles stateMachine (command:commands)
    | cycleCounter stateMachine == limitCycles = registerX stateMachine
    | otherwise                                = registerValueAfterCycles limitCycles (executeCommand stateMachine command) commands

executeCommand :: StateMachine -> Command -> StateMachine
executeCommand stateMachine Noop             = incrementCycle stateMachine
executeCommand stateMachine (Addx increment) = (incrementCycle stateMachine) { registerX = (registerX stateMachine) + increment }
