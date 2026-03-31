// ============================================================
// 04_modern_cpp14_17.cpp
// Topic: C++14/17 features — structured bindings, if constexpr,
//        std::optional, std::variant, std::string_view, fold expressions
// Author: Silas Chalwe
// Compile: g++ -std=c++17 -Wall -o output 04_modern_cpp14_17.cpp && ./output
// ============================================================

#include <iostream>
#include <optional>    // C++17
#include <variant>     // C++17
#include <string_view> // C++17
#include <map>
#include <tuple>
#include <string>

// ---- std::optional — value that may or may not exist ----
std::optional<int> divide(int a, int b) {
    if (b == 0) return std::nullopt; // no value
    return a / b;
}

// ---- Structured bindings (C++17) ----
std::pair<std::string, int> getNameAge() {
    return {"Alice", 25};
}

std::tuple<int, double, std::string> getStats() {
    return {42, 3.14, "hello"};
}

// ---- if constexpr (C++17) — compile-time branching in templates ----
template <typename T>
void printType(const T& val) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "Integer: " << val << "\n";
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "Float:   " << val << "\n";
    } else {
        std::cout << "Other:   " << val << "\n";
    }
}

// ---- std::variant — type-safe union ----
using Number = std::variant<int, double, std::string>;

void processNumber(const Number& n) {
    std::visit([](const auto& val){
        std::cout << "Value: " << val << "\n";
    }, n);
}

// ---- std::string_view — non-owning string reference ----
void printLength(std::string_view sv) {
    std::cout << "\"" << sv << "\" length=" << sv.size() << "\n";
}

// ---- Fold expressions (C++17) — variadic templates ----
template <typename... Args>
auto sum(Args... args) { return (args + ...); }

template <typename... Args>
void printAll(Args... args) { ((std::cout << args << " "), ...); std::cout << "\n"; }

// ============================================================
int main() {
    // optional
    std::cout << "=== std::optional ===" << std::endl;
    auto r1 = divide(10, 2);
    auto r2 = divide(10, 0);
    std::cout << "10/2 = " << (r1.has_value() ? std::to_string(*r1) : "no value") << "\n";
    std::cout << "10/0 = " << (r2.has_value() ? std::to_string(*r2) : "no value") << "\n";
    // value_or: fallback
    std::cout << "With fallback: " << r2.value_or(-1) << "\n";

    // structured bindings
    std::cout << "\n=== Structured Bindings ===" << std::endl;
    auto [name, age] = getNameAge();
    std::cout << name << " is " << age << "\n";

    auto [i, d, s] = getStats();
    std::cout << i << " " << d << " " << s << "\n";

    std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}};
    for (const auto& [student, score] : scores) {
        std::cout << student << ": " << score << "\n";
    }

    // if constexpr
    std::cout << "\n=== if constexpr ===" << std::endl;
    printType(42);
    printType(3.14);
    printType(std::string("hello"));

    // variant
    std::cout << "\n=== std::variant ===" << std::endl;
    Number n1 = 42;
    Number n2 = 3.14;
    Number n3 = std::string("C++17");
    processNumber(n1);
    processNumber(n2);
    processNumber(n3);

    // Check active type
    std::cout << "holds int: " << std::holds_alternative<int>(n1) << "\n";

    // string_view
    std::cout << "\n=== std::string_view ===" << std::endl;
    std::string str = "Hello, World!";
    printLength(str);
    printLength("literal"); // no allocation — direct view

    // fold expressions
    std::cout << "\n=== Fold Expressions ===" << std::endl;
    std::cout << "sum(1,2,3,4,5) = " << sum(1, 2, 3, 4, 5) << "\n";
    printAll("C++17", "fold", "expressions", "are", "cool");

    return 0;
}
