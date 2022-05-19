module Lexer where

data Symbol = Add | Sub | Mul | Div | ParO | ParC | Num Integer
  deriving (Show)

parseNum :: [Char] -> [Symbol]
parseNum [] = []
parseNum s = [Num (read s :: Integer)]

lexer :: String -> [Char] -> [Symbol]
lexer [] b = parseNum b
lexer ('+':r) b = (parseNum b) ++ [Add] ++ lexer r []
lexer ('-':r) b = (parseNum b) ++ [Sub] ++ lexer r []
lexer ('*':r) b = (parseNum b) ++ [Mul] ++ lexer r []
lexer ('/':r) b = (parseNum b) ++ [Div] ++ lexer r []
lexer ('(':r) b = (parseNum b) ++ [ParO] ++ lexer r []
lexer (')':r) b = (parseNum b) ++ [ParC] ++ lexer r []
lexer (' ':r) b = (parseNum b) ++ lexer r []
lexer (c:r) b = lexer r (b ++ [ c ])

