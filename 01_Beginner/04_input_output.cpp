// ============================================================
// 04_input_output.cpp
// Topic: cin, cout, cerr, and output formatting
// Author: Silas Chalwe
// ============================================================

#include <iostream>
#include <iomanip>   // for setw, setprecision, fixed, left, right
#include <string>

int main() {
    // ---- Basic output with cout ----
    std::cout << "=== Basic Output ===" << std::endl;
    std::cout << "Hello from cout!" << std::endl;   // endl flushes buffer
    std::cout << "New line with \\n\n";               // \n is faster (no flush)

    // ---- Error output with cerr ----
    std::cerr << "This goes to the error stream (cerr)." << std::endl;

    // ---- Basic input with cin ----
    std::string name;
    int age;

    std::cout << "\nEnter your name: ";
    std::cin >> name;                        // reads one word (stops at whitespace)

    std::cout << "Enter your age: ";
    std::cin >> age;

    std::cout << "Hello, " << name << "! You are " << age << " years old." << std::endl;

    // ---- Reading a full line ----
    std::cin.ignore();                       // discard leftover newline in buffer
    std::string sentence;
    std::cout << "Enter a sentence: ";
    std::getline(std::cin, sentence);        // reads entire line including spaces
    std::cout << "You wrote: " << sentence << std::endl;

    // ---- Formatting output ----
    std::cout << "\n=== Formatting ===" << std::endl;

    double pi = 3.14159265358979;
    std::cout << "Default        : " << pi << std::endl;
    std::cout << "fixed 2 dec    : " << std::fixed << std::setprecision(2) << pi << std::endl;
    std::cout << "fixed 6 dec    : " << std::fixed << std::setprecision(6) << pi << std::endl;
    std::cout << "scientific     : " << std::scientific << pi << std::endl;

    // Reset to default
    std::cout << std::defaultfloat;

    // Column alignment
    std::cout << "\n--- Column alignment ---" << std::endl;
    std::cout << std::left  << std::setw(15) << "Item"
              << std::right << std::setw(8)  << "Price" << std::endl;
    std::cout << std::string(23, '-') << std::endl;
    std::cout << std::left  << std::setw(15) << "Apple"
              << std::right << std::setw(8)  << std::fixed << std::setprecision(2) << 0.99 << std::endl;
    std::cout << std::left  << std::setw(15) << "Laptop"
              << std::right << std::setw(8)  << 999.99 << std::endl;

    return 0;
}
