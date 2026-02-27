# Execution Model

Variables are stored in a global symbol table.

Boolean logic is represented using integers:
0 → false
non-zero → true

Expressions are evaluated using operator precedence rules implemented in recursive-descent functions.

Control flow:
- if statements evaluate expression first
- if result != 0, block executes
- otherwise skipped