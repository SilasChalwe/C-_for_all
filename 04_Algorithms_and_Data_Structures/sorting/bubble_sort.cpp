// ============================================================
// sorting/bubble_sort.cpp
// Algorithm: Bubble Sort — O(n²) time, O(1) space
// Author: Silas Chalwe
// ============================================================
//
// Idea: Repeatedly step through the list, compare adjacent elements,
// and swap them if they are in the wrong order.
// The largest element "bubbles" to the top each pass.
// Optimisation: stop early if no swaps were made (already sorted).
// ============================================================

#include <iostream>
#include <vector>

void bubbleSort(std::vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        // After each outer iteration, the last i elements are in place
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // array is already sorted
    }
}

void printArray(const std::vector<int>& arr, const std::string& label = "") {
    if (!label.empty()) std::cout << label << ": ";
    for (int v : arr) std::cout << v << " ";
    std::cout << std::endl;
}

int main() {
    std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};
    printArray(data, "Before");
    bubbleSort(data);
    printArray(data, "After ");

    // Edge cases
    std::vector<int> empty = {};
    std::vector<int> single = {42};
    std::vector<int> sorted = {1, 2, 3, 4, 5};
    std::vector<int> reversed = {5, 4, 3, 2, 1};

    bubbleSort(empty);    printArray(empty,    "Empty   ");
    bubbleSort(single);   printArray(single,   "Single  ");
    bubbleSort(sorted);   printArray(sorted,   "Sorted  ");
    bubbleSort(reversed); printArray(reversed, "Reversed");

    return 0;
}
