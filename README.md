# C-Lite

**C-Lite** is a minimal, C-inspired interpreted scripting language written entirely from scratch in C. It features a hand-written lexer, a recursive-descent parser, and an Abstract Syntax Tree (AST) tree-walking interpreter.

This project was built to explore how compilers/interpreters work behind the scenes, without relying on code generation tools like Flex/Bison.

---

## Language Features

### Core Types & Variables
- **Primitive Types**: `int`, `bool`, `char`, `string` (or `str`).
- **Variable Declarations**: Explicit typing (e.g. `int a = 10;`, `string name = "C-Lite";`).
- **Variable Assignments**: Reassigning values without repeating the type (e.g. `a = 20;`).

### Scope & Shadowing
- Block-level lexical scoping using `{ }`.
- Variable shadowing: inner scopes can shadow variables defined in outer scopes.

### Control Flow
- **If-Else**: Conditional execution with optional `else` and `else if` blocks. Parentheses around conditions are optional.
- **While Loops**: Repeats execution as long as the condition is non-zero (or true).

### Operators & Logic
- **Arithmetic**: `+` (addition/concatenation), `-` (subtraction/negation), `*` (multiplication), `/` (integer division).
- **Comparison**: `==`, `!=`, `<`, `>`, `<=`, `>=`.
- **Logical**: `&&` (AND), `||` (OR), `!` (NOT).
- **String Concatenation**: Automatic coercion of other primitives to strings when using the `+` operator (e.g., `"Value: " + 42` evaluates to `"Value: 42"`).

### Functions / Procedures
- Declared using name and parameters: `myFunction(int paramA, bool paramB) { ... }`.
- Can be called like: `myFunction(10, true);`.
- Functions do not specify a return type and currently do not support return statements (they act as procedures).
- *Note*: Function parameters are added directly to the caller's scope level and leak after function completion (see [Execution Model Docs](docs/execution-model.md) for details).

### Built-in Statements
- **echo**: Prints expression values. Example: `echo "Hello " + name;`.
- **endl**: Increments the newline count when placed at the end of an echo statement. Example: `echo "Hello" endl endl;` (prints "Hello" followed by three newlines).

---

## Technical Documentation

Detailed technical design notes are available in the `docs/` directory:
- [Architecture](docs/architecture.md): Execution pipeline stages, file structure, and diagrams.
- [Execution Model](docs/execution-model.md): Type system conversion rules, scoping mechanisms, and interpreter quirks.
- [Grammar Specification](docs/grammar.md): Formal EBNF rules defining tokens, statements, and operator precedence.
- [Documentation Index](docs/index.html): Simple local browser landing page.

---

## Project Structure

```text
C-Lite/
├── include/       # C header files defining AST, Lexer, Parser, and Interpreter
├── src/           # C source code files
├── docs/          # Technical documentation and specs
├── examples/      # Well-commented sample .cl scripts
├── Makefile       # GCC compiler build configuration
└── LICENSE        # Project license
```

---

## Getting Started

### Prerequisites
Make sure you have GCC compiler and Make installed.
```bash
sudo apt install build-essential
```

### Building C-Lite
Compile the interpreter executable using the provided Makefile:
```bash
make
```
This builds the `clite` executable in the root workspace directory.

### Running Scripts
Run the interpreter on a source file:
```bash
./clite examples/basics.cl
```

To enable token and execution debug logging:
```bash
./clite examples/basics.cl --debug
```

---

## Examples Catalog

Check the [examples/](file:///home/surya/C-Lite/examples) directory for working demo scripts:
1. **[basics.cl](file:///home/surya/C-Lite/examples/basics.cl)**: Variable declarations, printing, basic arithmetic, and logical expressions.
2. **[control_flow.cl](file:///home/surya/C-Lite/examples/control_flow.cl)**: Conditionals (`if`/`else if`/`else`), block scoping, variable shadowing, and `while` loop iteration.
3. **[functions.cl](file:///home/surya/C-Lite/examples/functions.cl)**: Declaring and invoking procedures, parameter passing, and scoping behavior.
4. **[type_conversions.cl](file:///home/surya/C-Lite/examples/type_conversions.cl)**: Working conversions (length extraction, first char extraction, type mixing in string concatenation) and warnings about coercion limitations.

---

## License

MIT
