// ============================================================
// 02_memory_management.cpp
// Topic: Stack vs heap, RAII, avoiding leaks
// Author: Silas Chalwe
// ============================================================

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ---- RAII wrapper example ----
class FileRAII {
    FILE* file;
public:
    explicit FileRAII(const char* name, const char* mode)
        : file(std::fopen(name, mode)) {
        if (!file) throw std::runtime_error("Cannot open file");
        std::cout << "[FileRAII] opened\n";
    }
    ~FileRAII() {
        if (file) { std::fclose(file); std::cout << "[FileRAII] closed\n"; }
    }
    // Prevent copying (resource ownership is unique)
    FileRAII(const FileRAII&)            = delete;
    FileRAII& operator=(const FileRAII&) = delete;
    FILE* get() const { return file; }
};

// ---- Custom RAII buffer ----
template <typename T>
class Buffer {
    T*     data;
    size_t sz;
public:
    explicit Buffer(size_t n) : data(new T[n]()), sz(n) {
        std::cout << "[Buffer] allocated " << n << " elements\n";
    }
    ~Buffer() { delete[] data; std::cout << "[Buffer] freed\n"; }
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    T& operator[](size_t i) { return data[i]; }
    size_t size() const { return sz; }
};

int main() {
    std::cout << "=== Stack vs Heap ===" << std::endl;

    // Stack: auto-managed, fast, limited size
    {
        int stackArr[5] = {1, 2, 3, 4, 5};
        std::cout << "Stack array[0]=" << stackArr[0] << std::endl;
    } // stackArr destroyed here automatically

    // Heap: manual management → prefer smart pointers
    {
        auto heapArr = std::make_unique<int[]>(5);
        for (int i = 0; i < 5; i++) heapArr[i] = i + 1;
        std::cout << "Heap array[0]=" << heapArr[0] << std::endl;
    } // unique_ptr destructor frees memory

    std::cout << "\n=== RAII Buffer ===" << std::endl;
    {
        Buffer<double> buf(4);
        for (size_t i = 0; i < buf.size(); i++) buf[i] = i * 1.5;
        std::cout << "buf[2]=" << buf[2] << std::endl;
    }

    std::cout << "\n=== Smart Pointers (recap) ===" << std::endl;
    // unique_ptr — sole ownership, zero overhead
    auto up = std::make_unique<std::string>("unique");
    std::cout << *up << std::endl;

    // shared_ptr — shared ownership, ref-counted
    auto sp1 = std::make_shared<std::vector<int>>(std::initializer_list<int>{1,2,3});
    auto sp2 = sp1;
    sp1->push_back(4);
    std::cout << "shared_ptr size=" << sp2->size() << " (both see changes)\n";

    std::cout << "\n=== RAII File ===" << std::endl;
    try {
        FileRAII f("raii_test.txt", "w");
        std::fputs("RAII is great!\n", f.get());
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "No leaks — RAII cleaned up everything!\n";
    return 0;
}
