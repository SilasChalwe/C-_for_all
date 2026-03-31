// ============================================================
// 03_strings.cpp
// Topic: C-strings vs std::string, common string methods
// Author: Silas Chalwe
// ============================================================

#include <iostream>
#include <string>
#include <algorithm> // reverse, transform
#include <cctype>    // toupper, tolower
#include <cstring>   // strlen
#include <sstream>   // stringstream

int main() {
    // ---- C-style string (null-terminated char array) ----
    char cstr[] = "Hello";
    std::cout << "C-string: " << cstr << "  length=" << strlen(cstr) << std::endl;

    // ---- std::string — prefer this in modern C++ ----
    std::string s1 = "Hello";
    std::string s2 = " World";

    // Concatenation
    std::string s3 = s1 + s2;
    std::cout << "Concatenated: " << s3 << std::endl;

    // Length / size
    std::cout << "Length: " << s3.size() << std::endl;

    // Access individual characters
    std::cout << "First char: " << s3[0] << std::endl;
    std::cout << "Last char : " << s3.back() << std::endl;

    // Substring
    std::string sub = s3.substr(6, 5); // start=6, length=5
    std::cout << "Substr(6,5): " << sub << std::endl;

    // Find
    std::size_t pos = s3.find("World");
    if (pos != std::string::npos) {
        std::cout << "Found 'World' at index " << pos << std::endl;
    }

    // Replace
    std::string s4 = s3;
    s4.replace(6, 5, "C++");
    std::cout << "After replace: " << s4 << std::endl;

    // Erase
    s4.erase(5, 4); // erase 4 characters starting at index 5
    std::cout << "After erase:   " << s4 << std::endl;

    // Insert
    s4.insert(5, " Beautiful");
    std::cout << "After insert:  " << s4 << std::endl;

    // Compare
    std::string a = "apple", b = "banana";
    std::cout << "\n\"apple\" < \"banana\": " << (a < b ? "true" : "false") << std::endl;

    // Convert to uppercase
    std::string upper = s1;
    std::transform(upper.begin(), upper.end(), upper.begin(),
                   [](unsigned char c){ return static_cast<char>(std::toupper(c)); });
    std::cout << "Uppercase: " << upper << std::endl;

    // Reverse
    std::string rev = "racecar";
    std::reverse(rev.begin(), rev.end());
    std::cout << "Reversed 'racecar': " << rev << std::endl;

    // Convert number to string
    int num = 42;
    std::string numStr = std::to_string(num);
    std::cout << "to_string(42): \"" << numStr << "\"" << std::endl;

    // Convert string to number
    std::string numStr2 = "3.14";
    double d = std::stod(numStr2);
    std::cout << "stod(\"3.14\"): " << d << std::endl;

    // Splitting a string by delimiter using stringstream
    std::string csv = "Alice,Bob,Charlie";
    std::stringstream ss(csv);
    std::string token;
    std::cout << "\nCSV tokens: ";
    while (std::getline(ss, token, ',')) {
        std::cout << "[" << token << "] ";
    }
    std::cout << std::endl;

    return 0;
}
