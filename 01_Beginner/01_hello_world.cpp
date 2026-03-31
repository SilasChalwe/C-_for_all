// ============================================================
// 01_hello_world.cpp
// Topic: Your first C++ program
// Author: Silas Chalwe
// ============================================================
//
// Every C++ program starts execution in the main() function.
// #include <iostream> brings in the standard input/output library.
// std::cout prints to the console; std::endl flushes and adds a newline.
// ============================================================

#include <iostream>  // required for std::cout

int main() {
    // Print a greeting to the console
    std::cout << "Hello, World!" << std::endl;

    // We can also use the 'using' directive to avoid typing std:: every time
    using std::cout;
    cout << "Welcome to C++ for All!" << std::endl;

    // Return 0 signals successful execution to the operating system
    return 0;
}
