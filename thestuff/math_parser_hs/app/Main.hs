module Main where
import qualified Lexer as L

main :: IO ()
main = print ( L.lexer "(42 + 69) * 2" [] )
-- main = print [ParO, Num 42, Add, Num 69, ParC, Mul, Num 2]
