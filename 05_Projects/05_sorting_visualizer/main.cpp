// ============================================================
// Project: Console Sorting Visualizer
// Author: Silas Chalwe
// Compile: g++ -std=c++17 -Wall -o visualizer main.cpp && ./visualizer
//
// Tip: Run in a terminal wide enough to display the bar chart.
// Each step shows the current state of the array as a bar chart.
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
#include <random>

// Render the array as a vertical bar chart
void visualize(const std::vector<int>& arr, int highlight1 = -1, int highlight2 = -1) {
    int maxVal = *std::max_element(arr.begin(), arr.end());
    int height = 15; // chart height in rows

    for (int row = height; row >= 1; row--) {
        for (int i = 0; i < static_cast<int>(arr.size()); i++) {
            int barHeight = (arr[i] * height) / maxVal;
            if (barHeight >= row) {
                if (i == highlight1 || i == highlight2)
                    std::cout << "* "; // highlighted bar
                else
                    std::cout << "# ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << "\n";
    }
    // Print values
    for (int v : arr) std::cout << v % 10 << " ";
    std::cout << "\n\n";
}

void pause(int ms = 100) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void clearScreen() {
    std::cout << "\033[2J\033[H"; // ANSI clear screen
}

// ---- Bubble Sort with visualisation ----
void bubbleSortVis(std::vector<int> arr) {
    std::cout << "=== Bubble Sort ===\n";
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            clearScreen();
            std::cout << "Bubble Sort — pass " << (i+1) << ", comparing indices " << j << " and " << (j+1) << "\n";
            visualize(arr, j, j + 1);
            pause(80);
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    clearScreen();
    std::cout << "Bubble Sort — SORTED!\n";
    visualize(arr);
}

// ---- Selection Sort with visualisation ----
void selectionSortVis(std::vector<int> arr) {
    std::cout << "=== Selection Sort ===\n";
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            clearScreen();
            std::cout << "Selection Sort — finding minimum from index " << i << "\n";
            visualize(arr, i, j);
            pause(80);
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) std::swap(arr[i], arr[minIdx]);
    }
    clearScreen();
    std::cout << "Selection Sort — SORTED!\n";
    visualize(arr);
}

// ---- Insertion Sort with visualisation ----
void insertionSortVis(std::vector<int> arr) {
    std::cout << "=== Insertion Sort ===\n";
    int n = static_cast<int>(arr.size());
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            clearScreen();
            std::cout << "Insertion Sort — inserting " << key << " at position " << (j+1) << "\n";
            visualize(arr, j, j + 1);
            pause(80);
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    clearScreen();
    std::cout << "Insertion Sort — SORTED!\n";
    visualize(arr);
}

int main() {
    std::cout << "===============================\n";
    std::cout << " C++ Sorting Visualizer\n";
    std::cout << " Created by Silas Chalwe\n";
    std::cout << "===============================\n";
    std::cout << "Choose algorithm:\n"
              << "1. Bubble Sort\n"
              << "2. Selection Sort\n"
              << "3. Insertion Sort\n"
              << "Choice: ";

    int choice; std::cin >> choice;

    // Generate random data
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(1, 20);
    std::vector<int> data;
    for (int i = 0; i < 16; i++) data.push_back(dist(rng));

    std::cout << "Initial array: ";
    for (int v : data) std::cout << v << " ";
    std::cout << "\n\nPress Enter to start...";
    std::cin.ignore(); std::cin.get();

    switch (choice) {
        case 1: bubbleSortVis(data);    break;
        case 2: selectionSortVis(data); break;
        case 3: insertionSortVis(data); break;
        default: std::cout << "Invalid choice.\n";
    }

    return 0;
}
