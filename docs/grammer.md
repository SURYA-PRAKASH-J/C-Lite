# C-Lite Grammar (Current)

program        → statement*

statement      → declaration
               | assignment
               | if_statement
               | echo_statement

declaration    → "int" IDENTIFIER "=" expression ";"

assignment     → IDENTIFIER "=" expression ";"

if_statement   → "if" expression block

block          → "{" statement* "}"

echo_statement → "echo" expression ";"

expression     → equality

equality       → comparison ( ( "==" | "!=" ) comparison )*

comparison     → term ( ( ">" | "<" | ">=" | "<=" ) term )*

term           → factor ( ( "+" | "-" ) factor )*

factor         → unary ( ( "*" | "/" ) unary )*

unary          → primary

primary        → INTEGER
               | IDENTIFIER
               | "(" expression ")"
