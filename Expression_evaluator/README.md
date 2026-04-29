# Expression Evaluator (Mini Compiler using Stack)

An expression evaluator written in C++ that parses and computes mathematical expressions. It utilizes stack-based algorithms to convert expressions from **infix** to **postfix** notation before evaluating them efficiently.

This project demonstrates core computer science concepts such as abstract data structures (Stacks), string parsing, algorithm implementation (Shunting Yard algorithm logic), and structured error handling.

## Features

- **Infix to Postfix Conversion:** Parses natural human-readable mathematical inputs.
- **Stack-based Evaluation:** Evaluates postfix notation computationally efficiently.
- **Operator Precedence Handling:** Accurately respects order of operations (`^`, `*`, `/`, `+`, `-`).
- **Parentheses Support:** Handles nested expressions correctly.
- **Floating-point Math:** Supports decimals (e.g., `2.5 * 4`).
- **Robust Error Handling:** Safely catches division by zero, mismatched parentheses, and invalid characters.

## How to Compile and Run

Make sure you have a C++ compiler installed (like `g++` or `clang++`).

1. Open a terminal.
2. Navigate to the project directory.
3. Compile the code:
   ```bash
   g++ -o evaluator expression_evaluator.cpp
   ```
4. Run the executable:
   ```bash
   ./evaluator
   ```

## Example Usage

```text
========================================================
    Expression Evaluator (Mini Compiler using Stack)    
========================================================
Supported operations: +, -, *, /, ^ (Power), () (Parentheses)
Type 'exit' to quit.

Enter expression > 3 + 4 * 2 / ( 1 - 5 ) ^ 2
  [Debug] Postfix string: 3 4 2 * 1 5 - 2 ^ / + 
  [Result] 3.5
--------------------------------------------------------
Enter expression > 10 / 0
  [Debug] Postfix string: 10 0 / 
  [Error] Division by zero!
--------------------------------------------------------
Enter expression > (5 + 3
  [Error] Mismatched parentheses!
--------------------------------------------------------
```

## Technical Concepts Applied

1. **Stack Data Structure:** Uses `std::stack` to temporarily store operators during parsing and operands during evaluation.
2. **String Manipulation:** Traverses the string dynamically extracting multi-digit integer and decimal tokens.
3. **Exception Handling:** Uses `try-catch` blocks and `std::runtime_error` to build a bulletproof REPL interface.
