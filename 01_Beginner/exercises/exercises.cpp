// ============================================================
// exercises — Beginner Practice Problems
// Author: Silas Chalwe
//
// Instructions: Try to solve each exercise on your own before
// looking at the hint or solution section at the bottom.
// ============================================================

/*
EXERCISE 1 — FizzBuzz
  Print numbers 1 to 100.
  - If divisible by 3, print "Fizz" instead of the number.
  - If divisible by 5, print "Buzz" instead.
  - If divisible by both 3 and 5, print "FizzBuzz".

EXERCISE 2 — Sum of Digits
  Write a function sumDigits(int n) that returns the sum of all
  digits in a positive integer.
  Example: sumDigits(1234) → 10

EXERCISE 3 — Palindrome Check
  Write a function isPalindrome(std::string s) that returns true
  if the string reads the same forwards and backwards (ignore case).
  Example: "Racecar" → true, "Hello" → false

EXERCISE 4 — Simple Calculator
  Write a program that reads two numbers and an operator (+, -, *, /)
  from the user and prints the result.

EXERCISE 5 — Number Pyramid
  Print the following pattern for n=5:
      1
     1 2
    1 2 3
   1 2 3 4
  1 2 3 4 5
*/

// ============================================================
// SOLUTIONS — try the exercises first!
// ============================================================

#include <iostream>
#include <string>
#include <cctype>   // tolower

// ---- Exercise 1: FizzBuzz ----
void fizzBuzz(int limit) {
    for (int i = 1; i <= limit; i++) {
        if (i % 15 == 0)     std::cout << "FizzBuzz";
        else if (i % 3 == 0) std::cout << "Fizz";
        else if (i % 5 == 0) std::cout << "Buzz";
        else                 std::cout << i;
        std::cout << "\n";
    }
}

// ---- Exercise 2: Sum of Digits ----
int sumDigits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

// ---- Exercise 3: Palindrome Check ----
bool isPalindrome(std::string s) {
    // Convert to lowercase for case-insensitive comparison
    for (char& c : s) c = static_cast<char>(std::tolower(c));
    int left = 0, right = static_cast<int>(s.size()) - 1;
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

// ---- Exercise 4: Simple Calculator ----
void calculator() {
    double a, b;
    char op;
    std::cout << "Enter: num1 operator num2 (e.g. 3 + 5): ";
    std::cin >> a >> op >> b;
    switch (op) {
        case '+': std::cout << "= " << (a + b) << std::endl; break;
        case '-': std::cout << "= " << (a - b) << std::endl; break;
        case '*': std::cout << "= " << (a * b) << std::endl; break;
        case '/':
            if (b != 0) std::cout << "= " << (a / b) << std::endl;
            else        std::cout << "Error: division by zero" << std::endl;
            break;
        default: std::cout << "Unknown operator" << std::endl;
    }
}

// ---- Exercise 5: Number Pyramid ----
void pyramid(int n) {
    for (int i = 1; i <= n; i++) {
        // Print leading spaces
        for (int s = n - i; s > 0; s--) std::cout << " ";
        // Print numbers
        for (int j = 1; j <= i; j++) std::cout << j << " ";
        std::cout << std::endl;
    }
}

// ============================================================
int main() {
    std::cout << "=== FizzBuzz (1-20) ===" << std::endl;
    fizzBuzz(20);

    std::cout << "\n=== Sum of Digits ===" << std::endl;
    std::cout << "sumDigits(1234) = " << sumDigits(1234) << std::endl;
    std::cout << "sumDigits(9999) = " << sumDigits(9999) << std::endl;

    std::cout << "\n=== Palindrome Check ===" << std::endl;
    std::cout << "\"Racecar\" is palindrome: " << isPalindrome("Racecar") << std::endl;
    std::cout << "\"Hello\"   is palindrome: " << isPalindrome("Hello")   << std::endl;

    std::cout << "\n=== Calculator ===" << std::endl;
    calculator();

    std::cout << "\n=== Number Pyramid (n=5) ===" << std::endl;
    pyramid(5);

    return 0;
}
