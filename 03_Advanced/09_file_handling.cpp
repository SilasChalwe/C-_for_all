// ============================================================
// 09_file_handling.cpp
// Topic: Reading and writing files with fstream
// Author: Silas Chalwe
// ============================================================

#include <iostream>
#include <fstream>    // ifstream, ofstream, fstream
#include <sstream>
#include <string>
#include <vector>

int main() {
    const std::string filename = "data.txt";

    // ---- Write to a file (ofstream) ----
    std::cout << "=== Writing to file ===" << std::endl;
    {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error: could not open file for writing." << std::endl;
            return 1;
        }

        outFile << "Name,Age,Score\n";
        outFile << "Alice,20,95.5\n";
        outFile << "Bob,22,82.0\n";
        outFile << "Charlie,21,88.5\n";

        // outFile is automatically closed when it goes out of scope
    }
    std::cout << "Written to " << filename << std::endl;

    // ---- Read from a file line by line (ifstream) ----
    std::cout << "\n=== Reading file line by line ===" << std::endl;
    {
        std::ifstream inFile(filename);
        if (!inFile.is_open()) {
            std::cerr << "Error: could not open file for reading." << std::endl;
            return 1;
        }

        std::string line;
        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;
        }
    }

    // ---- Parse CSV ----
    std::cout << "\n=== Parsing CSV ===" << std::endl;
    {
        std::ifstream inFile(filename);
        std::string line;
        std::getline(inFile, line); // skip header

        while (std::getline(inFile, line)) {
            std::istringstream ss(line);
            std::string name, ageStr, scoreStr;
            std::getline(ss, name,    ',');
            std::getline(ss, ageStr,  ',');
            std::getline(ss, scoreStr,',');
            std::cout << "Name=" << name
                      << " Age="  << std::stoi(ageStr)
                      << " Score=" << std::stod(scoreStr) << std::endl;
        }
    }

    // ---- Append to a file ----
    std::cout << "\n=== Appending to file ===" << std::endl;
    {
        std::ofstream outFile(filename, std::ios::app);
        outFile << "Diana,23,91.0\n";
    }
    std::cout << "Appended 'Diana' to " << filename << std::endl;

    // ---- Read the whole file at once ----
    std::cout << "\n=== Full file after append ===" << std::endl;
    {
        std::ifstream inFile(filename);
        std::cout << inFile.rdbuf();  // stream file buffer directly to cout
    }

    // ---- Binary file ----
    std::cout << "=== Binary write & read ===" << std::endl;
    {
        struct Point { int x; int y; };
        std::vector<Point> points = {{1,2},{3,4},{5,6}};

        std::ofstream bin("points.bin", std::ios::binary);
        for (const auto& p : points)
            bin.write(reinterpret_cast<const char*>(&p), sizeof(Point));
    }
    {
        std::ifstream bin("points.bin", std::ios::binary);
        struct Point { int x; int y; };
        Point p;
        while (bin.read(reinterpret_cast<char*>(&p), sizeof(Point))) {
            std::cout << "(" << p.x << "," << p.y << ") ";
        }
        std::cout << std::endl;
    }

    return 0;
}
