-- median.hs
-- William Horn
-- 21 Mar 2018
--
-- For CS F331 / CSCE A331 Spring 2018
-- Solutions to Assignment 5 Exercise C

import System.IO
import Data.List
import Data.Char


main = do
    putStrLn "- enter list of numbers to calculate the median -"
    answer <- median
    hFlush stdout
    do
        putStrLn "median: "
        print (answer)
    hFlush stdout

    putStrLn "restart? (y/n)"
    restart <- getLine
    if map toLower restart == "y" then
        main
    else do
        putStrLn "\n"


numbers = do
    putStrLn "enter number (enter to calculate) "
    input <- getLine
    if input == "" then
        return []
    else do
        let num = read input ::Int
        next <- numbers
        return (num: next)

median = do
    nums <- numbers
    do
        sortedInput <- sortInputNumbers (nums)
        len <- getNumberOfInputValues (sortedInput)
        middle <- getMiddle (len)
        return (sortedInput !! middle)

sortInputNumbers list = do
    return (sort list)

getNumberOfInputValues list = do
    return (length list)

getMiddle len = do
    return (div len 2)
