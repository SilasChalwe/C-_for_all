// ============================================================
// sorting/quick_sort.cpp
// Algorithm: Quick Sort — O(n log n) avg, O(n²) worst
// Author: Silas Chalwe
// ============================================================
//
// Idea: Divide and Conquer.
//   1. Choose a pivot element.
//   2. Partition: put elements smaller than pivot to the left,
//      larger to the right.
//   3. Recursively sort sub-arrays.
//
// In-place, cache-friendly, generally the fastest in practice.
// Worst case (always picking smallest/largest) avoided by
// choosing a random or median-of-three pivot.
// ============================================================

#include <iostream>
#include <vector>
#include <cstdlib>  // rand

// Lomuto partition scheme
int partition(std::vector<int>& arr, int low, int high) {
    // Randomise pivot to improve average performance
    int randIdx = low + rand() % (high - low + 1);
    std::swap(arr[randIdx], arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(const std::vector<int>& arr, const std::string& label = "") {
    if (!label.empty()) std::cout << label << ": ";
    for (int v : arr) std::cout << v << " ";
    std::cout << std::endl;
}

int main() {
    srand(42); // fixed seed for reproducibility

    std::vector<int> data = {10, 7, 8, 9, 1, 5};
    printArray(data, "Before");
    quickSort(data, 0, static_cast<int>(data.size()) - 1);
    printArray(data, "After ");

    std::vector<int> dups = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    quickSort(dups, 0, static_cast<int>(dups.size()) - 1);
    printArray(dups, "Dups  ");

    return 0;
}
