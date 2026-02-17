# C‑Lite

C‑Lite is a **small, C‑inspired programming language** and compiler project written from scratch in **C**.

This project exists for one reason: **to understand how languages actually work** — lexing, parsing, grammar, and semantics — without hiding behind tools like Flex/Bison.

It is intentionally minimal, explicit, and educational.

---

## Goals

* Build a lexer by hand (no generator tools)
* Build a recursive‑descent parser by hand
* Understand how statements and expressions are recognized
* Learn how languages represent meaning internally (AST / symbols)
* Keep the implementation simple, readable, and hackable

This is **not** meant to be fast, production‑ready, or feature‑rich.
It *is* meant to be correct, clear, and instructive.

---

## Current Features

* Hand‑written lexer
* Tokenization of:

  * keywords (`int`)
  * identifiers
  * integer literals
  * assignment operator (`=`)
  * semicolon (`;`)
* Hand‑written recursive‑descent parser
* Supports multiple statements
* Statement types:

  * Variable declaration

    ```c
    int a = 10;
    ```
  * Assignment statement

    ```c
    a = 11;
    ```
* Expression parsing (`+ - * /`):

  * Supports comments with '//'
  * Supports basic mathematical operations with basic precedence and paranthesis
    ```c
    int a = 10 + 10 - 5;
    int b = (a / 15) * 3;
    // comments works too
    ```

* Supports boolean operations based on 0 [false] and 1 [true]
* Supports Comparative operators:
  ```c
     int a = 10 < 5; // a will be 0
  ```
* Supported Comparative Operations:

  * Greater Than ( > )
  * Lesser Than ( < )
  * Greater Than or Equal To ( >= )
  * Lesser Than or Equal To ( <= )
  * Equals To ( == )
  * Not Equals TO ( != )

* Supports basic 'if' statements
  
  ```c
  if 0{ 
    statements;
  }
  ```

  - The expression can be with or without paranthesis ' () '
* Debug mode to trace lexer behavior [use  ```out.o text.cl --debug```]

## Example Program

```c
int a = 10;
a = 11;
int c = 1111;
```

---

## Project Structure

```
C-Lite/
├── lexer.c        # Lexical analysis (tokenizer)
├── lexer.h
├── parser.c       # Recursive-descent parser
├── parser.h
├── main.c         # Entry point / driver
├── README.md
```

---

## Building

This project is built with **gcc**.

I have Makefile too.

to compile:

```
make
```
or

```bash
gcc -Wall -Wextra -o out main.c lexer.c parser.c expr.c
```

Run:

```bash
./out test.cl
```

Debug mode:

```bash
./out test.cl --debug
```

---

## Design Philosophy

* No code generation tools
* No hidden magic
* One token, one rule
* Grammar before optimization
* Readability over cleverness

C‑Lite is written the way **early compilers were written**: explicitly and incrementally.

---

## Planned Features

* While loops
* AST representation
* Optional interpreter or IR generation

---

## Why "C‑Lite"?

C‑Lite is a deliberately small subset inspired by C‑like syntax, designed for learning and experimentation rather than completeness.

---

## Status

🚧 **Active development**

Expect breaking changes, refactors, and redesigns as understanding improves.

---

## License

MIT

---

## Author

Surya Prakash

---

