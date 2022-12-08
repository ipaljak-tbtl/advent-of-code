{-# LANGUAGE NamedFieldPuns #-}

module Parser (parse, Terminal(..), Folder(..), File(..)) where

import Data.List (isPrefixOf)

data File = File
    { filename :: String
    , size     :: Int
    } deriving (Show)

data Folder = Folder
    { name    :: String
    , files   :: [File]
    , folders :: [Folder]
    } deriving (Show)

data Terminal = Terminal
    { current_directory :: String
    , root              :: Folder
    } deriving (Show)

initializeTerminal :: Terminal
initializeTerminal = Terminal { current_directory = "/", root = Folder { name = "/", files = [], folders = [] } }

parse :: String -> Terminal
parse input = parseCommands (lines input) initializeTerminal

parseCommands :: [String] -> Terminal -> Terminal
parseCommands []                 terminal = terminal
parseCommands (command:commands) terminal
    | "$ cd /"  == command         = parseCommands commands                  $ cdToRoot   terminal
    | "$ cd .." == command         = parseCommands commands                  $ cdBack     terminal
    | "$ ls"    == command         = parseCommands (removeLsOutput commands) $ listFolder terminal $ lsOutput commands
    | "$ cd " `isPrefixOf` command = parseCommands commands                  $ cdFolder   terminal $ drop 5 command
    | otherwise                    = error ("Could not match command: " ++ command)
        where
            lsCondition (first_letter:_) = first_letter /= '$'
            removeLsOutput               = dropWhile lsCondition
            lsOutput                     = takeWhile lsCondition

cdToRoot :: Terminal -> Terminal
cdToRoot Terminal { current_directory, root } = Terminal { current_directory = "/", root }

cdBack :: Terminal -> Terminal
cdBack Terminal { current_directory, root } = Terminal { current_directory = new_current_directory, root }
    where
        new_current_directory = removeLastFolder current_directory
        removeLastFolder      = reverse . dropWhile ((/=) '/') . drop 1 . reverse

cdFolder :: Terminal -> String -> Terminal
cdFolder Terminal { current_directory, root } folder = Terminal { current_directory = new_current_directory, root }
    where
        new_current_directory = current_directory ++ folder ++ "/"

listFolder :: Terminal -> [String] -> Terminal
listFolder terminal []                 = terminal
listFolder terminal (command:commands) = listFolder (insert terminal command) commands

insert :: Terminal -> String -> Terminal
insert terminal command
    | "dir " `isPrefixOf` command = terminal { root = insertFolder (root terminal) path $ drop 4 command }
    | otherwise                   = terminal { root = insertFile   (root terminal) path command }
        where
            path = (words . tail) [ if c == '/' then ' ' else c | c <- current_directory terminal ]

insertFolder :: Folder -> [String] -> String -> Folder
insertFolder folder []         new_folder_name = folder { folders = (folders folder ++ [ new_folder ]) }
    where
        new_folder = Folder { name = new_folder_name, files = [], folders = [] }
insertFolder folder (dir:path) new_folder_name = folder { folders = updated_folders }
    where
        updated_folders = map (\folder -> if (name folder) == dir then insertFolder folder path new_folder_name else folder) $ folders folder


insertFile :: Folder -> [String] -> String -> Folder
insertFile folder []         ls_output_line = folder { files = (files folder ++ [ new_file ]) }
    where
        new_file = File { filename, size }
        filename =       (last . words) ls_output_line
        size     = read ((head . words) ls_output_line) :: Int
insertFile folder (dir:path) ls_output_line = folder { folders = updated_folders }
    where
        updated_folders = map (\folder -> if (name folder) == dir then insertFile folder path ls_output_line else folder) $ folders folder

