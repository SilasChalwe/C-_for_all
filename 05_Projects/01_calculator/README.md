# Project 1 – Command-Line Calculator

**Author:** Silas Chalwe

## Description
A fully interactive command-line calculator that supports basic arithmetic operations, memory storage, and history viewing.

## Concepts Used
- Functions and function overloading
- `switch` statements
- Loops and input validation
- `std::stack` for history

## Requirements
- C++17 compiler (GCC/Clang/MSVC)

## How to Compile & Run
```bash
g++ -std=c++17 -Wall -o calculator main.cpp && ./calculator
```

## Example Session
```
=== C++ Calculator ===
Commands: +, -, *, /, %, ^, sqrt, history, clear, quit

Enter expression (e.g. 5 + 3): 10 + 5
= 15

Enter expression: 15 * 2
= 30

Enter expression: history
[2] 15 * 2 = 30
[1] 10 + 5 = 15
```
