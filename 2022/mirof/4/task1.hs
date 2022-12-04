import Text.Read

data ElfTasks = ElfTasks
    { start :: Integer
    , end   :: Integer
    } deriving (Show)

main = do
    input <- readFile "input.txt"
    let solution = solve $ parse input
    putStrLn $ show solution

parse :: String -> [(ElfTasks, ElfTasks)]
parse = map parseLine . lines

parseLine :: String -> (ElfTasks, ElfTasks)
parseLine line = (ElfTasks { start = start1, end = end1 } , ElfTasks { start = start2, end = end2 })
    where
        splitted_line = words $ [if c `elem` [',', '-'] then ' ' else c | c <- line]
        start1 = readInteger $ splitted_line !! 0
        end1   = readInteger $ splitted_line !! 1
        start2 = readInteger $ splitted_line !! 2
        end2   = readInteger $ splitted_line !! 3

readInteger :: String -> Integer
readInteger input = read input :: Integer

solve :: [(ElfTasks, ElfTasks)] -> Integer
solve [] = 0
solve ((elf1, elf2):tasks)
    | start elf1 >= start elf2 && end elf1 <= end elf2 = 1 + solve tasks
    | start elf2 >= start elf1 && end elf2 <= end elf1 = 1 + solve tasks
    | otherwise = 0 + solve tasks
