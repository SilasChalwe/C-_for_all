// ============================================================
// 05_conditionals.cpp
// Topic: if / else if / else and switch statements
// Author: Silas Chalwe
// ============================================================

#include <iostream>
#include <string>

int main() {
    // ---- if / else if / else ----
    int score;
    std::cout << "Enter your exam score (0-100): ";
    std::cin >> score;

    std::string grade;
    if (score >= 90) {
        grade = "A";
    } else if (score >= 80) {
        grade = "B";
    } else if (score >= 70) {
        grade = "C";
    } else if (score >= 60) {
        grade = "D";
    } else {
        grade = "F";
    }

    std::cout << "Your grade: " << grade << std::endl;

    // ---- Nested if ----
    if (score >= 60) {
        std::cout << "Result: PASS" << std::endl;
        if (score == 100) {
            std::cout << "Perfect score! Well done!" << std::endl;
        }
    } else {
        std::cout << "Result: FAIL — keep practising!" << std::endl;
    }

    // ---- switch statement ----
    // switch works with integer or character expressions
    int dayNum;
    std::cout << "\nEnter a day number (1-7): ";
    std::cin >> dayNum;

    switch (dayNum) {
        case 1:
            std::cout << "Monday" << std::endl;
            break;   // break exits the switch; without it execution "falls through"
        case 2:
            std::cout << "Tuesday" << std::endl;
            break;
        case 3:
            std::cout << "Wednesday" << std::endl;
            break;
        case 4:
            std::cout << "Thursday" << std::endl;
            break;
        case 5:
            std::cout << "Friday" << std::endl;
            break;
        case 6:
            // Intentional fall-through to group Saturday and Sunday
        case 7:
            std::cout << "Weekend!" << std::endl;
            break;
        default:
            std::cout << "Invalid day number." << std::endl;
    }

    // ---- Ternary operator as a concise if/else ----
    bool isEven = (score % 2 == 0);
    std::cout << "\nScore " << score << " is " << (isEven ? "even" : "odd") << std::endl;

    return 0;
}
