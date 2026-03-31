// ============================================================
// 07_structs.cpp
// Topic: Defining and using struct
// Author: Silas Chalwe
// ============================================================
//
// A struct groups related data under one name.
// In C++, struct members are public by default (unlike class).
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// ---- Basic struct definition ----
struct Point {
    double x;
    double y;
};

// ---- Struct with a member function ----
struct Rectangle {
    double width;
    double height;

    // Member function
    double area()      const { return width * height; }
    double perimeter() const { return 2 * (width + height); }
};

// ---- Nested struct ----
struct Student {
    std::string name;
    int         age;
    double      gpa;

    // Constructor-style initialisation using a constructor
    Student(std::string n, int a, double g) : name(n), age(a), gpa(g) {}
};

// ---- Passing struct to a function ----
void printPoint(const Point& p) {
    std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
}

// ============================================================
int main() {
    // Initialise with aggregate initialisation
    Point p1 = {3.0, 4.0};
    Point p2 = {0.0, 0.0};
    printPoint(p1);
    printPoint(p2);

    // Modify members
    p2.x = 1.0;
    p2.y = 2.0;
    printPoint(p2);

    // Rectangle with member functions
    Rectangle rect = {5.0, 3.0};
    std::cout << "\nRectangle " << rect.width << "x" << rect.height << std::endl;
    std::cout << "Area      : " << rect.area()      << std::endl;
    std::cout << "Perimeter : " << rect.perimeter() << std::endl;

    // Vector of students
    std::vector<Student> students = {
        {"Alice",  20, 3.8},
        {"Bob",    22, 3.2},
        {"Charlie",21, 3.9},
    };

    std::cout << "\n--- Student List ---" << std::endl;
    for (const auto& s : students) {
        std::cout << s.name << " (age " << s.age << ") — GPA " << s.gpa << std::endl;
    }

    // Sort by GPA descending
    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b){ return a.gpa > b.gpa; });

    std::cout << "\n--- Sorted by GPA (desc) ---" << std::endl;
    for (const auto& s : students) {
        std::cout << s.name << ": " << s.gpa << std::endl;
    }

    return 0;
}
