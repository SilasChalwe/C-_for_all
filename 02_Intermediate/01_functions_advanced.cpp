// ============================================================
// 01_functions_advanced.cpp
// Topic: Default arguments, pass-by-value vs pass-by-reference, inline
// Author: Silas Chalwe
// ============================================================

#include <iostream>
#include <string>

// ---- Pass-by-value: a copy is made; the original is unchanged ----
void doubleValue(int x) {
    x *= 2;
    std::cout << "Inside doubleValue: x = " << x << std::endl;
}

// ---- Pass-by-reference: the function works on the original variable ----
void doubleRef(int& x) {
    x *= 2;
}

// ---- Pass by const reference: efficient (no copy) but read-only ----
void printName(const std::string& name) {
    std::cout << "Name: " << name << std::endl;
}

// ---- Default parameter values ----
double power(double base, int exp = 2) {
    double result = 1.0;
    for (int i = 0; i < exp; i++) result *= base;
    return result;
}

// ---- Inline function: hints the compiler to expand the call in-place ----
// Best for tiny, frequently-called functions to avoid function-call overhead.
inline int square(int n) { return n * n; }

// ---- Returning multiple values via references (output parameters) ----
void minMax(const int arr[], int size, int& outMin, int& outMax) {
    outMin = outMax = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < outMin) outMin = arr[i];
        if (arr[i] > outMax) outMax = arr[i];
    }
}

// ============================================================
int main() {
    // Pass-by-value vs pass-by-reference
    int a = 10;
    doubleValue(a);
    std::cout << "After doubleValue: a = " << a << " (unchanged)" << std::endl;

    doubleRef(a);
    std::cout << "After doubleRef:   a = " << a << " (modified)" << std::endl;

    // const reference
    std::string s = "Silas Chalwe";
    printName(s);

    // Default parameters
    std::cout << "power(3)    = " << power(3)    << std::endl; // exp=2
    std::cout << "power(2, 8) = " << power(2, 8) << std::endl;

    // Inline function
    std::cout << "square(7)   = " << square(7) << std::endl;

    // Output parameters
    int nums[] = {5, 2, 9, 1, 7};
    int mn, mx;
    minMax(nums, 5, mn, mx);
    std::cout << "Min=" << mn << "  Max=" << mx << std::endl;

    return 0;
}
