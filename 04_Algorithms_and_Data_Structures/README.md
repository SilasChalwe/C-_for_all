# 04 – Algorithms & Data Structures 🔵

> **Goal:** Understand and implement the classic algorithms and data structures that form the foundation of computer science and software engineering.

---

## Topics Covered

### Sorting Algorithms
| File | Algorithm | Time Complexity |
|------|-----------|-----------------|
| [sorting/bubble_sort.cpp](./sorting/bubble_sort.cpp) | Bubble Sort | O(n²) |
| [sorting/selection_sort.cpp](./sorting/selection_sort.cpp) | Selection Sort | O(n²) |
| [sorting/insertion_sort.cpp](./sorting/insertion_sort.cpp) | Insertion Sort | O(n²) |
| [sorting/merge_sort.cpp](./sorting/merge_sort.cpp) | Merge Sort | O(n log n) |
| [sorting/quick_sort.cpp](./sorting/quick_sort.cpp) | Quick Sort | O(n log n) avg |

### Searching Algorithms
| File | Algorithm | Time Complexity |
|------|-----------|-----------------|
| [searching/linear_search.cpp](./searching/linear_search.cpp) | Linear Search | O(n) |
| [searching/binary_search.cpp](./searching/binary_search.cpp) | Binary Search | O(log n) |

### Recursion
| File | Topic |
|------|-------|
| [recursion/basics.cpp](./recursion/basics.cpp) | Factorial, Fibonacci, power |
| [recursion/backtracking.cpp](./recursion/backtracking.cpp) | N-Queens, maze solver |

### Data Structures
| File | Structure |
|------|-----------|
| [data_structures/linked_list.cpp](./data_structures/linked_list.cpp) | Singly linked list |
| [data_structures/stack.cpp](./data_structures/stack.cpp) | Stack (array-based + linked list) |
| [data_structures/queue.cpp](./data_structures/queue.cpp) | Queue (circular array + linked list) |
| [data_structures/binary_tree.cpp](./data_structures/binary_tree.cpp) | Binary Search Tree |
| [data_structures/graph.cpp](./data_structures/graph.cpp) | Graph — BFS and DFS |

---

## Learning Objectives

After finishing this section you will be able to:

- Implement and compare sorting algorithms by time complexity.
- Perform linear and binary search.
- Solve problems using recursion and backtracking.
- Build and manipulate linked lists, stacks, queues, trees, and graphs from scratch.

---

## How to Compile

```bash
g++ -std=c++17 -Wall -o output sorting/merge_sort.cpp && ./output
```

---

*Previous section → [03 Advanced](../03_Advanced/)  |  Next section → [05 Projects](../05_Projects/)*
