-- PA5.hs  INCOMPLETE
-- Glenn G. Chappell
-- 21 Mar 2018
--
-- For CS F331 / CSCE A331 Spring 2018
-- Solutions to Assignment 5 Exercise B

module PA5 where


-- collatzCounts
collatzCounts :: [Integer]
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


-- findList
findList :: Eq a => [a] -> [a] -> Maybe Int
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


-- operator ##
(##) :: Eq a => [a] -> [a] -> Int
lhs ## rhs = getNumEqual lhs rhs startingCount -- DUMMY; REWRITE THIS!!!

startingCount = 0
getNumEqual [] _ n = n
getNumEqual _ [] n = n
getNumEqual (x:xs) (y:ys) n
    | x == y = getNumEqual xs ys n+1
    | otherwise = getNumEqual xs ys n

-- filterAB
filterAB :: (a -> Bool) -> [a] -> [b] -> [b]
filterAB _ _ bs = bs  -- DUMMY; REWRITE THIS!!!


-- sumEvenOdd
sumEvenOdd :: Num a => [a] -> (a, a)
{-
  The assignment requires sumEvenOdd to be written using a fold.
  Something like this:

    sumEvenOdd xs = fold* ... xs where
        ...

  Above, "..." should be replaced by other code. The "fold*" must be
  one of the following: foldl, foldr, foldl1, foldr1.
-}
sumEvenOdd _ = (0, 0)  -- DUMMY; REWRITE THIS!!!

