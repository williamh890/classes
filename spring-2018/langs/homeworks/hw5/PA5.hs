-- PA5.hs
-- William Horn
-- 21 Mar 2018
--
-- For CS F331 / CSCE A331 Spring 2018
-- Solutions to Assignment 5 Exercise B

module PA5 where


collatzCounts = map collatzCount [1..]

collatzCount n
    | isBaseCase n = 0
    | isBaseCase (collatz n) = 1
    | otherwise = 1 + numberOfStepsFor n

isBaseCase n = n == 1
numberOfStepsFor n = collatzCount (collatz n)

collatz n
    | n == 0 = 0
    | mod n 2 == 0 = div n 2
    | otherwise = 3 * n + 1


findList sub main =
    checkForSubListAtIndex 0 sub main

checkForSubListAtIndex n subList mainList
    | isEndOfMainList subList mainList = Nothing
    | isThereASubList subList mainList = Just n
    | otherwise                        = checkForSubListAtIndex (n + 1) subList (theRestOf mainList)

isEndOfMainList subList mainList =
    (length subList) > (length mainList)

isThereASubList subList mainList =
    subList == take (length subList) mainList

getLenOfSubElsFrom subList mainList =
    (take (length subList) mainList)

theRestOf list =
    drop 1 list


lhs ## rhs = getNumEqual lhs rhs startingCount

startingCount = 0
getNumEqual [] _ n = n
getNumEqual _ [] n = n
getNumEqual (x:xs) (y:ys) n
    | x == y    = getNumEqual xs ys n+1
    | otherwise = getNumEqual xs ys n


filterAB f mask values =
    getMaskedValues f mask values []

getMaskedValues _ [] _  trueValues = trueValues
getMaskedValues _  _ [] trueValues = trueValues
getMaskedValues f (m:mask) (v:values) trueValues
    | isMaskTrue f m = getMaskedValues f mask values (trueValues ++ [v])
    | otherwise      = getMaskedValues f mask values trueValues

isMaskTrue f m = f m


sumEvenOdd nums = totals where
    tuplePieces = seperateOddsAndEvens nums
    evens = foldr (+) 0 (first  tuplePieces)
    odds  = foldr (+) 0 (second tuplePieces)
    totals = (evens, odds)

seperateOddsAndEvens [] = ([], [])
seperateOddsAndEvens [x] = ([x],[])
seperateOddsAndEvens (even:odd:nums) =
    (even:evens, odd:odds) where
        (evens, odds) = seperateOddsAndEvens nums

first  (x, _) = x
second (_, y) = y
