// ============================================================
// 08_smart_pointers.cpp
// Topic: unique_ptr, shared_ptr, weak_ptr
// Author: Silas Chalwe
// ============================================================
//
// Smart pointers manage dynamic memory automatically.
// They follow RAII: resource acquisition is initialisation.
// Prefer smart pointers over raw new/delete in modern C++.
// ============================================================

#include <iostream>
#include <memory>  // unique_ptr, shared_ptr, weak_ptr
#include <string>

class Resource {
    std::string name;
public:
    explicit Resource(const std::string& n) : name(n) {
        std::cout << "[Resource created: " << name << "]" << std::endl;
    }
    ~Resource() {
        std::cout << "[Resource destroyed: " << name << "]" << std::endl;
    }
    void use() const { std::cout << "Using resource: " << name << std::endl; }
    const std::string& getName() const { return name; }
};

// ============================================================
int main() {
    // ---- unique_ptr ----
    // Sole ownership. Cannot be copied, only moved.
    std::cout << "=== unique_ptr ===" << std::endl;
    {
        auto p1 = std::make_unique<Resource>("Unique-A");
        p1->use();

        // Transfer ownership with std::move
        auto p2 = std::move(p1);
        if (!p1) std::cout << "p1 is now null after move" << std::endl;
        p2->use();
    } // p2 goes out of scope → Resource destroyed automatically

    std::cout << std::endl;

    // ---- shared_ptr ----
    // Shared ownership via reference counting.
    // Resource is destroyed when the last shared_ptr to it is gone.
    std::cout << "=== shared_ptr ===" << std::endl;
    std::shared_ptr<Resource> sp1, sp2;
    {
        auto sp3 = std::make_shared<Resource>("Shared-B");
        sp1 = sp3;  // reference count = 2
        sp2 = sp3;  // reference count = 3
        std::cout << "use_count = " << sp3.use_count() << std::endl;
    } // sp3 destroyed — count drops to 2
    std::cout << "After sp3 gone, use_count = " << sp1.use_count() << std::endl;
    sp1->use();
    sp1.reset();  // count = 1
    sp2.reset();  // count = 0 → Resource destroyed

    std::cout << std::endl;

    // ---- weak_ptr ----
    // Observer — does NOT extend the lifetime of the managed resource.
    // Used to break cyclic shared_ptr references.
    std::cout << "=== weak_ptr ===" << std::endl;
    std::weak_ptr<Resource> wp;
    {
        auto sp = std::make_shared<Resource>("Shared-C");
        wp = sp;
        std::cout << "Expired? " << wp.expired() << std::endl;

        // Lock to get a temporary shared_ptr (safe access)
        if (auto locked = wp.lock()) {
            locked->use();
            std::cout << "use_count while locked = " << locked.use_count() << std::endl;
        }
    } // sp destroyed
    std::cout << "Expired after sp gone? " << wp.expired() << std::endl;

    // ---- unique_ptr with custom deleter ----
    std::cout << "\n=== unique_ptr with custom deleter ===" << std::endl;
    auto customDeleter = [](Resource* r) {
        std::cout << "[Custom deleter for: " << r->getName() << "]" << std::endl;
        delete r;
    };
    std::unique_ptr<Resource, decltype(customDeleter)>
        up(new Resource("Custom-D"), customDeleter);
    up->use();

    return 0;
}
