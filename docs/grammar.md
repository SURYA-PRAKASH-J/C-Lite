# C-Lite Language Grammar

This document provides the formal syntax specification for the C-Lite programming language. The grammar is described using a variant of Extended Backus-Naur Form (EBNF).

## EBNF Syntax Rules

### Top-Level

```text
program             → statement*
```

### Statements

In C-Lite, statements represent instructions that can be executed. Unlike variables, function declarations do not specify return types and act as procedures.

```text
statement           → declaration
                    | assignment
                    | function_declaration
                    | function_call
                    | if_statement
                    | while_statement
                    | echo_statement
                    | block

declaration         → type IDENTIFIER "=" expression ";"
type                → "int" | "bool" | "char" | "string" | "str"

assignment          → IDENTIFIER "=" expression ";"

function_declaration → IDENTIFIER "(" parameter_list? ")" block
parameter_list      → type IDENTIFIER ( "," type IDENTIFIER )*

function_call       → IDENTIFIER "(" argument_list? ")" ";"
argument_list       → expression ( "," expression )*

if_statement        → "if" expression block ( "else" ( if_statement | block ) )?

while_statement     → "while" expression block

block               → "{" statement* "}"

echo_statement      → "echo" expression ( "endl" )* ";"
```

---

### Expressions & Precedence

Expressions are evaluated to a single `Value`. Operator precedence is implemented in the parser from lowest to highest:

```text
expression          → logic_or

logic_or            → logic_and ( "||" logic_and )*

logic_and           → equality ( "&&" equality )*

equality            → comparison ( ( "==" | "!=" ) comparison )*

comparison          → term ( ( ">" | "<" | ">=" | "<=" ) term )*

term                → factor ( ( "+" | "-" ) factor )*

factor              → unary ( ( "*" | "/" ) unary )*

unary               → ( "!" | "-" ) unary 
                    | primary

primary             → INTEGER
                    | STRING_LITERAL
                    | CHAR_LITERAL
                    | IDENTIFIER
                    | "true"
                    | "false"
                    | "(" expression ")"
```

---

## Lexical Tokens

- **Identifiers**: `[a-zA-Z_][a-zA-Z0-9_]*`
- **Integer Literals**: `[0-9]+`
- **String Literals**: Double-quoted sequences of characters `"[^"]*"`. (Escaped characters like `\"` or `\n` are not processed and are treated as literal characters).
- **Character Literals**: Single-quoted characters `'[^']'`.
- **Comments**: Single-line comments starting with `//`.
