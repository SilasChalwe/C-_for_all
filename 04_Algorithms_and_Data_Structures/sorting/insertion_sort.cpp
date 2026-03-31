// ============================================================
// sorting/insertion_sort.cpp
// Algorithm: Insertion Sort — O(n²) worst, O(n) best (nearly sorted)
// Author: Silas Chalwe
// ============================================================
//
// Idea: Build a sorted sub-array one element at a time.
// Each new element is inserted into its correct position in
// the already-sorted portion — like sorting a hand of cards.
// Efficient for small or nearly-sorted arrays.
// ============================================================

#include <iostream>
#include <vector>

void insertionSort(std::vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    for (int i = 1; i < n; i++) {
        int key = arr[i];   // element to insert
        int j = i - 1;
        // Shift elements that are greater than key one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;   // insert key at correct position
    }
}

void printArray(const std::vector<int>& arr, const std::string& label = "") {
    if (!label.empty()) std::cout << label << ": ";
    for (int v : arr) std::cout << v << " ";
    std::cout << std::endl;
}

int main() {
    std::vector<int> data = {12, 11, 13, 5, 6};
    printArray(data, "Before");
    insertionSort(data);
    printArray(data, "After ");

    // Nearly sorted — insertion sort shines here
    std::vector<int> nearly = {1, 2, 4, 3, 5, 6};
    insertionSort(nearly);
    printArray(nearly, "Nearly sorted");

    return 0;
}
