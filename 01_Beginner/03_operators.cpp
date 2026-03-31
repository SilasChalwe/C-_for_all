// ============================================================
// 03_operators.cpp
// Topic: Arithmetic, relational, logical, and bitwise operators
// Author: Silas Chalwe
// ============================================================

#include <iostream>

int main() {
    // ---- Arithmetic operators ----
    int a = 10, b = 3;
    std::cout << "=== Arithmetic ===" << std::endl;
    std::cout << "a + b = " << (a + b) << std::endl;  // addition
    std::cout << "a - b = " << (a - b) << std::endl;  // subtraction
    std::cout << "a * b = " << (a * b) << std::endl;  // multiplication
    std::cout << "a / b = " << (a / b) << std::endl;  // integer division (truncates)
    std::cout << "a % b = " << (a % b) << std::endl;  // modulus (remainder)

    // Increment / decrement
    int c = 5;
    std::cout << "c++ = " << c++ << std::endl; // post-increment: use then add
    std::cout << "c   = " << c   << std::endl; // c is now 6
    std::cout << "++c = " << ++c << std::endl; // pre-increment: add then use

    // ---- Relational (comparison) operators ----
    std::cout << "\n=== Relational ===" << std::endl;
    std::cout << "a == b : " << (a == b) << std::endl; // equal
    std::cout << "a != b : " << (a != b) << std::endl; // not equal
    std::cout << "a >  b : " << (a >  b) << std::endl; // greater than
    std::cout << "a <  b : " << (a <  b) << std::endl; // less than
    std::cout << "a >= b : " << (a >= b) << std::endl; // greater or equal
    std::cout << "a <= b : " << (a <= b) << std::endl; // less or equal

    // ---- Logical operators ----
    bool x = true, y = false;
    std::cout << "\n=== Logical ===" << std::endl;
    std::cout << "x && y : " << (x && y) << std::endl; // AND
    std::cout << "x || y : " << (x || y) << std::endl; // OR
    std::cout << "!x     : " << (!x)     << std::endl; // NOT

    // ---- Bitwise operators ----
    int p = 0b1010, q = 0b1100; // binary literals (C++14)
    std::cout << "\n=== Bitwise (p=10, q=12) ===" << std::endl;
    std::cout << "p & q  = " << (p & q)  << std::endl; // AND  -> 1000 = 8
    std::cout << "p | q  = " << (p | q)  << std::endl; // OR   -> 1110 = 14
    std::cout << "p ^ q  = " << (p ^ q)  << std::endl; // XOR  -> 0110 = 6
    std::cout << "~p     = " << (~p)     << std::endl; // NOT (bitwise complement)
    std::cout << "p << 1 = " << (p << 1) << std::endl; // left shift  (multiply by 2)
    std::cout << "p >> 1 = " << (p >> 1) << std::endl; // right shift (divide by 2)

    // ---- Assignment operators ----
    int n = 10;
    n += 5;  std::cout << "\nn += 5 → " << n << std::endl;
    n -= 3;  std::cout << "n -= 3 → " << n << std::endl;
    n *= 2;  std::cout << "n *= 2 → " << n << std::endl;
    n /= 4;  std::cout << "n /= 4 → " << n << std::endl;
    n %= 3;  std::cout << "n %= 3 → " << n << std::endl;

    // ---- Ternary (conditional) operator ----
    int max = (a > b) ? a : b;
    std::cout << "\nMax of " << a << " and " << b << " is " << max << std::endl;

    return 0;
}
