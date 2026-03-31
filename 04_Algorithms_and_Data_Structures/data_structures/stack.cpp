// ============================================================
// data_structures/stack.cpp
// Topic: Stack — LIFO (Last In, First Out)
// Author: Silas Chalwe
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

// ---- Stack backed by a dynamic array (vector) ----
template <typename T>
class Stack {
    std::vector<T> data;

public:
    void push(const T& val) { data.push_back(val); }

    void pop() {
        if (empty()) throw std::underflow_error("Stack underflow");
        data.pop_back();
    }

    T& top() {
        if (empty()) throw std::underflow_error("Stack is empty");
        return data.back();
    }

    const T& top() const {
        if (empty()) throw std::underflow_error("Stack is empty");
        return data.back();
    }

    bool   empty() const { return data.empty(); }
    size_t size()  const { return data.size();  }

    void display() const {
        std::cout << "Stack (top→bottom): ";
        for (int i = static_cast<int>(data.size()) - 1; i >= 0; i--)
            std::cout << data[i] << " ";
        std::cout << std::endl;
    }
};

// ---- Application: balanced parentheses checker ----
bool isBalanced(const std::string& s) {
    Stack<char> stk;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            stk.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (stk.empty()) return false;
            char top = stk.top(); stk.pop();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) return false;
        }
    }
    return stk.empty();
}

// ---- Application: reverse a string ----
std::string reverseString(const std::string& s) {
    Stack<char> stk;
    for (char c : s) stk.push(c);
    std::string result;
    while (!stk.empty()) { result += stk.top(); stk.pop(); }
    return result;
}

int main() {
    Stack<int> s;
    s.push(10); s.push(20); s.push(30);
    s.display();
    std::cout << "Top: " << s.top() << "  Size: " << s.size() << std::endl;
    s.pop();
    s.display();

    // Balanced parentheses
    std::cout << "\n=== Balanced Parentheses ===" << std::endl;
    std::vector<std::string> tests = {
        "(())",    "{[()]}",  "([)]",  "(((",  "{}"
    };
    for (const auto& t : tests) {
        std::cout << "\"" << t << "\" → " << (isBalanced(t) ? "balanced" : "NOT balanced") << std::endl;
    }

    // Reverse string
    std::cout << "\n=== Reverse String ===" << std::endl;
    std::string str = "Hello, C++!";
    std::cout << "\"" << str << "\" reversed: \"" << reverseString(str) << "\"" << std::endl;

    return 0;
}
