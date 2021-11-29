
remainder  = 20201227
subjectNum = 7
publicKeyCard = 6930903
publicKeyDoor = 19716708

main = (putStrLn . show) (calculateEncryptionKey 1 (defineLoop 1 1))

defineLoop :: Integer -> Integer -> (Integer, Integer)
defineLoop value currentLoop
    | result == publicKeyCard = (currentLoop, publicKeyDoor)
    | result == publicKeyDoor = (currentLoop, publicKeyCard)
    | otherwise               = defineLoop result (currentLoop + 1)
        where result = (value * subjectNum) `mod` remainder

calculateEncryptionKey :: Integer -> (Integer, Integer) -> Integer
calculateEncryptionKey value (0, _)          = value
calculateEncryptionKey value (loop, subjNum) = calculateEncryptionKey (value * subjNum `mod` remainder) (loop-1, subjNum)
