// ============================================================
// Project: Student Database (CRUD + File Persistence)
// Author: Silas Chalwe
// Compile: g++ -std=c++17 -Wall -o student_db main.cpp && ./student_db
// ============================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Student {
    int         id;
    std::string name;
    int         age;
    double      gpa;
};

const std::string DB_FILE = "students.csv";

void saveToFile(const std::vector<Student>& students) {
    std::ofstream f(DB_FILE);
    f << "id,name,age,gpa\n";
    for (const auto& s : students)
        f << s.id << "," << s.name << "," << s.age << "," << s.gpa << "\n";
}

std::vector<Student> loadFromFile() {
    std::vector<Student> students;
    std::ifstream f(DB_FILE);
    if (!f.is_open()) return students;
    std::string line;
    std::getline(f, line); // skip header
    while (std::getline(f, line)) {
        std::istringstream ss(line);
        std::string idStr, name, ageStr, gpaStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, name,  ',');
        std::getline(ss, ageStr,',');
        std::getline(ss, gpaStr,',');
        students.push_back({std::stoi(idStr), name, std::stoi(ageStr), std::stod(gpaStr)});
    }
    return students;
}

void displayAll(const std::vector<Student>& students) {
    if (students.empty()) { std::cout << "No students.\n"; return; }
    std::cout << std::left
              << std::setw(5)  << "ID"
              << std::setw(18) << "Name"
              << std::setw(6)  << "Age"
              << std::setw(6)  << "GPA\n";
    std::cout << std::string(35, '-') << "\n";
    for (const auto& s : students) {
        std::cout << std::setw(5)  << s.id
                  << std::setw(18) << s.name
                  << std::setw(6)  << s.age
                  << std::fixed << std::setprecision(2) << s.gpa << "\n";
    }
}

int nextId(const std::vector<Student>& students) {
    if (students.empty()) return 1;
    return std::max_element(students.begin(), students.end(),
        [](const Student& a, const Student& b){ return a.id < b.id; })->id + 1;
}

int main() {
    auto students = loadFromFile();

    // Pre-seed if empty
    if (students.empty()) {
        students.push_back({1, "Alice", 20, 3.8});
        students.push_back({2, "Bob",   22, 3.2});
        students.push_back({3, "Charlie",21,3.9});
        saveToFile(students);
    }

    int choice;
    do {
        std::cout << "\n=== Student Database ===\n"
                  << "1. List all\n"
                  << "2. Add student\n"
                  << "3. Search by name\n"
                  << "4. Update GPA\n"
                  << "5. Delete student\n"
                  << "6. Sort by GPA\n"
                  << "0. Exit\n"
                  << "Choice: ";
        std::cin >> choice;

        if (choice == 1) {
            displayAll(students);
        } else if (choice == 2) {
            Student s;
            s.id = nextId(students);
            std::cout << "Name: "; std::cin >> s.name;
            std::cout << "Age:  "; std::cin >> s.age;
            std::cout << "GPA:  "; std::cin >> s.gpa;
            students.push_back(s);
            saveToFile(students);
            std::cout << "Student added (ID=" << s.id << ")\n";
        } else if (choice == 3) {
            std::string name;
            std::cout << "Name to search: "; std::cin >> name;
            bool found = false;
            for (const auto& s : students) {
                if (s.name.find(name) != std::string::npos) {
                    std::cout << "Found: " << s.name << " (ID=" << s.id << " GPA=" << s.gpa << ")\n";
                    found = true;
                }
            }
            if (!found) std::cout << "Not found.\n";
        } else if (choice == 4) {
            int id; double gpa;
            std::cout << "Student ID: "; std::cin >> id;
            std::cout << "New GPA:    "; std::cin >> gpa;
            for (auto& s : students) {
                if (s.id == id) { s.gpa = gpa; saveToFile(students); std::cout << "Updated.\n"; break; }
            }
        } else if (choice == 5) {
            int id;
            std::cout << "Student ID to delete: "; std::cin >> id;
            auto it = std::find_if(students.begin(), students.end(),
                                   [id](const Student& s){ return s.id == id; });
            if (it != students.end()) {
                students.erase(it);
                saveToFile(students);
                std::cout << "Deleted.\n";
            } else { std::cout << "Not found.\n"; }
        } else if (choice == 6) {
            std::sort(students.begin(), students.end(),
                      [](const Student& a, const Student& b){ return a.gpa > b.gpa; });
            displayAll(students);
        }
    } while (choice != 0);

    std::cout << "Goodbye!\n";
    return 0;
}
