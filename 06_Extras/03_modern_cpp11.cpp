// ============================================================
// 03_modern_cpp11.cpp
// Topic: C++11 features — auto, range-for, lambdas, nullptr,
//        move semantics, initialiser lists, uniform initialisation
// Author: Silas Chalwe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <utility>   // std::move

// ---- Move semantics demo ----
class BigData {
    std::vector<int> data;
public:
    explicit BigData(size_t n) : data(n, 0) {
        std::cout << "[BigData] constructed (n=" << n << ")\n";
    }
    // Copy constructor
    BigData(const BigData& other) : data(other.data) {
        std::cout << "[BigData] copy constructed\n";
    }
    // Move constructor — transfers ownership, no data copy
    BigData(BigData&& other) noexcept : data(std::move(other.data)) {
        std::cout << "[BigData] move constructed\n";
    }
    size_t size() const { return data.size(); }
};

int main() {
    // ---- auto ----
    auto x = 42;
    auto pi = 3.14159;
    auto name = std::string("C++11");
    std::cout << "auto: x=" << x << " pi=" << pi << " name=" << name << "\n";

    // ---- Range-based for ----
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::cout << "Range-for: ";
    for (const auto& elem : v) std::cout << elem << " ";
    std::cout << "\n";

    // Modify via reference
    for (auto& elem : v) elem *= 2;
    std::cout << "Doubled:   ";
    for (auto e : v) std::cout << e << " ";
    std::cout << "\n";

    // ---- nullptr (replaces NULL) ----
    int* nullPtr = nullptr;
    std::cout << "nullPtr is null: " << (nullPtr == nullptr) << "\n";

    // ---- Lambdas ----
    auto square = [](int n){ return n * n; };
    std::cout << "Lambda square(7) = " << square(7) << "\n";

    // Lambda with capture
    int multiplier = 3;
    auto times = [multiplier](int n){ return n * multiplier; };
    std::cout << "Capture lambda 5*3 = " << times(5) << "\n";

    // Lambda with mutable capture (modify the copy)
    int count = 0;
    auto increment = [count]() mutable { return ++count; };
    std::cout << "Mutable lambda: " << increment() << " " << increment() << "\n";
    std::cout << "Original count (unchanged): " << count << "\n";

    // Lambda stored in a variable, used with algorithms
    std::sort(v.begin(), v.end(), [](int a, int b){ return a > b; });
    std::cout << "Sorted desc: ";
    for (auto e : v) std::cout << e << " ";
    std::cout << "\n";

    // ---- Uniform initialisation ----
    std::vector<std::string> words{"hello", "world", "c++11"};
    struct Point { int x, y; };
    Point p{3, 4};
    std::cout << "Point: (" << p.x << "," << p.y << ")\n";

    // ---- Move semantics ----
    std::cout << "\n=== Move Semantics ===\n";
    BigData a(1000);
    BigData b = std::move(a);   // move, not copy — a is now in a valid but unspecified state
    std::cout << "b.size()=" << b.size() << "\n";

    // ---- unique_ptr / make_unique (C++14, shown here) ----
    auto up = std::make_unique<int>(99);
    std::cout << "unique_ptr value: " << *up << "\n";

    // ---- constexpr ----
    constexpr int MAX = 100;
    constexpr double HALF = MAX / 2.0;
    std::cout << "constexpr MAX=" << MAX << " HALF=" << HALF << "\n";

    return 0;
}
