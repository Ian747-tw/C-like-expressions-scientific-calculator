# Scientific Calculator Requirements

The program must read and evaluate integer infix expressions and print detailed
conversion/evaluation output for each input line until EOF. The implementation
should use pure recursion (no explicit stack or iterative parsing algorithms).

## Input handling
- Repeatedly read a full line from stdin, length <= 1000000.
- Stop when no more lines can be read (EOF).

## Output requirements per line
- Show stack operations that transform the infix expression to a postfix one.
- Show the corresponding postfix expression.
- Show the evaluated result. The result must match the value produced by a
  normal C statement for the same expression.

## Supported operators and functions
- Multiplicative: `*`, `/`, `%`.
- Additive: binary `+`, binary `-`.
- Bitwise: `&`, `^`, `|`, `<<`, `>>`.
- Parentheses: `(`, `)`.
- Unary: unary `-`, unary `+`, bitwise not `~`.
- Logical: `&&`, `||`, logical not `!`.
  - `&&` returns 1 if both operands are non-zero, else 0.
  - `||` returns 1 if either operand is non-zero, else 0.
  - `!` returns 0 if operand is non-zero, else 1.
- Equality: `==`, `!=`.
  - Return 1 if true, else 0.
- Functions: `sin`, `cos`, `exp`, `log`, `pow`, `sqrt`, `fabs`.
