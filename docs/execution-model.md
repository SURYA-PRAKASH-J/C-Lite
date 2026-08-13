# C-Lite Interpreter Execution Model

This document outlines how values, variables, scopes, and control flow are managed at runtime by the C-Lite AST interpreter.

## Values and Types

At runtime, all values are encapsulated in a `Value` struct (defined in [AST.h](file:///home/surya/C-Lite/include/AST.h)):

* **`TYPE_INT`**: Represents 32-bit signed integers.
* **`TYPE_BOOL`**: Represents boolean flags (`true` / `false`), represented internally as `1` or `0`.
* **`TYPE_CHAR`**: Represents single-byte characters (e.g., `'A'`).
* **`TYPE_STR`**: Represents heap-allocated, null-terminated strings.

---

## Type System & Coercion Rules

C-Lite permits certain implicit conversions during variable assignment and binary operations:

### 1. Working Conversions
* **String to Int**: Evaluates to the length of the string.
  ```c
  string s = "Hello";
  int len = s; // len becomes 5
  ```
* **String to Char**: Evaluates to the first character of the string.
  ```c
  string s = "Hello";
  char c = s; // c becomes 'H'
  ```
* **Char + Char**: Concatenating two characters produces a two-character heap-allocated string.
  ```c
  char c1 = 'A';
  char c2 = 'B';
  string s = c1 + c2; // s becomes "AB"
  ```
* **Mixed-Type String Concatenation**: When adding a string to another type, the other type is automatically formatted as a string.
  ```c
  echo "Value: " + 42; // prints "Value: 42"
  ```

### 2. Known Limitations & Crashes
* **Primitive-to-String Coercion**: Direct assignment of non-string values to a string variable (e.g. `string s = 10;` or `string s = true;`) is **unsupported** and triggers an interpreter segmentation fault (due to calling `strdup` on a `NULL` string pointer).
  * **Workaround**: Force concatenation with an empty string: `string s = "" + 10;`.

---

## Symbol Table & Lexical Scoping

Variables are managed inside a flat array of `Symbol` structures up to a capacity of 128 variables.

### Scoping Rules
* **Stack Depth**: Blocks `{ }` increment the `current_depth` counter. 
* **Shadowing**: When resolving a variable name, the interpreter scans the symbol array backwards (from newest to oldest), returning the first match. This allows variables in inner blocks to shadow outer variables.
* **Cleanup**: On block exit, any variables whose declaration depth matches the block's depth are discarded from the stack.

---

## Function Execution Scoping (Important Quirks)

Functions in C-Lite behave as procedures (they cannot return values, and return statements are not implemented). They are stored in a global `FunctionTable`.

Due to the way the interpreter executes function calls:
1. **Parameter Insertion**: Arguments are evaluated and inserted into the symbol table **before** entering the function body block.
2. **Scoping Level**: Because of this, parameters are bound at the **caller's** depth (e.g. depth `0` for global calls) instead of the function's internal scope depth.
3. **Implications**:
   - **Name Conflicts**: If a parameter has the same name as a variable already declared in the caller's current scope, the interpreter aborts with `Error: Redeclared in same scope!`.
   - **Parameter Leaks**: When the function exits, parameters are **not** cleaned up and will leak into the caller's scope, persisting as active variables.
   - **Best Practice**: Use unique parameter names that do not overlap with variables in the calling environment.

---

## Control Flow Execution

* **If Statements**: The interpreter evaluates the condition expression. If its numeric value is non-zero (or `true`), the body block executes. If zero, the `else` branch (if present) is executed.
* **While Loops**: The condition expression is evaluated before each loop iteration. As long as it evaluates to a non-zero value, the body block is executed.
