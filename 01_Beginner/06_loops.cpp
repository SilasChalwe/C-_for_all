// ============================================================
// 06_loops.cpp
// Topic: for, while, do-while, break, continue
// Author: Silas Chalwe
// ============================================================

#include <iostream>

int main() {
    // ---- for loop ----
    // Best used when you know the number of iterations in advance
    std::cout << "=== for loop (1 to 5) ===" << std::endl;
    for (int i = 1; i <= 5; i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // ---- Nested for loop — multiplication table ----
    std::cout << "\n--- 3x3 Multiplication Table ---" << std::endl;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            std::cout << (i * j) << "\t";
        }
        std::cout << std::endl;
    }

    // ---- while loop ----
    // Best used when the number of iterations is not known upfront
    std::cout << "\n=== while loop: countdown ===" << std::endl;
    int count = 5;
    while (count > 0) {
        std::cout << count << " ";
        count--;
    }
    std::cout << "Go!" << std::endl;

    // ---- do-while loop ----
    // Executes the body at least once before checking the condition
    std::cout << "\n=== do-while: guess the number ===" << std::endl;
    int secret = 7;
    int guess;
    do {
        std::cout << "Guess a number (1-10): ";
        std::cin >> guess;
        if (guess != secret) {
            std::cout << "Wrong! Try again." << std::endl;
        }
    } while (guess != secret);
    std::cout << "Correct! The number was " << secret << "." << std::endl;

    // ---- break — exit loop early ----
    std::cout << "\n=== break: stop at 6 ===" << std::endl;
    for (int i = 1; i <= 10; i++) {
        if (i == 6) {
            std::cout << "(breaking at " << i << ")" << std::endl;
            break;           // exits the loop immediately
        }
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // ---- continue — skip current iteration ----
    std::cout << "\n=== continue: skip even numbers ===" << std::endl;
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;        // skip back to the loop condition
        }
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // ---- Range-based for loop (C++11) ----
    std::cout << "\n=== Range-based for loop ===" << std::endl;
    int numbers[] = {10, 20, 30, 40, 50};
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    return 0;
}
