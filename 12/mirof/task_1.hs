data Direction = DEast | DWest | DSouth | DNorth
    deriving Show
data Action = AFront | ANorth | ASouth | AEast | AWest | ALeft | ARight
    deriving Show

main :: IO ()
main = readFile "problem_1.txt" >>= putStrLn . show . getManhattanDistance . parseInputData

parseInputData :: String -> [Action]
parseInputData = concat . map parseAction . lines

parseAction :: String -> [Action]
parseAction ('N':xs) = expandAction ANorth (read xs :: Int)
parseAction ('S':xs) = expandAction ASouth (read xs :: Int)
parseAction ('E':xs) = expandAction AEast  (read xs :: Int)
parseAction ('W':xs) = expandAction AWest  (read xs :: Int)
parseAction ('F':xs) = expandAction AFront (read xs :: Int)
parseAction "R90"    = expandAction ARight 1
parseAction "R180"   = expandAction ARight 2
parseAction "R270"   = expandAction ARight 3
parseAction "L90"    = expandAction ALeft  1
parseAction "L180"   = expandAction ALeft  2
parseAction "L270"   = expandAction ALeft  3

expandAction :: Action -> Int -> [Action]
expandAction action 0     = []
expandAction action count = action : expandAction action (count - 1)

getManhattanDistance :: [Action] -> Int
getManhattanDistance actions = getManhattanDistance' (DEast, 0, 0) actions

getManhattanDistance' :: (Direction, Int, Int) -> [Action] -> Int
getManhattanDistance' (_, x, y) []          =  abs x + abs y
getManhattanDistance' state     (a:actions) = getManhattanDistance' newState actions
    where newState = applyAction state a

applyAction :: (Direction, Int, Int) -> Action -> (Direction, Int, Int)
applyAction (DNorth, x, y) ARight = (DEast,  x, y)
applyAction (DEast , x, y) ARight = (DSouth, x, y)
applyAction (DSouth, x, y) ARight = (DWest,  x, y)
applyAction (DWest,  x, y) ARight = (DNorth, x, y)

applyAction (DNorth, x, y) ALeft  = (DWest,  x, y)
applyAction (DWest,  x, y) ALeft  = (DSouth, x, y)
applyAction (DSouth, x, y) ALeft  = (DEast,  x, y)
applyAction (DEast,  x, y) ALeft  = (DNorth, x, y)

applyAction (DNorth, x, y) AFront = (DNorth, x,     y + 1)
applyAction (DSouth, x, y) AFront = (DSouth, x,     y - 1)
applyAction (DWest,  x, y) AFront = (DWest,  x - 1, y    )
applyAction (DEast,  x, y) AFront = (DEast,  x + 1, y    )

applyAction (direct, x, y) ANorth = (direct, x,     y + 1)
applyAction (direct, x, y) ASouth = (direct, x,     y - 1)
applyAction (direct, x, y) AWest  = (direct, x - 1, y    )
applyAction (direct, x, y) AEast  = (direct, x + 1, y    )

