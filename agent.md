# Scientific Calculator Requirements (Rewrite Plan)

The project has two implementations with different strategies and preprocessing
rules. Both read and evaluate one infix expression per input line until EOF.

## Input handling
- Repeatedly read a full line from stdin, length <= 1000000.
- Stop when no more lines can be read (EOF).

## calculator.cpp (pure recursion)
- Use pure recursion only (no explicit stack or iterative parsing algorithms).
- Before the string enters `main_solve`, apply preprocessing:
  - `log(a,b)` -> `l(a,b)`
  - `pow(a,b)` -> `p(a,b)`
  - `sin(a)` -> `(a)s` (same for other single-argument functions)
- Use the existing `string_process` function; extend it to handle doubles.

## postfix.cpp (stack-based)
- Convert infix to postfix using a stack, then evaluate postfix using a stack.
- Preprocessing rules for function calls:
  - `log(a,b)` -> `((a)(b))l`
  - `sin(a)` -> `(a)s` (same for other single-argument functions)
- Unary handling in infix-to-postfix:
  - `-5` -> `(5)u-`
  - `+3` -> `(3)u+`
  - `... * -(...)` -> `... * (...)u-`

## Supported operators and functions
- Multiplicative: `*`, `/`, `%`.
- Additive: binary `+`, binary `-`.
- Shift: `<<`, `>>`. (stack-based)
- Equality: `==`, `!=` (return 1 if true, else 0). (stack-based)
- Bitwise: `&`, `^`, `|`, unary `~`. (stack-based)
- Logical: `&&`, `||`, unary `!` (C-like truth rules). (stack-based)
- Parentheses: `(`, `)`.
- Functions: `sin`, `cos`, `exp`, `log`, `pow`, `sqrt`, `fabs`.

## Operator precedence (C-like)
1) Parentheses
2) Unary: `+`, `-`, `~`, `!`
3) Multiplicative: `*`, `/`, `%`
4) Additive: `+`, `-`
5) Shift: `<<`, `>>`
6) Equality: `==`, `!=`
7) Bitwise AND: `&`
8) Bitwise XOR: `^`
9) Bitwise OR: `|`
10) Logical AND: `&&`
11) Logical OR: `||`
