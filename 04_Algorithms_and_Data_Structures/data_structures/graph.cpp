// ============================================================
// data_structures/graph.cpp
// Topic: Graph — Adjacency List, BFS, DFS
// Author: Silas Chalwe
// ============================================================
//
// A graph G = (V, E) consists of vertices and edges.
// Representations: adjacency matrix, adjacency list (used here).
//
// BFS (Breadth-First Search): explores level by level (uses queue).
// DFS (Depth-First Search):   explores as deep as possible (uses stack/recursion).
// ============================================================

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <set>
#include <string>
#include <algorithm>   // std::reverse

class Graph {
    int numVertices;
    bool directed;
    std::vector<std::vector<int>> adj; // adjacency list

public:
    Graph(int v, bool isDirected = false)
        : numVertices(v), directed(isDirected), adj(v) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }

    // ---- BFS: shortest path (unweighted) ----
    void bfs(int start) const {
        std::vector<bool> visited(numVertices, false);
        std::queue<int> q;
        visited[start] = true;
        q.push(start);

        std::cout << "BFS from " << start << ": ";
        while (!q.empty()) {
            int v = q.front(); q.pop();
            std::cout << v << " ";
            for (int neighbour : adj[v]) {
                if (!visited[neighbour]) {
                    visited[neighbour] = true;
                    q.push(neighbour);
                }
            }
        }
        std::cout << std::endl;
    }

    // ---- DFS iterative ----
    void dfs(int start) const {
        std::vector<bool> visited(numVertices, false);
        std::stack<int> stk;
        stk.push(start);

        std::cout << "DFS from " << start << ": ";
        while (!stk.empty()) {
            int v = stk.top(); stk.pop();
            if (!visited[v]) {
                visited[v] = true;
                std::cout << v << " ";
                // Push in reverse order so leftmost neighbour is processed first
                for (int i = static_cast<int>(adj[v].size()) - 1; i >= 0; i--)
                    if (!visited[adj[v][i]]) stk.push(adj[v][i]);
            }
        }
        std::cout << std::endl;
    }

    // ---- DFS recursive ----
    void dfsRecursive(int v, std::vector<bool>& visited) const {
        visited[v] = true;
        std::cout << v << " ";
        for (int neighbour : adj[v]) {
            if (!visited[neighbour]) dfsRecursive(neighbour, visited);
        }
    }

    void dfsRecursiveStart(int start) const {
        std::vector<bool> visited(numVertices, false);
        std::cout << "DFS recursive from " << start << ": ";
        dfsRecursive(start, visited);
        std::cout << std::endl;
    }

    // ---- Shortest path (BFS) ----
    std::vector<int> shortestPath(int src, int dest) const {
        std::vector<int> parent(numVertices, -1);
        std::vector<bool> visited(numVertices, false);
        std::queue<int> q;
        visited[src] = true;
        q.push(src);

        while (!q.empty()) {
            int v = q.front(); q.pop();
            if (v == dest) break;
            for (int nb : adj[v]) {
                if (!visited[nb]) {
                    visited[nb] = true;
                    parent[nb]  = v;
                    q.push(nb);
                }
            }
        }

        // Reconstruct path
        std::vector<int> path;
        if (!visited[dest]) return path; // no path
        for (int v = dest; v != -1; v = parent[v]) path.push_back(v);
        std::reverse(path.begin(), path.end());
        return path;
    }

    void display() const {
        std::cout << "Adjacency list:" << std::endl;
        for (int v = 0; v < numVertices; v++) {
            std::cout << v << " → ";
            for (int nb : adj[v]) std::cout << nb << " ";
            std::cout << std::endl;
        }
    }
};

int main() {
    // Undirected graph
    //   0 — 1 — 2
    //   |       |
    //   3 — 4 — 5
    Graph g(6);
    g.addEdge(0, 1); g.addEdge(1, 2);
    g.addEdge(0, 3); g.addEdge(2, 5);
    g.addEdge(3, 4); g.addEdge(4, 5);

    g.display();
    std::cout << std::endl;

    g.bfs(0);
    g.dfs(0);
    g.dfsRecursiveStart(0);

    auto path = g.shortestPath(0, 5);
    std::cout << "Shortest path 0→5: ";
    for (int v : path) std::cout << v << " ";
    std::cout << std::endl;

    // Directed graph
    std::cout << "\n=== Directed Graph ===" << std::endl;
    Graph dg(4, true);
    dg.addEdge(0, 1); dg.addEdge(0, 2);
    dg.addEdge(1, 3); dg.addEdge(2, 3);
    dg.display();
    dg.bfs(0);

    return 0;
}
