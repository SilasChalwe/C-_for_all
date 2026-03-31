// ============================================================
// 04_pointers.cpp
// Topic: Pointer syntax, pointer arithmetic, null pointers
// Author: Silas Chalwe
// ============================================================
//
// A pointer is a variable that stores a memory address.
// Pointers are fundamental to low-level C++ programming,
// dynamic memory, and data structures.
// ============================================================

#include <iostream>

int main() {
    // ---- Declaring and initialising a pointer ----
    int value = 42;
    int* ptr = &value;  // & = "address-of" operator; ptr holds the address of value

    std::cout << "=== Basic Pointer Usage ===" << std::endl;
    std::cout << "value         = " << value  << std::endl;
    std::cout << "address (&v)  = " << ptr    << std::endl; // memory address
    std::cout << "dereferenced  = " << *ptr   << std::endl; // * = dereference

    // Modifying the value through the pointer
    *ptr = 100;
    std::cout << "After *ptr=100, value = " << value << std::endl;

    // ---- Null pointer (always initialise unused pointers to nullptr) ----
    int* nullPtr = nullptr;
    if (nullPtr == nullptr) {
        std::cout << "\nnullPtr is null — safe to check before dereferencing" << std::endl;
    }

    // ---- Pointer to pointer ----
    int x = 5;
    int* p = &x;
    int** pp = &p;   // pointer to a pointer
    std::cout << "\n=== Pointer to Pointer ===" << std::endl;
    std::cout << "x    = " << x    << std::endl;
    std::cout << "*p   = " << *p   << std::endl;
    std::cout << "**pp = " << **pp << std::endl;

    // ---- Pointer arithmetic ----
    // Moving a pointer steps through consecutive memory locations.
    int arr[] = {10, 20, 30, 40, 50};
    int* aPtr = arr;  // array name is a pointer to its first element

    std::cout << "\n=== Pointer Arithmetic ===" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << "*(aPtr + " << i << ") = " << *(aPtr + i) << std::endl;
    }

    // ---- Pointer and array equivalence ----
    std::cout << "\narr[2] == *(arr+2): " << (arr[2] == *(arr + 2)) << std::endl;

    // ---- const pointer vs pointer to const ----
    int a = 10, b = 20;

    const int* ptrToConst = &a;   // can't modify *ptrToConst, but ptr can change
    // *ptrToConst = 99;  // ERROR

    int* const constPtr = &a;     // ptr is fixed, but *constPtr can change
    *constPtr = 99;
    // constPtr = &b;  // ERROR

    const int* const bothConst = &b; // neither ptr nor *ptr can change

    std::cout << "\na after *constPtr=99: " << a << std::endl;
    (void)ptrToConst; (void)bothConst; // suppress unused variable warnings

    return 0;
}
