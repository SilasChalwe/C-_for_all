// ============================================================
// 05_modern_cpp20.cpp
// Topic: C++20 features — Concepts, Ranges, std::span, designated initialisers
// Author: Silas Chalwe
// Compile: g++ -std=c++20 -Wall -o output 05_modern_cpp20.cpp && ./output
//
// Requirements: GCC 10+ / Clang 10+ / MSVC 2019+
// ============================================================

#include <iostream>
#include <concepts>   // C++20
#include <ranges>     // C++20
#include <span>       // C++20
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

// ============================================================
// CONCEPTS — constrain template parameters at compile time
// ============================================================

// Custom concept: type must support + and be comparable
template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

// Use the concept to constrain a template function
template <Addable T>
T addTwo(T a, T b) {
    return a + b;
}

// Using standard library concepts
template <std::integral T>
T factorial(T n) {
    T result = 1;
    for (T i = 2; i <= n; i++) result *= i;
    return result;
}

// ============================================================
// RANGES — composable, lazy range adaptors
// ============================================================
void rangesDemo() {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Filter even numbers, then square them
    auto result = nums
        | std::views::filter([](int n){ return n % 2 == 0; })
        | std::views::transform([](int n){ return n * n; });

    std::cout << "Even squares: ";
    for (int v : result) std::cout << v << " ";
    std::cout << "\n";

    // Take first 3 elements
    auto firstThree = nums | std::views::take(3);
    std::cout << "First three: ";
    for (int v : firstThree) std::cout << v << " ";
    std::cout << "\n";

    // Reverse
    std::cout << "Reversed: ";
    for (int v : nums | std::views::reverse) std::cout << v << " ";
    std::cout << "\n";

    // iota view — generate a range
    std::cout << "iota 1..5: ";
    for (int v : std::views::iota(1, 6)) std::cout << v << " ";
    std::cout << "\n";
}

// ============================================================
// std::span — non-owning view over contiguous data
// ============================================================
void printSpan(std::span<const int> s) {
    std::cout << "span[" << s.size() << "]: ";
    for (int v : s) std::cout << v << " ";
    std::cout << "\n";
}

// ============================================================
// Designated initialisers (C++20) — initialise named members
// ============================================================
struct Config {
    int    width  = 800;
    int    height = 600;
    bool   fullscreen = false;
    std::string title = "Default";
};

int main() {
    // Concepts
    std::cout << "=== Concepts ===" << std::endl;
    std::cout << "addTwo(3, 4) = "      << addTwo(3, 4)     << "\n";
    std::cout << "addTwo(1.5, 2.5) = "  << addTwo(1.5, 2.5) << "\n";
    std::cout << "factorial(10) = "     << factorial(10)     << "\n";
    // addTwo("a", "b");  // would fail — strings are not Addable

    // Ranges
    std::cout << "\n=== Ranges ===" << std::endl;
    rangesDemo();

    // std::span
    std::cout << "\n=== std::span ===" << std::endl;
    int arr[] = {10, 20, 30, 40, 50};
    printSpan(arr);                          // span from C array
    std::vector<int> v = {1, 2, 3, 4, 5};
    printSpan(v);                            // span from vector
    printSpan(std::span(v).subspan(1, 3));   // sub-span

    // Designated initialisers
    std::cout << "\n=== Designated Initialisers ===" << std::endl;
    Config cfg = {.width = 1920, .height = 1080, .fullscreen = true, .title = "Game"};
    std::cout << cfg.title << " " << cfg.width << "x" << cfg.height
              << (cfg.fullscreen ? " fullscreen" : "") << "\n";

    return 0;
}
