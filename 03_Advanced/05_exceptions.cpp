// ============================================================
// 05_exceptions.cpp
// Topic: try / catch / throw, custom exception classes
// Author: Silas Chalwe
// ============================================================
//
// Exceptions provide a structured way to handle runtime errors
// without cluttering normal control flow with error-return codes.
// ============================================================

#include <iostream>
#include <stdexcept>   // std::runtime_error, std::invalid_argument, etc.
#include <string>
#include <vector>
#include <cmath>       // std::sqrt

// ---- Custom exception class ----
class DivisionByZeroException : public std::runtime_error {
public:
    explicit DivisionByZeroException(const std::string& msg = "Division by zero")
        : std::runtime_error(msg) {}
};

class NegativeNumberException : public std::invalid_argument {
    double value;
public:
    NegativeNumberException(double v)
        : std::invalid_argument("Negative number not allowed: " + std::to_string(v)),
          value(v) {}
    double getValue() const { return value; }
};

// ---- Functions that throw ----
double safeDivide(double a, double b) {
    if (b == 0) throw DivisionByZeroException();
    return a / b;
}

double squareRoot(double x) {
    if (x < 0) throw NegativeNumberException(x);
    return std::sqrt(x);
}

// ---- Function that re-throws ----
void processInput(double x) {
    try {
        double result = squareRoot(x);
        std::cout << "sqrt(" << x << ") = " << result << std::endl;
    } catch (const NegativeNumberException& e) {
        std::cout << "[processInput] Caught: " << e.what()
                  << " — re-throwing..." << std::endl;
        throw;  // re-throw for caller to handle
    }
}

// ============================================================
int main() {
    // ---- Basic try / catch ----
    std::cout << "=== Basic exceptions ===" << std::endl;
    try {
        std::cout << safeDivide(10.0, 2.0) << std::endl;
        std::cout << safeDivide(5.0,  0.0) << std::endl;  // throws
    } catch (const DivisionByZeroException& e) {
        std::cout << "Caught DivisionByZero: " << e.what() << std::endl;
    }

    // ---- Catching multiple exception types ----
    std::cout << "\n=== Multiple catch blocks ===" << std::endl;
    double inputs[] = {16.0, -4.0, 0.0, 9.0};
    for (double x : inputs) {
        try {
            std::cout << "sqrt(" << x << ") = " << squareRoot(x) << std::endl;
        } catch (const NegativeNumberException& e) {
            std::cout << "NegativeNumberException: value=" << e.getValue() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "std::exception: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "Unknown exception!" << std::endl;
        }
    }

    // ---- Re-throwing ----
    std::cout << "\n=== Re-throwing ===" << std::endl;
    try {
        processInput(-9.0);
    } catch (const NegativeNumberException& e) {
        std::cout << "[main] Caught re-thrown: " << e.what() << std::endl;
    }

    // ---- Standard library exceptions ----
    std::cout << "\n=== Standard exceptions ===" << std::endl;
    try {
        std::string s = "hello";
        char c = s.at(100);  // throws std::out_of_range
        (void)c;
    } catch (const std::out_of_range& e) {
        std::cout << "out_of_range: " << e.what() << std::endl;
    }

    try {
        std::vector<int> v = {1, 2, 3};
        v.at(10);  // throws std::out_of_range
    } catch (const std::out_of_range& e) {
        std::cout << "vector out_of_range: " << e.what() << std::endl;
    }

    std::cout << "\nProgram continues normally after handled exceptions." << std::endl;
    return 0;
}
