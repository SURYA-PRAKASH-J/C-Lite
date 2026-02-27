# Architecture

C-Lite currently executes code during parsing.

Flow:

Source File
   ↓
Lexer (tokenizes input into Token structs)
   ↓
Parser (recursive descent)
   ↓
Direct evaluation of expressions and statements
   ↓
Output

There is currently no AST. Execution happens immediately as rules are recognized.