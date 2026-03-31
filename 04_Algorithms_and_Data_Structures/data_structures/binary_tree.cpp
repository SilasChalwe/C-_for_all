// ============================================================
// data_structures/binary_tree.cpp
// Topic: Binary Search Tree (BST)
// Author: Silas Chalwe
// ============================================================
//
// BST property: for every node N,
//   all keys in left subtree  < N.key
//   all keys in right subtree > N.key
//
// Operations: insert, search, delete, traversals
// ============================================================

#include <iostream>
#include <queue>
#include <vector>

struct Node {
    int   key;
    Node* left;
    Node* right;
    explicit Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
    Node* root;

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key) node->left  = insert(node->left,  key);
        else if (key > node->key) node->right = insert(node->right, key);
        // duplicates ignored
        return node;
    }

    bool search(Node* node, int key) const {
        if (!node)           return false;
        if (key == node->key) return true;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }

    Node* minNode(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* remove(Node* node, int key) {
        if (!node) return nullptr;
        if      (key < node->key) node->left  = remove(node->left, key);
        else if (key > node->key) node->right = remove(node->right, key);
        else {
            // Found — three cases
            if (!node->left)  { Node* tmp = node->right; delete node; return tmp; }
            if (!node->right) { Node* tmp = node->left;  delete node; return tmp; }
            // Two children: replace with in-order successor
            Node* succ = minNode(node->right);
            node->key  = succ->key;
            node->right = remove(node->right, succ->key);
        }
        return node;
    }

    // Traversals
    void inOrder(Node* node)  const { if (!node) return; inOrder(node->left); std::cout << node->key << " "; inOrder(node->right); }
    void preOrder(Node* node) const { if (!node) return; std::cout << node->key << " "; preOrder(node->left); preOrder(node->right); }
    void postOrder(Node* node)const { if (!node) return; postOrder(node->left); postOrder(node->right); std::cout << node->key << " "; }

    int height(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(height(node->left), height(node->right));
    }

    void clear(Node* node) { if (!node) return; clear(node->left); clear(node->right); delete node; }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(int key)       { root = insert(root, key); }
    bool search(int key) const { return search(root, key); }
    void remove(int key)       { root = remove(root, key); }
    int  height()        const { return height(root); }

    void inOrder()   const { std::cout << "In-order:   "; inOrder(root);   std::cout << std::endl; }
    void preOrder()  const { std::cout << "Pre-order:  "; preOrder(root);  std::cout << std::endl; }
    void postOrder() const { std::cout << "Post-order: "; postOrder(root); std::cout << std::endl; }

    void levelOrder() const {
        if (!root) return;
        std::queue<Node*> q;
        q.push(root);
        std::cout << "Level-order: ";
        while (!q.empty()) {
            Node* n = q.front(); q.pop();
            std::cout << n->key << " ";
            if (n->left)  q.push(n->left);
            if (n->right) q.push(n->right);
        }
        std::cout << std::endl;
    }
};

int main() {
    BST tree;
    for (int k : {50, 30, 70, 20, 40, 60, 80, 10, 35}) tree.insert(k);

    std::cout << "=== BST Traversals ===" << std::endl;
    tree.inOrder();    // should print sorted
    tree.preOrder();
    tree.postOrder();
    tree.levelOrder();
    std::cout << "Height: " << tree.height() << std::endl;

    std::cout << "\n=== Search ===" << std::endl;
    std::cout << "Search 40: " << (tree.search(40) ? "found" : "not found") << std::endl;
    std::cout << "Search 99: " << (tree.search(99) ? "found" : "not found") << std::endl;

    std::cout << "\n=== Delete ===" << std::endl;
    tree.remove(30); // node with two children
    tree.inOrder();
    tree.remove(10); // leaf
    tree.inOrder();

    return 0;
}
