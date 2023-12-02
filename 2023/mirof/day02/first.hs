import Text.Read
import Data.Char

---------------- Models ----------------

data Group = Group {
    red   :: Integer,
    green :: Integer,
    blue  :: Integer
} deriving (Eq, Show)

empty_group :: Group
empty_group = Group { red = 0, green = 0, blue = 0 }

data Game = Game {
    iden   :: Integer,
    groups :: [Group]
} deriving (Eq, Show)

instance Num Group where
    (+) first second = Group { 
                           red =   (red first)   + (red second),
                           green = (green first) + (green second), 
                           blue =  (blue first)  + (blue second) 
                       }

    fromInteger 0 = empty_group -- needed for sum

---------------- Parsing ---------------

parse :: String -> [Game]
parse = map parse_line . lines

parse_line :: String -> Game
parse_line line = Game { iden = iden , groups = (parse_groups empty_group (drop 2 tokens)) }
    where 
        tokens = map (\word -> if last word == ',' then init word else word) $ words line -- remove end comma if present
        iden   = read (init (tokens !! 1)) :: Integer -- removes ':' at end

parse_groups :: Group -> [String] -> [Group] 
parse_groups group []   = [group] -- last character is not ';' so we record group

parse_groups group (num:"red"  :rest) = parse_groups (group + empty_group { red   = read num :: Integer }) rest
parse_groups group (num:"green":rest) = parse_groups (group + empty_group { green = read num :: Integer }) rest
parse_groups group (num:"blue" :rest) = parse_groups (group + empty_group { blue  = read num :: Integer }) rest

parse_groups group (num:"red;"  :rest) = (group + empty_group { red   = read num :: Integer }) : parse_groups empty_group rest 
parse_groups group (num:"green;":rest) = (group + empty_group { green = read num :: Integer }) : parse_groups empty_group rest 
parse_groups group (num:"blue;" :rest) = (group + empty_group { blue  = read num :: Integer }) : parse_groups empty_group rest 

----------------- Solve ----------------

solve :: [Game] -> Integer
solve games = sum $ map iden valid_games
    where
        valid_games = filter (\game -> all condition $ groups game) games
        condition = \group -> red group <= 12 && green group <= 13 && blue group <= 14

------------------ Main ----------------

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

