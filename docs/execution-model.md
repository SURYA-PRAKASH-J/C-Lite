# Execution Model

C-Lite uses a tree-walking interpreter to execute the Abstract Syntax Tree.

## Values and Types

All values in C-Lite are represented by a `Value` structure:

- `TYPE_INT`: Integer values.
- `TYPE_BOOL`: Boolean values (internally 0 or 1).
- `TYPE_CHAR`: Single characters.
- `TYPE_STR`: Heap-allocated strings.

The interpreter handles dynamic type checks and conversions, such as string concatenation (e.g., `string + int`).

## Symbol Table & Scoping

C-Lite implements **Lexical Scoping** using a stack-based symbol table:

- **Global Scope**: Variables declared outside any block.
- **Block Scope**: Variables declared within `{ }`.
- **Shadowing**: Variables in inner scopes can shadow variables in outer scopes.
- **Cleanup**: When a block finishes execution, its local variables are automatically removed from the symbol table.

## Control Flow

Control flow is handled by conditionally traversing AST nodes:

- `IfNode`: Evaluates the condition; if non-zero, executes the body block; otherwise, executes the optional `else` block.
- `WhileNode`: Repeatedly evaluates the condition and executes the body block as long as the condition remains non-zero.

## Error Handling

The interpreter performs basic error checking:

- Undefined variable usage.
- Redeclaration of variables in the same scope.
- Division by zero.
