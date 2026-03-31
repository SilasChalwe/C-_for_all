// ============================================================
// searching/linear_search.cpp
// Algorithm: Linear Search — O(n)
// Author: Silas Chalwe
// ============================================================

#include <iostream>
#include <vector>

// Returns the index of target, or -1 if not found
int linearSearch(const std::vector<int>& arr, int target) {
    for (int i = 0; i < static_cast<int>(arr.size()); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

// Find ALL occurrences
std::vector<int> linearSearchAll(const std::vector<int>& arr, int target) {
    std::vector<int> indices;
    for (int i = 0; i < static_cast<int>(arr.size()); i++) {
        if (arr[i] == target) indices.push_back(i);
    }
    return indices;
}

int main() {
    std::vector<int> data = {4, 2, 9, 7, 5, 3, 8, 1, 6};

    int target = 7;
    int idx = linearSearch(data, target);
    if (idx != -1) std::cout << target << " found at index " << idx << std::endl;
    else           std::cout << target << " not found" << std::endl;

    std::cout << linearSearch(data, 99) << " (not found → -1)" << std::endl;

    // Find all
    std::vector<int> dups = {3, 1, 4, 1, 5, 9, 2, 6, 1, 3};
    auto positions = linearSearchAll(dups, 1);
    std::cout << "All indices of 1: ";
    for (int p : positions) std::cout << p << " ";
    std::cout << std::endl;

    return 0;
}
