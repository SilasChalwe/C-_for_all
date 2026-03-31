// ============================================================
// 06_stl_containers.cpp
// Topic: vector, list, map, set, unordered_map
// Author: Silas Chalwe
// ============================================================

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <string>

// Helper: print a container
template <typename C>
void print(const std::string& label, const C& c) {
    std::cout << label << ": ";
    for (const auto& v : c) std::cout << v << " ";
    std::cout << std::endl;
}

int main() {
    // ---- std::vector — dynamic array, O(1) random access ----
    std::cout << "=== std::vector ===" << std::endl;
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
    v.push_back(5);         // add at end  O(1) amortised
    v.insert(v.begin(), 0); // insert at front O(n)
    print("vector", v);
    std::cout << "size=" << v.size() << "  front=" << v.front() << "  back=" << v.back() << std::endl;
    v.erase(v.begin());     // remove first element
    v.pop_back();           // remove last element
    print("after erase+pop", v);

    // ---- std::list — doubly linked list, O(1) insert/erase anywhere ----
    std::cout << "\n=== std::list ===" << std::endl;
    std::list<int> lst = {1, 2, 3, 4, 5};
    lst.push_front(0);
    lst.push_back(6);
    lst.remove(3);          // remove all elements equal to 3
    print("list", lst);

    // ---- std::map — sorted key-value pairs, O(log n) access ----
    std::cout << "\n=== std::map ===" << std::endl;
    std::map<std::string, int> wordCount;
    std::vector<std::string> words = {"apple", "banana", "apple", "cherry", "banana", "apple"};
    for (const auto& w : words) wordCount[w]++;
    for (const auto& [word, count] : wordCount) {   // structured bindings (C++17)
        std::cout << word << " → " << count << std::endl;
    }
    std::cout << "apple count = " << wordCount.at("apple") << std::endl;
    std::cout << "Contains 'mango': " << (wordCount.count("mango") > 0 ? "yes" : "no") << std::endl;

    // ---- std::set — sorted unique values, O(log n) ----
    std::cout << "\n=== std::set ===" << std::endl;
    std::set<int> primes = {2, 3, 5, 7, 11, 13};
    primes.insert(17);
    primes.insert(7);   // duplicate — ignored
    print("primes", primes);
    std::cout << "Contains 5: " << (primes.count(5) ? "yes" : "no") << std::endl;

    // ---- std::unordered_map — hash table, O(1) average access ----
    std::cout << "\n=== std::unordered_map ===" << std::endl;
    std::unordered_map<std::string, std::string> capitals = {
        {"Zambia",  "Lusaka"},
        {"Kenya",   "Nairobi"},
        {"Nigeria", "Abuja"},
    };
    capitals["Ghana"] = "Accra";
    for (const auto& [country, capital] : capitals) {
        std::cout << country << " → " << capital << std::endl;
    }
    // Safe lookup
    auto it = capitals.find("Zimbabwe");
    if (it == capitals.end()) {
        std::cout << "Zimbabwe not found" << std::endl;
    }

    return 0;
}
