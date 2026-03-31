// ============================================================
// 05_references.cpp
// Topic: References vs pointers, swap by reference
// Author: Silas Chalwe
// ============================================================
//
// A reference is an alias — another name for an existing variable.
// References must be initialised when declared and cannot be reseated.
// ============================================================

#include <iostream>
#include <string>

// Swap two integers using references
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Demonstrate returning a reference (be careful with lifetime!)
int& getElement(int arr[], int index) {
    return arr[index]; // returns a reference to an array element
}

int main() {
    // ---- Basic reference ----
    int x = 10;
    int& ref = x;   // ref is another name for x

    std::cout << "x   = " << x   << std::endl;
    std::cout << "ref = " << ref << std::endl;

    ref = 42;  // modifying through the reference changes x
    std::cout << "After ref=42: x = " << x << std::endl;

    // ---- References vs pointers ----
    // Reference: no null, no arithmetic, always valid after init, cleaner syntax
    // Pointer:   can be null, supports arithmetic, can be reseated

    // ---- Swap using references ----
    int a = 5, b = 8;
    std::cout << "\nBefore swap: a=" << a << "  b=" << b << std::endl;
    swap(a, b);
    std::cout << "After swap:  a=" << a << "  b=" << b << std::endl;

    // ---- const reference (read-only alias) ----
    const std::string greeting = "Hello, World!";
    const std::string& greetRef = greeting;
    std::cout << "\nconst ref: " << greetRef << std::endl;
    // greetRef[0] = 'h';  // ERROR: read-only reference

    // ---- Reference as function return ----
    int arr[] = {10, 20, 30, 40, 50};
    getElement(arr, 2) = 99;  // sets arr[2] to 99 via the returned reference
    std::cout << "\narr[2] after getElement(arr,2)=99: " << arr[2] << std::endl;

    // ---- Range-based for with reference (avoids copying) ----
    std::cout << "\nModify array elements via range-for references:" << std::endl;
    for (int& elem : arr) elem *= 2;
    for (int v : arr)     std::cout << v << " ";
    std::cout << std::endl;

    return 0;
}
