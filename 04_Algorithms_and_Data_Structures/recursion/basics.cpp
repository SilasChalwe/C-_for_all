// ============================================================
// recursion/basics.cpp
// Topic: Factorial, Fibonacci, power — recursion fundamentals
// Author: Silas Chalwe
// ============================================================
//
// Recursion: a function that calls itself with a smaller input
// until it reaches a base case (termination condition).
//
// Every recursive function needs:
//   1. A base case — prevents infinite recursion.
//   2. A recursive case — makes progress toward the base case.
// ============================================================

#include <iostream>
#include <map>

// ---- Factorial: n! = n × (n-1) × ... × 1, 0! = 1 ----
long long factorial(int n) {
    if (n <= 1) return 1;              // base case
    return n * factorial(n - 1);      // recursive case
}

// ---- Fibonacci: naive (exponential time) ----
int fibNaive(int n) {
    if (n <= 1) return n;
    return fibNaive(n - 1) + fibNaive(n - 2);
}

// ---- Fibonacci: memoised (linear time) ----
int fibMemo(int n, std::map<int,int>& memo) {
    if (n <= 1) return n;
    if (memo.count(n)) return memo[n]; // cached result
    memo[n] = fibMemo(n-1, memo) + fibMemo(n-2, memo);
    return memo[n];
}

// ---- Power: x^n ----
double power(double x, int n) {
    if (n == 0) return 1.0;           // base case: x^0 = 1
    if (n < 0)  return 1.0 / power(x, -n);
    if (n % 2 == 0) {
        double half = power(x, n / 2);
        return half * half;           // fast exponentiation: O(log n)
    }
    return x * power(x, n - 1);
}

// ---- Sum of array ----
int arraySum(const int arr[], int n) {
    if (n == 0) return 0;
    return arr[n - 1] + arraySum(arr, n - 1);
}

// ---- String reversal ----
std::string reverseString(const std::string& s) {
    if (s.empty()) return s;
    return reverseString(s.substr(1)) + s[0];
}

// ============================================================
int main() {
    std::cout << "=== Factorial ===" << std::endl;
    for (int i = 0; i <= 10; i++) {
        std::cout << i << "! = " << factorial(i) << std::endl;
    }

    std::cout << "\n=== Fibonacci ===" << std::endl;
    std::map<int,int> memo;
    for (int i = 0; i <= 15; i++) {
        std::cout << "fib(" << i << ") = " << fibMemo(i, memo) << std::endl;
    }

    std::cout << "\n=== Power ===" << std::endl;
    std::cout << "2^10  = " << power(2, 10)  << std::endl;
    std::cout << "3^0   = " << power(3, 0)   << std::endl;
    std::cout << "2^-3  = " << power(2, -3)  << std::endl;
    std::cout << "1.5^4 = " << power(1.5, 4) << std::endl;

    std::cout << "\n=== Array Sum ===" << std::endl;
    int arr[] = {1, 2, 3, 4, 5};
    std::cout << "Sum of {1,2,3,4,5} = " << arraySum(arr, 5) << std::endl;

    std::cout << "\n=== Reverse String ===" << std::endl;
    std::cout << "reverse(\"hello\") = " << reverseString("hello") << std::endl;

    return 0;
}
