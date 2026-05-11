# C-Lite Grammar

The following is the formal grammar for C-Lite, represented in a variant of EBNF.

## Top-Level
```text
program        → statement*
```

## Statements
```text
statement      → declaration
               | assignment
               | if_statement
               | while_statement
               | echo_statement
               | block

declaration    → type IDENTIFIER "=" expression ";"
type           → "int" | "bool" | "char" | "string" | "str"

assignment     → IDENTIFIER "=" expression ";"

if_statement   → "if" expression block ( "else" ( if_statement | block ) )?

while_statement → "while" expression block

block          → "{" statement* "}"

echo_statement → "echo" expression ( "endl" )* ";"
```

## Expressions (Precedence: Low to High)
```text
expression     → logic_or

logic_or       → logic_and ( "||" logic_and )*

logic_and      → equality ( "&&" equality )*

equality       → comparison ( ( "==" | "!=" ) comparison )*

comparison     → term ( ( ">" | "<" | ">=" | "<=" ) term )*

term           → factor ( ( "+" | "-" ) factor )*

factor         → unary ( ( "*" | "/" ) unary )*

unary          → ( "!" | "-" ) unary 
               | primary

primary        → INTEGER
               | STRING_LITERAL
               | CHAR_LITERAL
               | IDENTIFIER
               | "true"
               | "false"
               | "(" expression ")"
```

## Tokens
-   `IDENTIFIER`: `[a-zA-Z_][a-zA-Z0-9_]*`
-   `INTEGER`: `[0-9]+`
-   `STRING_LITERAL`: `"[^"]*"`
-   `CHAR_LITERAL`: `'[^']'`
