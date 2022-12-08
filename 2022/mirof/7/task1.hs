{-# LANGUAGE NamedFieldPuns #-}

import Text.Read
import Parser (parse, Terminal(..), Folder(..), File(..))

main = do
    input <- readFile "input.txt"
    let solution = solve (parse input) 100000
    putStrLn $ show solution

solve :: Terminal -> Int -> Int
solve terminal limit = foldersLessThan (root terminal) limit

foldersLessThan :: Folder -> Int -> Int
foldersLessThan folder limit
    | folderFullSize <= limit = folderFullSize + otherFoldersLessThanSize
    | otherwise               =                  otherFoldersLessThanSize
        where
            folderFullSize           = (sum $ map (folderSize)                              (folders folder)) + (sum $ map size (files folder))
            otherFoldersLessThanSize =  sum $ map (\folder -> foldersLessThan folder limit) (folders folder)

folderSize :: Folder -> Int
folderSize Folder { name, files = [], folders = [] } = 0
folderSize Folder { name, files, folders }           = filesSize + foldersSize
    where
        filesSize   = sum $ map size       files
        foldersSize = sum $ map folderSize folders
