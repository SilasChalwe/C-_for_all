// ============================================================
// 07_functions.cpp
// Topic: Declaring, defining, calling, and overloading functions
// Author: Silas Chalwe
// ============================================================
//
// A function is a reusable block of code that performs a specific task.
// Benefits: avoids code duplication, makes programs easier to read and test.
// ============================================================

#include <iostream>
#include <string>

// ---- Function declaration (prototype) ----
// Tells the compiler the function exists before it is used.
void greet(const std::string& name);
int  add(int a, int b);
double add(double a, double b);  // overloaded add for doubles
int  factorial(int n);
void printLine(char ch = '-', int len = 40); // default parameter values

// ============================================================
int main() {
    // ---- Calling a void function ----
    greet("Silas");

    // ---- Calling a function that returns a value ----
    int sum = add(3, 7);
    std::cout << "3 + 7 = " << sum << std::endl;

    // ---- Function overloading ----
    // The compiler picks the correct version based on argument types
    double dsum = add(1.5, 2.5);
    std::cout << "1.5 + 2.5 = " << dsum << std::endl;

    // ---- Recursive function ----
    std::cout << "5! = " << factorial(5) << std::endl;

    // ---- Default parameters ----
    printLine();          // uses defaults: '-', 40
    printLine('=', 20);   // override both defaults
    printLine('*');       // override only the character

    return 0;
}

// ============================================================
// Function definitions
// ============================================================

// void function — returns nothing
void greet(const std::string& name) {
    std::cout << "Hello, " << name << "!" << std::endl;
}

// Function returning int
int add(int a, int b) {
    return a + b;
}

// Overloaded add for double (same name, different parameter types)
double add(double a, double b) {
    return a + b;
}

// Recursive function — calls itself with a smaller input
int factorial(int n) {
    if (n <= 1) return 1;     // base case: prevents infinite recursion
    return n * factorial(n - 1); // recursive call
}

// Function with default parameter values
void printLine(char ch, int len) {
    for (int i = 0; i < len; i++) {
        std::cout << ch;
    }
    std::cout << std::endl;
}
