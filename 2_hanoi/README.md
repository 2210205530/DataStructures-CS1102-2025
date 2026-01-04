# Assignment 2: Tower of Hanoi

## 📋 Description
Implementation of the classic Tower of Hanoi problem with both recursive and iterative solutions.

## 🎯 Features
- **Recursive solution** (classic approach)
- **Iterative solution** (using explicit stack)
- **Minimum moves calculation** (2^n - 1 formula)
- **Input validation**

## ⚙️ Functions
1. `hanoi_recursive()` - Recursive solution
2. `hanoi_iterative()` - Stack-based iterative solution  
3. `calculate_min_moves()` - Calculates minimum moves required

## 📊 Complexity Analysis
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
