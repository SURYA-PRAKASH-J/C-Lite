# C-Lite

**C-Lite** is a minimal, C-inspired interpreted programming language written entirely from scratch in C. It features a hand-written lexer, a recursive-descent parser, and an AST-based interpreter.

The main reason I created this is to explore how actual programming languages work behind the scenes. Also for my own satisfaction and fun.

C-Lite is intentionally small, explicit, and educational.

## Language Features

C-Lite supports core programming constructs with explicit typing:

### Core Types & Variables
- **Primitive Types**: `int`, `bool`, `char`, `string` (or `str`).
- **Declarations**: Explicit typing (e.g., `int a = 10;`).
- **Assignments**: Standard variable updates.

### Control Flow
- **If-Else**: Conditional execution with optional `else` and `else if` blocks.
- **While Loops**: Standard loop constructs for repetitive execution.
- **Scoping**: Block-level scoping with `{ }`.

### Operators & Logic
- **Arithmetic**: `+`, `-`, `*`, `/`.
- **Comparison**: `==`, `!=`, `<`, `>`, `<=`, `>=`.
- **Logical**: `&&` (AND), `||` (OR), `!` (NOT).
- **String Concatenation**: Automatic conversion and concatenation using the `+` operator.

### Built-in Statements
- **echo**: Prints values to the console.
- **endl**: Keyword for multiple newlines (e.g., `echo "Hello" endl endl;`).

## Example

```c
int a = 10;
string name = "C-Lite";

if (a > 5) {
    echo "Welcome to " + name;
    echo "Value is: " + a endl;
}

int i = 0;
while (i < 3) {
    echo i;
    i = i + 1;
}
```

## Implementation Details

C-Lite follows a classic interpreter pipeline:

1.  **Hand-written Lexer**: Tokenizes source text into a stream of typed tokens.
2.  **Recursive-Descent Parser**: Builds an **Abstract Syntax Tree (AST)** from the token stream.
3.  **AST Interpreter**: Traverses the AST and executes nodes using a stack-based symbol table for scoping.

No code generation tools (like Flex/Bison) are used. Every token and rule is implemented explicitly in C.

> [!NOTE]
> All core language logic, the lexer, parser, and interpreter were entirely hand-written. AI was only utilized for structuring the documentation and writing this README.

## Project Structure

```text
C-Lite/
├── include/       # Header files defining types and interfaces
├── src/           # Implementation of lexer, parser, and interpreter
├── docs/          # Detailed design and grammar specifications
├── Makefile       # Build configuration
└── examples/      # Sample scripts (.cl files)
```

## Getting Started

### Building

Ensure you have `gcc` and `make` installed.

```bash
make
```

### Running

Run the interpreter with a C-Lite source file:

```bash
./clite text.cl
```

For debug output (tokens and execution trace):

```bash
./clite text.cl --debug
```

## Documentation

Detailed technical notes are available in the `docs/` directory:
- [Architecture](docs/architecture.md): Overview of the execution pipeline.
- [Execution Model](docs/execution-model.md): Symbol tables, scoping, and value representation.
- [Grammar](docs/grammer.md): Formal language specification.

## Contributions

- Surya Prakash J [obviously me]

Contributions, issues, and feature requests are welcome!
Feel free to fork the repo and submit a pull request.

## Why This Project

Because I thought how hard could it be (*Pretty hard actually*)

## License

MIT

## Author

Surya Prakash J
