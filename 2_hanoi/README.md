# Assignment 2: Tower of Hanoi

## Description
Implementation of the classic Tower of Hanoi problem with both recursive and iterative solutions.

## Features
- **Recursive solution** (classic approach)
- **Iterative solution** (using explicit stack)
- **Minimum moves calculation** (2^n - 1 formula)
- **Input validation**

## Functions
1. `hanoi_recursive()` - Recursive solution
2. `hanoi_iterative()` - Stack-based iterative solution  
3. `calculate_min_moves()` - Calculates minimum moves required

## Complexity Analysis
| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Recursive | O(2^n) | O(n) (recursion stack) |
| Iterative | O(2^n) | O(n) (explicit stack) |
| Min Moves | O(n) | O(1) |

## Formula
Minimum moves required for n disks: **2^n - 1**

Examples:
- 1 disk → 1 move
- 2 disks → 3 moves  
- 3 disks → 7 moves
- 4 disks → 15 moves

Number of disks: 3

Recursive Solution:
-------------------
-Move disk 1 from A to C



-Move disk 2 from A to B




-Move disk 1 from C to B



-Move disk 3 from A to C



-Move disk 1 from B to A




-Move disk 2 from B to C



-Move disk 1 from A to C

Total moves (recursive): 7
