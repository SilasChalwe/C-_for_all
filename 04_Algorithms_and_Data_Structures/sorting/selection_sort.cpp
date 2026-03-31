// ============================================================
// sorting/selection_sort.cpp
// Algorithm: Selection Sort — O(n²) time, O(1) space
// Author: Silas Chalwe
// ============================================================
//
// Idea: Find the minimum element in the unsorted part and
// place it at the beginning. Repeat for the remaining sub-array.
// Makes at most n-1 swaps (fewer than Bubble Sort).
// ============================================================

#include <iostream>
#include <vector>

void selectionSort(std::vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; i++) {
        // Find the minimum in arr[i..n-1]
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        // Swap it with the first unsorted element
        if (minIdx != i) std::swap(arr[i], arr[minIdx]);
    }
}

void printArray(const std::vector<int>& arr, const std::string& label = "") {
    if (!label.empty()) std::cout << label << ": ";
    for (int v : arr) std::cout << v << " ";
    std::cout << std::endl;
}

int main() {
    std::vector<int> data = {64, 25, 12, 22, 11};
    printArray(data, "Before");
    selectionSort(data);
    printArray(data, "After ");

    std::vector<int> rev = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    selectionSort(rev);
    printArray(rev, "Reversed");

    return 0;
}
