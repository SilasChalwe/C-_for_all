// ============================================================
// 04_templates.cpp
// Topic: Function templates, class templates, template specialisation
// Author: Silas Chalwe
// ============================================================
//
// Templates let you write generic code that works with any type.
// The compiler generates concrete versions at compile time.
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>   // std::strcmp

// ---- Function template ----
template <typename T>
T maxOf(T a, T b) {
    return (a > b) ? a : b;
}

// ---- Template with multiple type parameters ----
template <typename T, typename U>
void printPair(const T& first, const U& second) {
    std::cout << "(" << first << ", " << second << ")" << std::endl;
}

// ---- Template function: generic print of a container ----
template <typename Container>
void printContainer(const Container& c, const std::string& label = "") {
    if (!label.empty()) std::cout << label << ": ";
    for (const auto& elem : c) std::cout << elem << " ";
    std::cout << std::endl;
}

// ---- Template function: generic swap ----
template <typename T>
void mySwap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

// ---- Class template: generic Stack ----
template <typename T>
class Stack {
private:
    std::vector<T> data;

public:
    void push(const T& item) { data.push_back(item); }

    void pop() {
        if (empty()) throw std::runtime_error("Stack underflow");
        data.pop_back();
    }

    T& top() {
        if (empty()) throw std::runtime_error("Stack is empty");
        return data.back();
    }

    bool   empty() const { return data.empty(); }
    size_t size()  const { return data.size(); }

    void display() const {
        std::cout << "Stack [top → bottom]: ";
        for (int i = static_cast<int>(data.size()) - 1; i >= 0; i--)
            std::cout << data[i] << " ";
        std::cout << std::endl;
    }
};

// ---- Template specialisation ----
// Special behaviour for const char* comparisons
template <>
const char* maxOf<const char*>(const char* a, const char* b) {
    return (std::strcmp(a, b) > 0) ? a : b;
}

// ---- Non-type template parameter ----
template <typename T, int SIZE>
class FixedArray {
    T data[SIZE];
public:
    FixedArray() { std::fill(data, data + SIZE, T{}); }
    T& operator[](int i) { return data[i]; }
    int size() const { return SIZE; }
};

// ============================================================
int main() {
    // Function template
    std::cout << "maxOf(3, 7)       = " << maxOf(3, 7)         << std::endl;
    std::cout << "maxOf(3.14, 2.71) = " << maxOf(3.14, 2.71)   << std::endl;
    std::cout << "maxOf(\"apple\", \"banana\") = "
              << maxOf(std::string("apple"), std::string("banana")) << std::endl;

    // Multiple type parameters
    printPair(42, "hello");
    printPair(3.14, true);

    // Generic container print
    std::vector<int> v = {1, 2, 3, 4, 5};
    printContainer(v, "vector");

    // Generic swap
    int a = 10, b = 20;
    mySwap(a, b);
    std::cout << "After mySwap: a=" << a << " b=" << b << std::endl;

    // Class template — Stack<int>
    std::cout << "\n=== Stack<int> ===" << std::endl;
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.display();
    std::cout << "Top: " << intStack.top() << std::endl;
    intStack.pop();
    intStack.display();

    // Stack<string>
    std::cout << "\n=== Stack<string> ===" << std::endl;
    Stack<std::string> strStack;
    strStack.push("C++");
    strStack.push("Templates");
    strStack.push("Are");
    strStack.push("Powerful");
    strStack.display();

    // Non-type template parameter
    FixedArray<double, 5> fa;
    for (int i = 0; i < fa.size(); i++) fa[i] = i * 1.1;
    std::cout << "\nFixedArray: ";
    for (int i = 0; i < fa.size(); i++) std::cout << fa[i] << " ";
    std::cout << std::endl;

    return 0;
}
