// ============================================================
// data_structures/linked_list.cpp
// Topic: Singly Linked List
// Author: Silas Chalwe
// ============================================================

#include <iostream>
#include <stdexcept>

struct Node {
    int   data;
    Node* next;
    explicit Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
    Node* head;
    int   size;

public:
    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList() { clear(); }

    void pushFront(int val) {
        Node* node = new Node(val);
        node->next = head;
        head = node;
        size++;
    }

    void pushBack(int val) {
        Node* node = new Node(val);
        if (!head) { head = node; }
        else {
            Node* cur = head;
            while (cur->next) cur = cur->next;
            cur->next = node;
        }
        size++;
    }

    void insertAt(int val, int pos) {
        if (pos < 0 || pos > size) throw std::out_of_range("Invalid position");
        if (pos == 0) { pushFront(val); return; }
        Node* cur = head;
        for (int i = 0; i < pos - 1; i++) cur = cur->next;
        Node* node = new Node(val);
        node->next = cur->next;
        cur->next  = node;
        size++;
    }

    void popFront() {
        if (!head) throw std::underflow_error("List is empty");
        Node* tmp = head;
        head = head->next;
        delete tmp;
        size--;
    }

    bool remove(int val) {
        if (!head) return false;
        if (head->data == val) { popFront(); return true; }
        Node* cur = head;
        while (cur->next && cur->next->data != val) cur = cur->next;
        if (!cur->next) return false;
        Node* tmp = cur->next;
        cur->next  = tmp->next;
        delete tmp;
        size--;
        return true;
    }

    bool contains(int val) const {
        Node* cur = head;
        while (cur) { if (cur->data == val) return true; cur = cur->next; }
        return false;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* cur  = head;
        while (cur) {
            Node* next = cur->next;
            cur->next  = prev;
            prev = cur;
            cur  = next;
        }
        head = prev;
    }

    int getSize() const { return size; }

    void clear() {
        while (head) { Node* tmp = head; head = head->next; delete tmp; }
        size = 0;
    }

    void print() const {
        Node* cur = head;
        while (cur) { std::cout << cur->data; if (cur->next) std::cout << " → "; cur = cur->next; }
        std::cout << " → nullptr" << std::endl;
    }
};

int main() {
    LinkedList list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushFront(0);
    list.insertAt(99, 2);
    std::cout << "After inserts: "; list.print();

    list.remove(99);
    std::cout << "After remove 99: "; list.print();

    std::cout << "Contains 2: " << (list.contains(2) ? "yes" : "no") << std::endl;

    list.reverse();
    std::cout << "Reversed: "; list.print();

    std::cout << "Size: " << list.getSize() << std::endl;

    return 0;
}
