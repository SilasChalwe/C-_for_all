// ============================================================
// exercises — Advanced Practice Problems
// Author: Silas Chalwe
// ============================================================

/*
EXERCISE 1 — Generic Min Function
  Write a template function myMin<T> that returns the smaller of two values.
  Test it with int, double, char, and std::string.

EXERCISE 2 — Generic Pair Class
  Implement a template class Pair<T1, T2> with:
  - Members: first, second
  - Constructor, getters
  - swap() method that swaps first and second (only when T1 == T2)

EXERCISE 3 — Exception-safe Division
  Write a divide(double a, double b) function that throws a
  std::domain_error when b==0. Write a test loop that safely
  handles the exception and continues.

EXERCISE 4 — Word Frequency with map
  Given a string sentence, use std::map to count word frequencies
  and print them sorted alphabetically.

EXERCISE 5 — Observer Pattern
  Implement a simple NumberSource class that emits integer values.
  Create two observer lambdas: one that prints even numbers,
  another that accumulates a running sum and prints it.
*/

// ============================================================
// SOLUTIONS
// ============================================================

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <functional>
#include <stdexcept>

// ---- Exercise 1: Generic Min ----
template <typename T>
T myMin(const T& a, const T& b) { return (a < b) ? a : b; }

// ---- Exercise 2: Generic Pair ----
template <typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;
    Pair(T1 f, T2 s) : first(f), second(s) {}
    T1 getFirst()  const { return first; }
    T2 getSecond() const { return second; }
};
// Specialisation that adds swap when types are the same
template <typename T>
class Pair<T, T> {
public:
    T first, second;
    Pair(T f, T s) : first(f), second(s) {}
    void swap() { T tmp = first; first = second; second = tmp; }
    void display() const { std::cout << "(" << first << ", " << second << ")" << std::endl; }
};

// ---- Exercise 3: Exception-safe Division ----
double divide(double a, double b) {
    if (b == 0.0) throw std::domain_error("Division by zero");
    return a / b;
}

// ---- Exercise 4: Word Frequency ----
std::map<std::string, int> wordFrequency(const std::string& sentence) {
    std::map<std::string, int> freq;
    std::istringstream iss(sentence);
    std::string word;
    while (iss >> word) freq[word]++;
    return freq;
}

// ---- Exercise 5: Observer NumberSource ----
class NumberSource {
    std::vector<std::function<void(int)>> observers;
public:
    void subscribe(std::function<void(int)> fn) { observers.push_back(fn); }
    void emit(int value) { for (auto& fn : observers) fn(value); }
};

// ============================================================
int main() {
    // Exercise 1
    std::cout << "=== Exercise 1: Generic Min ===" << std::endl;
    std::cout << "myMin(3, 7)          = " << myMin(3, 7)                     << std::endl;
    std::cout << "myMin(3.14, 2.71)    = " << myMin(3.14, 2.71)               << std::endl;
    std::cout << "myMin('z', 'a')      = " << myMin('z', 'a')                 << std::endl;
    std::cout << "myMin(\"cat\",\"ant\")   = " << myMin(std::string("cat"), std::string("ant")) << std::endl;

    // Exercise 2
    std::cout << "\n=== Exercise 2: Generic Pair ===" << std::endl;
    Pair<int, int> p(10, 20);
    p.display();
    p.swap();
    p.display();

    // Exercise 3
    std::cout << "\n=== Exercise 3: Exception-safe Division ===" << std::endl;
    double divisors[] = {2.0, 0.0, 5.0};
    for (double d : divisors) {
        try {
            std::cout << "10 / " << d << " = " << divide(10.0, d) << std::endl;
        } catch (const std::domain_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    // Exercise 4
    std::cout << "\n=== Exercise 4: Word Frequency ===" << std::endl;
    auto freq = wordFrequency("the quick brown fox jumps over the lazy dog the dog");
    for (const auto& [word, count] : freq) {
        std::cout << word << ": " << count << std::endl;
    }

    // Exercise 5
    std::cout << "\n=== Exercise 5: Observer NumberSource ===" << std::endl;
    NumberSource source;
    int runningSum = 0;
    source.subscribe([](int n){
        if (n % 2 == 0) std::cout << "Even: " << n << std::endl;
    });
    source.subscribe([&runningSum](int n){
        runningSum += n;
        std::cout << "Running sum: " << runningSum << std::endl;
    });
    for (int i = 1; i <= 5; i++) source.emit(i);

    return 0;
}
