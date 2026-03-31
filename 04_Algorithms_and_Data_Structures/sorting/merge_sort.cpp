// ============================================================
// sorting/merge_sort.cpp
// Algorithm: Merge Sort — O(n log n) time, O(n) space
// Author: Silas Chalwe
// ============================================================
//
// Idea: Divide and Conquer.
//   1. Divide array into two halves.
//   2. Recursively sort each half.
//   3. Merge the two sorted halves.
//
// Stable sort — preserves relative order of equal elements.
// Preferred for linked lists and large data sets.
// ============================================================

#include <iostream>
#include <vector>

// Merge two sorted sub-arrays arr[l..m] and arr[m+1..r]
void merge(std::vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Temporary arrays
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else               arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(std::vector<int>& arr, int l, int r) {
    if (l >= r) return;         // base case: single element
    int m = l + (r - l) / 2;   // avoid overflow vs (l+r)/2
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

void printArray(const std::vector<int>& arr, const std::string& label = "") {
    if (!label.empty()) std::cout << label << ": ";
    for (int v : arr) std::cout << v << " ";
    std::cout << std::endl;
}

int main() {
    std::vector<int> data = {38, 27, 43, 3, 9, 82, 10};
    printArray(data, "Before");
    mergeSort(data, 0, static_cast<int>(data.size()) - 1);
    printArray(data, "After ");

    std::vector<int> large = {5, 2, 8, 1, 9, 3, 7, 4, 6, 10, 0, -1};
    mergeSort(large, 0, static_cast<int>(large.size()) - 1);
    printArray(large, "Large ");

    return 0;
}
