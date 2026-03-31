# 06 – Extras ⚪

> **Goal:** Level up your C++ craftsmanship with best practices, coding standards, and modern language features.

---

## Topics Covered

| File | Topic |
|------|-------|
| [01_best_practices.md](./01_best_practices.md) | Naming conventions, code style, RAII |
| [02_memory_management.cpp](./02_memory_management.cpp) | Stack vs heap, RAII, avoiding leaks |
| [03_modern_cpp11.cpp](./03_modern_cpp11.cpp) | `auto`, range-for, lambdas, `nullptr`, move semantics |
| [04_modern_cpp14_17.cpp](./04_modern_cpp14_17.cpp) | Structured bindings, `if constexpr`, `std::optional`, `std::variant` |
| [05_modern_cpp20.cpp](./05_modern_cpp20.cpp) | Concepts, ranges, `std::format` |
| [06_debugging_tips.md](./06_debugging_tips.md) | GDB, Valgrind, AddressSanitizer, common bugs |

---

## Learning Objectives

After finishing this section you will be able to:

- Write clean, idiomatic C++ following community standards.
- Avoid common memory management pitfalls.
- Use modern C++ (C++11 through C++20) features confidently.
- Debug programs effectively with standard tools.

---

## How to Compile Modern C++ Examples

```bash
# C++17 features
g++ -std=c++17 -Wall -o output 04_modern_cpp14_17.cpp && ./output

# C++20 features (requires GCC 10+ or Clang 10+)
g++ -std=c++20 -Wall -o output 05_modern_cpp20.cpp && ./output
```

---

*Previous section → [05 Projects](../05_Projects/)*
