// ============================================================
// recursion/backtracking.cpp
// Topic: N-Queens, Maze Solver
// Author: Silas Chalwe
// ============================================================
//
// Backtracking: explore all possibilities by building solutions
// incrementally and abandoning ("backtracking") as soon as you
// determine that a partial solution cannot lead to a valid answer.
// ============================================================

#include <iostream>
#include <vector>
#include <string>

// ============================================================
// N-QUEENS: Place N queens on an NxN board so no two attack each other.
// ============================================================

bool isSafe(const std::vector<int>& board, int row, int col) {
    // Check all previous rows
    for (int r = 0; r < row; r++) {
        if (board[r] == col)                    return false; // same column
        if (std::abs(board[r] - col) == row - r) return false; // diagonal
    }
    return true;
}

void solveNQueens(std::vector<int>& board, int row, int n, int& solutions) {
    if (row == n) {
        solutions++;
        // Print the board
        std::cout << "Solution " << solutions << ":" << std::endl;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                std::cout << (board[r] == c ? "Q " : ". ");
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        return;
    }
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            solveNQueens(board, row + 1, n, solutions);
            board[row] = -1; // backtrack
        }
    }
}

// ============================================================
// MAZE SOLVER: Find a path from top-left to bottom-right.
// ============================================================

void printMaze(const std::vector<std::vector<int>>& maze) {
    for (const auto& row : maze) {
        for (int cell : row) {
            if (cell == 1) std::cout << "X ";       // wall
            else if (cell == 2) std::cout << "* ";   // path
            else std::cout << ". ";                   // open
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool solveMaze(std::vector<std::vector<int>>& maze, int row, int col,
               int destRow, int destCol) {
    int n = static_cast<int>(maze.size());
    int m = static_cast<int>(maze[0].size());

    // Out of bounds or wall or already visited
    if (row < 0 || row >= n || col < 0 || col >= m || maze[row][col] != 0)
        return false;

    // Mark current cell as part of the solution path
    maze[row][col] = 2;

    // Destination reached?
    if (row == destRow && col == destCol) return true;

    // Try all four directions: down, right, up, left
    if (solveMaze(maze, row+1, col, destRow, destCol)) return true;
    if (solveMaze(maze, row, col+1, destRow, destCol)) return true;
    if (solveMaze(maze, row-1, col, destRow, destCol)) return true;
    if (solveMaze(maze, row, col-1, destRow, destCol)) return true;

    // Backtrack
    maze[row][col] = 0;
    return false;
}

// ============================================================
int main() {
    // N-Queens (4x4 for readable output)
    std::cout << "=== 4-Queens Solutions ===" << std::endl;
    int n = 4;
    std::vector<int> board(n, -1);
    int solutions = 0;
    solveNQueens(board, 0, n, solutions);
    std::cout << "Total solutions for " << n << "-Queens: " << solutions << std::endl;

    // Maze solver
    std::cout << "\n=== Maze Solver ===" << std::endl;
    std::vector<std::vector<int>> maze = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    std::cout << "Maze (X=wall, .=open):" << std::endl;
    printMaze(maze);

    if (solveMaze(maze, 0, 0, 4, 4)) {
        std::cout << "Path found (*=path):" << std::endl;
        printMaze(maze);
    } else {
        std::cout << "No path found." << std::endl;
    }

    return 0;
}
