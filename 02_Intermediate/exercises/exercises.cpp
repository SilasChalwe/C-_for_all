// ============================================================
// exercises — Intermediate Practice Problems
// Author: Silas Chalwe
// ============================================================

/*
EXERCISE 1 — Reverse an Array
  Write a function reverseArray(int arr[], int size) that reverses
  the array in-place using pointers. Print the array before and after.

EXERCISE 2 — String Word Count
  Write a function wordCount(const std::string& s) that returns the
  number of words in a sentence.
  Example: "Hello World C++" → 3

EXERCISE 3 — Dynamic Matrix
  Ask the user for rows and cols, allocate a 2-D array on the heap,
  fill it with values 1..rows*cols, print it, then free memory.

EXERCISE 4 — Linked Node
  Create a struct Node with an int value and a Node* next pointer.
  Build a short linked list: 1 → 2 → 3 → nullptr.
  Traverse and print all values, then free the memory.

EXERCISE 5 — Rectangle Class
  Implement a Rectangle class with:
  - Private: width, height
  - Constructor with validation (positive dimensions)
  - Methods: area(), perimeter(), isSquare()
  - Overloaded == operator to compare two rectangles by area
*/

// ============================================================
// SOLUTIONS
// ============================================================

#include <iostream>
#include <string>
#include <sstream>

// ---- Exercise 1: Reverse Array ----
void reverseArray(int arr[], int size) {
    int* left  = arr;
    int* right = arr + size - 1;
    while (left < right) {
        int tmp = *left;
        *left   = *right;
        *right  = tmp;
        left++;
        right--;
    }
}

// ---- Exercise 2: Word Count ----
int wordCount(const std::string& s) {
    std::istringstream iss(s);
    std::string word;
    int count = 0;
    while (iss >> word) count++;
    return count;
}

// ---- Exercise 3: Dynamic Matrix ----
void dynamicMatrix(int rows, int cols) {
    int** m = new int*[rows];
    int val = 1;
    for (int i = 0; i < rows; i++) {
        m[i] = new int[cols];
        for (int j = 0; j < cols; j++) m[i][j] = val++;
    }
    std::cout << "Dynamic " << rows << "x" << cols << " matrix:" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) std::cout << m[i][j] << "\t";
        std::cout << std::endl;
    }
    for (int i = 0; i < rows; i++) delete[] m[i];
    delete[] m;
}

// ---- Exercise 4: Linked List ----
struct Node {
    int   value;
    Node* next;
    Node(int v, Node* n = nullptr) : value(v), next(n) {}
};

void printList(Node* head) {
    while (head) {
        std::cout << head->value;
        if (head->next) std::cout << " → ";
        head = head->next;
    }
    std::cout << " → nullptr" << std::endl;
}

void freeList(Node* head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

// ---- Exercise 5: Rectangle Class ----
class Rectangle {
private:
    double width, height;
public:
    Rectangle(double w, double h) {
        if (w <= 0 || h <= 0) throw std::invalid_argument("Dimensions must be positive");
        width = w; height = h;
    }
    double area()      const { return width * height; }
    double perimeter() const { return 2 * (width + height); }
    bool   isSquare()  const { return width == height; }
    bool operator==(const Rectangle& other) const { return area() == other.area(); }
    void display() const {
        std::cout << "Rectangle(" << width << "x" << height
                  << ") area=" << area()
                  << " perimeter=" << perimeter()
                  << " isSquare=" << (isSquare() ? "yes" : "no") << std::endl;
    }
};

// ============================================================
int main() {
    // Exercise 1
    std::cout << "=== Exercise 1: Reverse Array ===" << std::endl;
    int arr[] = {1, 2, 3, 4, 5};
    reverseArray(arr, 5);
    for (int v : arr) std::cout << v << " ";
    std::cout << std::endl;

    // Exercise 2
    std::cout << "\n=== Exercise 2: Word Count ===" << std::endl;
    std::cout << "wordCount(\"Hello World C++\") = "
              << wordCount("Hello World C++") << std::endl;

    // Exercise 3
    std::cout << "\n=== Exercise 3: Dynamic Matrix ===" << std::endl;
    dynamicMatrix(3, 4);

    // Exercise 4
    std::cout << "\n=== Exercise 4: Linked List ===" << std::endl;
    Node* head = new Node(1, new Node(2, new Node(3)));
    printList(head);
    freeList(head);

    // Exercise 5
    std::cout << "\n=== Exercise 5: Rectangle Class ===" << std::endl;
    Rectangle r1(4.0, 4.0);
    Rectangle r2(2.0, 8.0);
    r1.display();
    r2.display();
    std::cout << "r1 == r2 (same area): " << (r1 == r2 ? "yes" : "no") << std::endl;

    return 0;
}
