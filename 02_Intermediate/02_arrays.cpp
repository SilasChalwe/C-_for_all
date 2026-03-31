// ============================================================
// 02_arrays.cpp
// Topic: C-style arrays, 2-D arrays, std::array
// Author: Silas Chalwe
// ============================================================

#include <iostream>
#include <array>     // std::array
#include <algorithm> // std::sort, std::find

int main() {
    // ---- 1-D C-style array ----
    int scores[5] = {85, 92, 78, 95, 88};
    std::cout << "=== 1-D Array ===" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << "scores[" << i << "] = " << scores[i] << std::endl;
    }

    // Array size trick (only works for stack arrays, not pointers)
    int size = sizeof(scores) / sizeof(scores[0]);
    std::cout << "Array size: " << size << std::endl;

    // ---- 2-D array — a grid/matrix ----
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    std::cout << "\n=== 2-D Array (3x3 Matrix) ===" << std::endl;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            std::cout << matrix[r][c] << " ";
        }
        std::cout << std::endl;
    }

    // ---- std::array (safer, knows its own size) ----
    std::array<int, 5> arr = {3, 1, 4, 1, 5};
    std::cout << "\n=== std::array ===" << std::endl;
    std::cout << "Size: " << arr.size() << std::endl;

    // Sort using STL algorithm
    std::sort(arr.begin(), arr.end());
    std::cout << "Sorted: ";
    for (int v : arr) std::cout << v << " ";
    std::cout << std::endl;

    // Search
    auto it = std::find(arr.begin(), arr.end(), 4);
    if (it != arr.end()) {
        std::cout << "Found 4 at index " << (it - arr.begin()) << std::endl;
    }

    // Accessing first/last safely
    std::cout << "Front: " << arr.front() << "  Back: " << arr.back() << std::endl;

    // ---- Passing arrays to functions ----
    // C-style arrays decay to pointers, so size must be passed separately.
    // std::array can be passed by reference without losing size info.

    return 0;
}
