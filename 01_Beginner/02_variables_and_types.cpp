// ============================================================
// 02_variables_and_types.cpp
// Topic: Variables, primitive data types, sizeof
// Author: Silas Chalwe
// ============================================================
//
// A variable is a named storage location in memory.
// C++ is statically typed — every variable must have a declared type.
// ============================================================

#include <iostream>
#include <string>   // for std::string
#include <climits>  // for INT_MAX, INT_MIN etc.

int main() {
    // ---- Integer types ----
    int age = 25;                  // typically 4 bytes, holds whole numbers
    short s = 32000;               // typically 2 bytes
    long l = 1000000L;             // at least 4 bytes
    long long ll = 9000000000LL;   // at least 8 bytes
    unsigned int population = 8000000000U; // no negative values

    // ---- Floating-point types ----
    float  pi_f = 3.14f;           // ~6-7 significant digits
    double pi_d = 3.14159265358979; // ~15-16 significant digits

    // ---- Character type ----
    char grade = 'A';              // single character, stored as ASCII code

    // ---- Boolean type ----
    bool isLearning = true;        // true (1) or false (0)

    // ---- String (not a primitive, but very common) ----
    std::string name = "Silas Chalwe";

    // ---- Print values ----
    std::cout << "Name    : " << name       << std::endl;
    std::cout << "Age     : " << age        << std::endl;
    std::cout << "Grade   : " << grade      << std::endl;
    std::cout << "Pi (f)  : " << pi_f       << std::endl;
    std::cout << "Pi (d)  : " << pi_d       << std::endl;
    std::cout << "Learning: " << isLearning  << std::endl;

    // ---- sizeof operator ----
    std::cout << "\n--- sizeof (bytes) ---" << std::endl;
    std::cout << "int        : " << sizeof(int)       << std::endl;
    std::cout << "long long  : " << sizeof(long long) << std::endl;
    std::cout << "double     : " << sizeof(double)    << std::endl;
    std::cout << "char       : " << sizeof(char)      << std::endl;
    std::cout << "bool       : " << sizeof(bool)      << std::endl;

    // ---- Integer limits ----
    std::cout << "\n--- Limits ---" << std::endl;
    std::cout << "INT_MAX = " << INT_MAX << std::endl;
    std::cout << "INT_MIN = " << INT_MIN << std::endl;

    // ---- auto keyword: compiler deduces the type ----
    auto x = 42;       // deduced as int
    auto y = 3.14;     // deduced as double
    auto z = "hello";  // deduced as const char*
    std::cout << "\nauto x=" << x << "  y=" << y << "  z=" << z << std::endl;

    return 0;
}
