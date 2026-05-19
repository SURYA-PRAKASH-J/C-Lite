# Architecture

C-Lite follows a modular interpreter architecture, separating the concerns of scanning, parsing, and execution.

## Pipeline

1. **Source Code**: The user provides a `.cl` file.
2. **Lexer (Scanner)**: The `Lexer` reads the source character by character and groups them into `Token` structures. It handles keywords, identifiers, literals, and comments.
3. **Parser**: A recursive-descent parser consumes the token stream. Instead of direct execution, it constructs an **Abstract Syntax Tree (AST)**.
4. **AST (Abstract Syntax Tree)**: Represents the hierarchical structure of the program. Nodes represent expressions, statements, and blocks.
5. **Interpreter (Evaluator)**: The interpreter traverses the AST recursively. It maintains a symbol table for variable storage and scoping, executing the operations defined by the AST nodes.

## Key Components

- `lexer.c`: Tokenization logic.
- `parser.c` & `expr.c`: Recursive-descent parsing and AST construction.
- `AST.c`: Factory functions for creating AST nodes.
- `interpreter.c`: Evaluation logic for expressions and execution logic for statements.
- `main.c`: Orchestrates the pipeline and handles CLI arguments.
