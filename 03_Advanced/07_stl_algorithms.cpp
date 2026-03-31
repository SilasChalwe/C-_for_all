// ============================================================
// 07_stl_algorithms.cpp
// Topic: sort, find, transform, accumulate, lambdas
// Author: Silas Chalwe
// ============================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>      // std::accumulate, std::iota
#include <functional>   // std::greater
#include <string>

int main() {
    std::vector<int> v = {5, 3, 8, 1, 9, 2, 7, 4, 6};

    // ---- std::sort ----
    auto printVec = [](const std::vector<int>& vec, const std::string& label) {
        std::cout << label << ": ";
        for (int x : vec) std::cout << x << " ";
        std::cout << std::endl;
    };

    std::sort(v.begin(), v.end());                     // ascending
    printVec(v, "sort ascending");
    std::sort(v.begin(), v.end(), std::greater<int>()); // descending
    printVec(v, "sort descending");
    std::sort(v.begin(), v.end(), [](int a, int b){ return a < b; }); // lambda
    printVec(v, "sort with lambda");

    // ---- std::find ----
    auto it = std::find(v.begin(), v.end(), 7);
    if (it != v.end()) {
        std::cout << "Found 7 at index " << (it - v.begin()) << std::endl;
    }

    // ---- std::count_if ----
    int evenCount = std::count_if(v.begin(), v.end(), [](int x){ return x % 2 == 0; });
    std::cout << "Even numbers: " << evenCount << std::endl;

    // ---- std::transform — apply a function to each element ----
    std::vector<int> doubled(v.size());
    std::transform(v.begin(), v.end(), doubled.begin(), [](int x){ return x * 2; });
    printVec(doubled, "doubled");

    // ---- std::accumulate — fold/reduce ----
    int sum     = std::accumulate(v.begin(), v.end(), 0);
    int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());
    std::cout << "Sum=" << sum << "  Product=" << product << std::endl;

    // ---- std::min_element / std::max_element ----
    auto minIt = std::min_element(v.begin(), v.end());
    auto maxIt = std::max_element(v.begin(), v.end());
    std::cout << "Min=" << *minIt << "  Max=" << *maxIt << std::endl;

    // ---- std::reverse ----
    std::reverse(v.begin(), v.end());
    printVec(v, "reversed");

    // ---- std::unique (after sort, removes consecutive duplicates) ----
    std::vector<int> dups = {1, 1, 2, 3, 3, 3, 4, 5, 5};
    auto newEnd = std::unique(dups.begin(), dups.end());
    dups.erase(newEnd, dups.end());
    printVec(dups, "unique");

    // ---- std::for_each ----
    std::cout << "for_each squares: ";
    std::for_each(v.begin(), v.end(), [](int x){ std::cout << x*x << " "; });
    std::cout << std::endl;

    // ---- std::iota — fill with incrementing values ----
    std::vector<int> seq(5);
    std::iota(seq.begin(), seq.end(), 1); // 1, 2, 3, 4, 5
    printVec(seq, "iota(1..5)");

    // ---- Lambdas with capture ----
    int threshold = 5;
    auto greaterThanThreshold = [threshold](int x){ return x > threshold; };
    int countAbove = std::count_if(v.begin(), v.end(), greaterThanThreshold);
    std::cout << "Elements > " << threshold << ": " << countAbove << std::endl;

    return 0;
}
