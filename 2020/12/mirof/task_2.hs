data Direction = DEast | DWest | DSouth | DNorth
    deriving Show
data Action = AFront | ANorth | ASouth | AEast | AWest | ALeft | ARight
    deriving Show

main :: IO ()
main = readFile "problem_2.txt" >>= putStrLn . show . getManhattanDistance . parseInputData

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
getManhattanDistance actions = getManhattanDistance' (DEast, (0, 0), (10, 1)) actions

getManhattanDistance' :: (Direction, (Int, Int), (Int, Int)) -> [Action] -> Int
getManhattanDistance' (_, (x, y), _) []          =  abs x + abs y
getManhattanDistance' state          (a:actions) = getManhattanDistance' newState actions
    where newState = applyAction state a

applyAction :: (Direction, (Int, Int), (Int, Int)) -> Action -> (Direction, (Int, Int), (Int, Int))
applyAction (direct, ss, (xw, yw)) ARight = (direct, ss, (yw,  -xw))
applyAction (direct, ss, (xw, yw)) ALeft  = (direct, ss, (-yw, xw ))

applyAction (direct, (x, y), (xw, yw)) AFront = (direct, (x + xw, y + yw), (xw, yw))

applyAction (direct, (x, y), (xw, yw)) ANorth = (direct, (x, y), (xw,     yw + 1))
applyAction (direct, (x, y), (xw, yw)) ASouth = (direct, (x, y), (xw,     yw - 1))
applyAction (direct, (x, y), (xw, yw)) AWest  = (direct, (x, y), (xw - 1, yw    ))
applyAction (direct, (x, y), (xw, yw)) AEast  = (direct, (x, y), (xw + 1, yw    ))

