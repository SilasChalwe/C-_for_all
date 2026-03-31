# C++ Debugging Tips

> *Created and maintained by Silas Chalwe*

---

## 1. Compiler Warnings — Your First Line of Defence

Always compile with maximum warnings:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Wshadow -o program program.cpp
```

| Flag | What it enables |
|------|----------------|
| `-Wall` | Common warnings |
| `-Wextra` | Extra warnings |
| `-Wpedantic` | Standards conformance |
| `-Wshadow` | Variable shadowing |
| `-Wuninitialized` | Use before initialisation |

---

## 2. GDB — GNU Debugger

```bash
# Compile with debug info
g++ -std=c++17 -g -o program program.cpp

# Start GDB
gdb ./program

# Useful GDB commands
(gdb) run              # run the program
(gdb) break main       # set breakpoint at main
(gdb) break file.cpp:42  # set breakpoint at line 42
(gdb) next             # execute next line
(gdb) step             # step into function
(gdb) continue         # continue until next breakpoint
(gdb) print x          # print value of variable x
(gdb) backtrace        # show call stack
(gdb) quit             # exit GDB
```

---

## 3. Valgrind — Memory Error Detection

```bash
valgrind --leak-check=full ./program
```

Detects:
- Memory leaks
- Use after free
- Double free
- Uninitialised reads

---

## 4. AddressSanitizer (ASan)

Fast memory error detector built into GCC/Clang:

```bash
g++ -std=c++17 -fsanitize=address -g -o program program.cpp
./program
```

Detects heap/stack overflows, use-after-free, and more — in real time.

---

## 5. UndefinedBehaviourSanitizer (UBSan)

```bash
g++ -std=c++17 -fsanitize=undefined -g -o program program.cpp
./program
```

Detects signed integer overflow, null pointer dereference, etc.

---

## 6. Common Bugs and How to Avoid Them

| Bug | Example | Fix |
|-----|---------|-----|
| Dangling pointer | `int* p = ...; delete p; *p = 5;` | Use smart pointers |
| Memory leak | `new` without `delete` | Use RAII / smart pointers |
| Off-by-one | `arr[size]` | Use `arr[size-1]` or range-for |
| Uninitialised variable | `int x; cout << x;` | Always initialise |
| Integer overflow | `int x = INT_MAX + 1;` | Use `long long` or check bounds |
| Null dereference | `ptr->method()` when ptr==nullptr | Check before dereference |
| Use after move | `vec.push_back(std::move(s)); cout << s;` | Don't use moved-from objects |
| Signed/unsigned mismatch | `for (int i=0; i < vec.size();...` | Use `size_t` or cast |

---

## 7. Useful Diagnostic Snippets

```cpp
// Assert (disabled in Release builds)
#include <cassert>
assert(ptr != nullptr);

// Static assert — compile-time check
static_assert(sizeof(int) == 4, "Expected 4-byte int");

// Log to stderr
#include <iostream>
std::cerr << "[DEBUG] value=" << x << std::endl;

// Print call stack (GCC/Clang with -rdynamic)
#include <execinfo.h>
void printStackTrace() {
    void* buf[32];
    int n = backtrace(buf, 32);
    backtrace_symbols_fd(buf, n, 2);
}
```

---

## 8. IDE Support

| IDE | Debugger | Linter |
|-----|----------|--------|
| VS Code | GDB / LLDB | clangd, cppcheck |
| CLion | GDB / LLDB | Built-in |
| Visual Studio | MSVC Debugger | Built-in |
| Eclipse CDT | GDB | Built-in |
