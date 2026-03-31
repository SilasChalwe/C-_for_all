// ============================================================
// Project: Command-Line Calculator
// Author: Silas Chalwe
// Compile: g++ -std=c++17 -Wall -o calculator main.cpp && ./calculator
// ============================================================

#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <cmath>
#include <iomanip>
#include <vector>

struct HistoryEntry {
    std::string expression;
    double result;
};

double calculate(double a, const std::string& op, double b, bool& valid) {
    valid = true;
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) { std::cout << "Error: Division by zero\n"; valid = false; return 0; }
        return a / b;
    }
    if (op == "%") {
        if (b == 0) { std::cout << "Error: Modulo by zero\n"; valid = false; return 0; }
        return std::fmod(a, b);
    }
    if (op == "^") return std::pow(a, b);
    valid = false;
    return 0;
}

int main() {
    std::cout << "=================================\n";
    std::cout << "      C++ Command-Line Calculator    \n";
    std::cout << "   Created by Silas Chalwe         \n";
    std::cout << "=================================\n";
    std::cout << "Usage: <num> <op> <num>\n";
    std::cout << "Operators: + - * / % ^\n";
    std::cout << "Commands: sqrt <n>, history, clear, quit\n\n";

    std::vector<HistoryEntry> history;

    while (true) {
        std::cout << "calc> ";
        std::string line;
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;

        // Handle special commands
        if (line == "quit" || line == "exit") break;
        if (line == "history") {
            if (history.empty()) { std::cout << "No history yet.\n"; continue; }
            for (int i = static_cast<int>(history.size()) - 1; i >= 0; i--) {
                std::cout << "[" << (i+1) << "] " << history[i].expression
                          << " = " << history[i].result << "\n";
            }
            continue;
        }
        if (line == "clear") { history.clear(); std::cout << "History cleared.\n"; continue; }

        // sqrt
        std::istringstream iss(line);
        std::string token;
        iss >> token;
        if (token == "sqrt") {
            double n;
            if (iss >> n) {
                if (n < 0) { std::cout << "Error: sqrt of negative number\n"; continue; }
                double res = std::sqrt(n);
                std::cout << "= " << std::fixed << std::setprecision(4) << res << "\n";
                history.push_back({"sqrt(" + std::to_string(n) + ")", res});
            }
            continue;
        }

        // Binary operation
        double a, b;
        std::string op;
        std::istringstream expr(line);
        if (!(expr >> a >> op >> b)) {
            std::cout << "Invalid expression. Example: 5 + 3\n";
            continue;
        }

        bool valid;
        double result = calculate(a, op, b, valid);
        if (valid) {
            std::cout << "= " << std::fixed << std::setprecision(4) << result << "\n";
            history.push_back({line, result});
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}
