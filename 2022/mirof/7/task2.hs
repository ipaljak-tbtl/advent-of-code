{-# LANGUAGE NamedFieldPuns #-}

import Text.Read
import Parser (parse, Terminal(..), Folder(..), File(..))

main = do
    input <- readFile "input.txt"
    let solution = solve (parse input)
    putStrLn $ show solution

memorySize         = 70000000
updateRequiredSize = 30000000

solve :: Terminal -> Int
solve terminal = minimalSize
    where
        neededAdditionalSpace = updateRequiredSize - (memorySize - folderSize (root terminal))
        minimalSize           = foldr1 min $ filter (\s -> s >= neededAdditionalSpace) $ findAllFolderSizes (root terminal)

findAllFolderSizes :: Folder -> [Int]
findAllFolderSizes folder = (folderSize folder) : (concat $ map findAllFolderSizes (folders folder))

folderSize :: Folder -> Int
folderSize Folder { name, files = [], folders = [] } = 0
folderSize Folder { name, files, folders }           = filesSize + foldersSize
    where
        filesSize   = sum $ map size       files
        foldersSize = sum $ map folderSize folders
