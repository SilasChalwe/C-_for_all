// ============================================================
// data_structures/queue.cpp
// Topic: Queue — FIFO (First In, First Out)
// Author: Silas Chalwe
// ============================================================

#include <iostream>
#include <deque>
#include <string>
#include <stdexcept>

// ---- Queue backed by std::deque ----
template <typename T>
class Queue {
    std::deque<T> data;

public:
    void enqueue(const T& val) { data.push_back(val); }

    void dequeue() {
        if (empty()) throw std::underflow_error("Queue underflow");
        data.pop_front();
    }

    T& front() {
        if (empty()) throw std::underflow_error("Queue is empty");
        return data.front();
    }

    T& back() {
        if (empty()) throw std::underflow_error("Queue is empty");
        return data.back();
    }

    bool   empty() const { return data.empty(); }
    size_t size()  const { return data.size();  }

    void display() const {
        std::cout << "Queue (front→back): ";
        for (const auto& v : data) std::cout << v << " ";
        std::cout << std::endl;
    }
};

// ---- Application: BFS level-order tree traversal (simplified) ----
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

void bfs(TreeNode* root) {
    if (!root) return;
    Queue<TreeNode*> q;
    q.enqueue(root);
    std::cout << "BFS (level-order): ";
    while (!q.empty()) {
        TreeNode* node = q.front(); q.dequeue();
        std::cout << node->val << " ";
        if (node->left)  q.enqueue(node->left);
        if (node->right) q.enqueue(node->right);
    }
    std::cout << std::endl;
}

// ---- Priority Queue simulation (min-heap concept) ----
// Use std::priority_queue (max-heap by default)
#include <queue>

void priorityQueueDemo() {
    std::cout << "\n=== Priority Queue (max-heap) ===" << std::endl;
    std::priority_queue<int> pq;
    pq.push(30); pq.push(10); pq.push(50); pq.push(20);
    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << std::endl;

    // Min-heap
    std::cout << "Min-heap: ";
    std::priority_queue<int, std::vector<int>, std::greater<int>> minPQ;
    minPQ.push(30); minPQ.push(10); minPQ.push(50); minPQ.push(20);
    while (!minPQ.empty()) {
        std::cout << minPQ.top() << " ";
        minPQ.pop();
    }
    std::cout << std::endl;
}

int main() {
    Queue<std::string> q;
    q.enqueue("Alice");
    q.enqueue("Bob");
    q.enqueue("Charlie");
    q.display();
    std::cout << "Front: " << q.front() << std::endl;
    q.dequeue();
    q.display();

    // BFS on a small tree:
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    TreeNode* root = new TreeNode(1);
    root->left  = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left  = new TreeNode(4);
    root->left->right = new TreeNode(5);

    std::cout << "\n";
    bfs(root);

    // Cleanup
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;

    priorityQueueDemo();

    return 0;
}
