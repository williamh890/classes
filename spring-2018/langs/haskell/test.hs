module Main where

import System.Environment

fibopair 0 = (0, 1)
fibopair n = (b, a+b) where
    (a, b) = fibopair (n-1)

fibo n = a where
    (a, b) = fibopair n

allfibos = map fibo [0..]

somefibos = take 5 allfibos

-- | 'main' runs the main program
main = do
    putStrLn "Fibonacci Numbers"
    putStrLn ""


haqify s = "Haq! " ++ s
