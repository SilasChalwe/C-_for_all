// ============================================================
// 06_dynamic_memory.cpp
// Topic: new / delete, heap vs stack
// Author: Silas Chalwe
// ============================================================
//
// Stack memory: automatically managed, limited in size, fast.
// Heap memory:  manually managed with new/delete, larger, flexible.
//
// Rule: every 'new' must have exactly one matching 'delete'.
// Prefer smart pointers (see 03_Advanced/08_smart_pointers.cpp).
// ============================================================

#include <iostream>

int main() {
    // ---- Allocating a single value on the heap ----
    int* p = new int(42);   // allocates an int, initialises to 42
    std::cout << "Heap int: " << *p << "  at address " << p << std::endl;
    delete p;               // MUST free to avoid memory leak
    p = nullptr;            // good practice: null out the pointer after deletion

    // ---- Allocating an array on the heap ----
    int n;
    std::cout << "\nHow many integers? ";
    std::cin >> n;

    int* arr = new int[n];  // dynamic array — size determined at runtime

    std::cout << "Enter " << n << " integers:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::cout << "You entered: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    delete[] arr;           // [] is required for array deallocation
    arr = nullptr;

    // ---- Stack vs heap comparison ----
    std::cout << "\n--- Stack allocation (automatic) ---" << std::endl;
    {
        int stackVar = 100;    // lives on the stack
        std::cout << "stackVar = " << stackVar << std::endl;
    }
    // stackVar is destroyed here — we cannot access it outside the block

    std::cout << "--- Heap allocation (manual) ---" << std::endl;
    int* heapVar = new int(200);   // lives on the heap
    std::cout << "heapVar = " << *heapVar << std::endl;
    // heapVar is still accessible here — heap lifetime is explicit
    delete heapVar;
    heapVar = nullptr;

    // ---- Allocating a 2-D array on the heap ----
    int rows = 2, cols = 3;
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j;
        }
    }

    std::cout << "\nDynamic 2-D array:" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Free in reverse order
    for (int i = 0; i < rows; i++) delete[] matrix[i];
    delete[] matrix;

    return 0;
}
