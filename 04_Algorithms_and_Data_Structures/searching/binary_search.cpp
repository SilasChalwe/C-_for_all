// ============================================================
// searching/binary_search.cpp
// Algorithm: Binary Search — O(log n)  [array MUST be sorted]
// Author: Silas Chalwe
// ============================================================
//
// Idea: Repeatedly halve the search interval.
//   - Compare target with the middle element.
//   - If equal → found.
//   - If target < middle → search left half.
//   - If target > middle → search right half.
// ============================================================

#include <iostream>
#include <vector>

// Iterative binary search
int binarySearch(const std::vector<int>& arr, int target) {
    int low = 0, high = static_cast<int>(arr.size()) - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;  // avoids overflow
        if (arr[mid] == target) return mid;
        if (arr[mid] <  target) low  = mid + 1;
        else                    high = mid - 1;
    }
    return -1;
}

// Recursive binary search
int binarySearchRecursive(const std::vector<int>& arr, int target, int low, int high) {
    if (low > high) return -1;
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] <  target) return binarySearchRecursive(arr, target, mid + 1, high);
    return binarySearchRecursive(arr, target, low, mid - 1);
}

// Find the first occurrence of target in a sorted array with duplicates
int binarySearchFirst(const std::vector<int>& arr, int target) {
    int low = 0, high = static_cast<int>(arr.size()) - 1, result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) { result = mid; high = mid - 1; } // keep going left
        else if (arr[mid] < target) low  = mid + 1;
        else                        high = mid - 1;
    }
    return result;
}

int main() {
    std::vector<int> sorted = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};

    std::cout << "Array: ";
    for (int v : sorted) std::cout << v << " ";
    std::cout << std::endl;

    // Iterative
    std::cout << "Iterative  search 23 → index " << binarySearch(sorted, 23) << std::endl;
    std::cout << "Iterative  search 99 → index " << binarySearch(sorted, 99) << std::endl;

    // Recursive
    int n = static_cast<int>(sorted.size());
    std::cout << "Recursive  search 56 → index "
              << binarySearchRecursive(sorted, 56, 0, n - 1) << std::endl;

    // First occurrence
    std::vector<int> dups = {1, 2, 2, 2, 3, 4, 5};
    std::cout << "First '2' in {1,2,2,2,3,4,5} → index "
              << binarySearchFirst(dups, 2) << std::endl;

    return 0;
}
