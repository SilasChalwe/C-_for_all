// ============================================================
// mini_project — Student Grade Manager
// Author: Silas Chalwe
//
// Description: A simple console application that lets you add
// students, record their grades, and view statistics.
//
// Concepts used: Classes, vectors, structs, OOP encapsulation,
//                file I/O (optional), input validation
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <numeric>   // std::accumulate
#include <algorithm> // std::max_element, std::min_element, std::sort
#include <iomanip>   // std::setw, std::fixed, std::setprecision

// ---- Student record ----
struct Student {
    std::string name;
    std::vector<double> grades;

    Student(const std::string& n) : name(n) {}

    void addGrade(double g) {
        if (g < 0 || g > 100) {
            std::cout << "Invalid grade. Must be 0-100." << std::endl;
            return;
        }
        grades.push_back(g);
    }

    double average() const {
        if (grades.empty()) return 0.0;
        return std::accumulate(grades.begin(), grades.end(), 0.0) / grades.size();
    }

    char letterGrade() const {
        double avg = average();
        if (avg >= 90) return 'A';
        if (avg >= 80) return 'B';
        if (avg >= 70) return 'C';
        if (avg >= 60) return 'D';
        return 'F';
    }

    void display() const {
        std::cout << std::left << std::setw(15) << name
                  << " | Avg: " << std::fixed << std::setprecision(1)
                  << std::setw(6) << average()
                  << " | Grade: " << letterGrade()
                  << " | Grades: ";
        for (double g : grades) std::cout << g << " ";
        std::cout << std::endl;
    }
};

// ---- Grade Manager ----
class GradeManager {
private:
    std::vector<Student> students;

public:
    void addStudent(const std::string& name) {
        // Check for duplicates
        for (const auto& s : students) {
            if (s.name == name) {
                std::cout << name << " already exists." << std::endl;
                return;
            }
        }
        students.emplace_back(name);
        std::cout << "Student '" << name << "' added." << std::endl;
    }

    void addGrade(const std::string& name, double grade) {
        for (auto& s : students) {
            if (s.name == name) {
                s.addGrade(grade);
                return;
            }
        }
        std::cout << "Student '" << name << "' not found." << std::endl;
    }

    void displayAll() const {
        if (students.empty()) {
            std::cout << "No students yet." << std::endl;
            return;
        }
        std::cout << "\n=== Student Report ===\n";
        for (const auto& s : students) s.display();
    }

    void displayTopStudents() const {
        if (students.empty()) return;
        // Sort by average descending (copy)
        auto sorted = students;
        std::sort(sorted.begin(), sorted.end(),
                  [](const Student& a, const Student& b){ return a.average() > b.average(); });
        std::cout << "\n=== Top Students ===\n";
        int rank = 1;
        for (const auto& s : sorted) {
            std::cout << rank++ << ". " << s.name
                      << " — " << std::fixed << std::setprecision(1) << s.average() << std::endl;
        }
    }
};

// ---- Main menu ----
int main() {
    GradeManager manager;

    // Pre-populate some sample data
    manager.addStudent("Alice");
    manager.addGrade("Alice", 88);
    manager.addGrade("Alice", 92);
    manager.addGrade("Alice", 85);

    manager.addStudent("Bob");
    manager.addGrade("Bob", 70);
    manager.addGrade("Bob", 75);
    manager.addGrade("Bob", 68);

    manager.addStudent("Charlie");
    manager.addGrade("Charlie", 95);
    manager.addGrade("Charlie", 97);
    manager.addGrade("Charlie", 91);

    manager.displayAll();
    manager.displayTopStudents();

    // Interactive menu
    int choice;
    do {
        std::cout << "\n--- Menu ---\n"
                  << "1. Add student\n"
                  << "2. Add grade\n"
                  << "3. Display all\n"
                  << "4. Top students\n"
                  << "0. Exit\n"
                  << "Choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string name;
            std::cout << "Student name: ";
            std::cin >> name;
            manager.addStudent(name);
        } else if (choice == 2) {
            std::string name;
            double grade;
            std::cout << "Student name: ";
            std::cin >> name;
            std::cout << "Grade (0-100): ";
            std::cin >> grade;
            manager.addGrade(name, grade);
        } else if (choice == 3) {
            manager.displayAll();
        } else if (choice == 4) {
            manager.displayTopStudents();
        }
    } while (choice != 0);

    std::cout << "Goodbye!" << std::endl;
    return 0;
}
