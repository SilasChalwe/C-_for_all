# C++ Best Practices

> *Created and maintained by Silas Chalwe*

A summary of widely accepted C++ best practices and coding standards.

---

## 1. Naming Conventions

| Entity | Convention | Example |
|--------|-----------|---------|
| Variables | camelCase | `int studentAge;` |
| Constants | UPPER_SNAKE or `constexpr` | `constexpr int MAX_SIZE = 100;` |
| Classes / Structs | PascalCase | `class StudentRecord` |
| Functions / Methods | camelCase | `void calculateGPA()` |
| Namespaces | lowercase | `namespace utils` |
| Private members | trailing or leading underscore | `int age_;` or `int m_age;` |
| Template parameters | PascalCase | `template <typename ValueType>` |

---

## 2. Code Style

- **Indentation:** 4 spaces (no tabs).
- **Braces:** opening brace on the same line as the statement.
- **Line length:** keep lines under 100 characters.
- **One statement per line** — never `int a=1,b=2,c=3;`.
- **Include order:** standard library → third-party → project headers.
- **Prefer `//` comments** over `/* */` for single-line notes.
- **Comment the "why"**, not the "what" (the code itself says what).

---

## 3. RAII — Resource Acquisition Is Initialisation

Acquire resources in constructors, release them in destructors.
This guarantees cleanup even when exceptions are thrown.

```cpp
// BAD: manual management
FILE* f = fopen("file.txt", "r");
// ... if exception here, file is never closed!
fclose(f);

// GOOD: RAII with std::fstream
{
    std::ifstream file("file.txt");
    // file automatically closed when it goes out of scope
}
```

---

## 4. Prefer Modern Features

| Old style | Modern style |
|-----------|-------------|
| `int* p = NULL;` | `int* p = nullptr;` |
| `typedef MyVec vector<int>;` | `using MyVec = vector<int>;` |
| Manual loops | Range-based `for` |
| Raw pointers | Smart pointers |
| C-style casts | `static_cast`, `dynamic_cast` |
| `#define MAX 100` | `constexpr int MAX = 100;` |
| `printf / scanf` | `cout / cin` |

---

## 5. The Rule of Five (if you manage resources manually)

If you define any of these, define all five:
1. Destructor
2. Copy constructor
3. Copy assignment operator
4. Move constructor
5. Move assignment operator

Or use **Rule of Zero**: let the compiler generate them by using
smart pointers and STL containers.

---

## 6. const Correctness

- Mark member functions that don't modify state as `const`.
- Pass large objects by `const reference`: `void f(const std::string& s)`.
- Use `constexpr` for compile-time constants.

---

## 7. Exception Safety

- **Basic guarantee:** no resource leaks.
- **Strong guarantee:** operation either succeeds or has no effect.
- **No-throw guarantee:** operation never throws.
- Use `noexcept` to signal that a function won't throw.

---

## 8. Avoid Undefined Behaviour

- Never dereference a null or dangling pointer.
- Never read/write out of array bounds.
- Never return a reference to a local variable.
- Never use a variable before initialising it.
- Always initialise member variables in constructors.

---

## 9. Useful Tools

| Tool | Purpose |
|------|---------|
| `g++ -Wall -Wextra -Wpedantic` | Enable all compiler warnings |
| `clang-tidy` | Static analysis / linter |
| `cppcheck` | Static analysis |
| `valgrind` | Memory leak / error detection |
| `AddressSanitizer` | Compile with `-fsanitize=address` |
| `gdb` | Debugger |

---

## 10. Further Reading

- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [cppreference.com](https://en.cppreference.com)
- *Effective Modern C++* — Scott Meyers
- *The C++ Programming Language* — Bjarne Stroustrup
