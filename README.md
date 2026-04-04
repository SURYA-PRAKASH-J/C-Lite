# C-Lite

**C-Lite** is a minimal, C-inspired interpreted programming language written entirely from scratch in C.

The main reason I created such is to explore how actual programming language works behind the scenes. Also for my own satisfaction and fun.

C-Lite is intentionally small, explicit, and educational.

## Language Overview

### Example

```C-Lite
int a = 10;
int b = (a * 2) + 5;

if (b > 20) {
    echo b;
}
```

## C-Lite currently supports

### Core Features

- Integer variables
- Variable declaration and assignment
- Arithmetic expressions (+ - * /)
- Parentheses with correct operator precedence
- Single-line comments (//)

### Comparison & Boolean Logic

- > < >= <= == !=
- Boolean values represented as:
  - 0 → false
  - 1 → true

### Control Flow

- Basic if statements
- Built-in Statement
- echo for printing values
- While loop

## Implementation Details

C-Lite is built using:

- Hand-written lexer (no generator tools)
- Recursive-descent parser
- Direct execution during parsing (current architecture)

No code generation tools. No hidden abstractions.
Every token and rule is implemented explicitly.

## Project Structure

```Tree
C-Lite/
├── LICENSE  
├── Makefile  
├── README.md  
├── alphabets.cl
├── clite
├── docs
│   ├── architecture.md
│   ├── execution-model.md
│   └── grammer.md
├── include
│   ├── AST.h
│   ├── expr.h
│   ├── interpreter.h
│   ├── lexer.h
│   └── parser.h
├── src
│   ├── AST.c
│   ├── expr.c
│   ├── interpreter.c
│   ├── lexer.c
│   ├── main.c
│   └── parser.c
└── text.cl

```

## Building

Using gcc:

```bash
make
```

Or manually:

```bash
gcc -Wall -Wextra -o out src/*.c
```

Run:

```bash
./out test.cl
```

### Debug mode

```bash
./out test.cl --debug
```

## Design Philosophy

- Flexiblity
- structured

## Roadmap

Planned improvements:

- While loops
- Explicit AST representation
- Separation of parsing and execution
- Possible IR or bytecode stage

## Documentation

Detailed language specification and design notes can be found in the docs/ directory.
**Note:** Docs under development

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
