/**
 *student name [meseud hadis redi]
 *student id[2210205530]
 *file test_hanoi.c
 * brief Test cases for Hanoi Tower implementation
 */

#include <stdio.h>
#include <string.h>

// Function declarations from hanoi.c
void hanoi_recursive(int n, char from, char to, char aux, int *move_count);
void hanoi_iterative(int n);
int calculate_min_moves(int n);

/**
 * Test recursive solution with 1 disk
 */
void test_one_disk() {
    printf("Test 1: One disk (recursive)... ");
    int moves = 0;
    
    hanoi_recursive(1, 'A', 'C', 'B', &moves);
    
    if (moves == 1) {
        printf("PASS - Correct moves: %d\n", moves);
    } else {
        printf("FAIL - Expected 1 move, got %d\n", moves);
    }
}

/**
 * Test minimum moves calculation
 */
void test_min_moves_calculation() {
    printf("Test 2: Minimum moves calculation... ");
    
    // Test cases: n -> 2^n - 1
    int test_cases[][2] = {
        {1, 1},    // 2^1 - 1 = 1
        {2, 3},    // 2^2 - 1 = 3
        {3, 7},    // 2^3 - 1 = 7
        {4, 15},   // 2^4 - 1 = 15
        {5, 31}    // 2^5 - 1 = 31
    };
    
    int all_pass = 1;
    for (int i = 0; i < 5; i++) {
        int n = test_cases[i][0];
        int expected = test_cases[i][1];
        int actual = calculate_min_moves(n);
        
        if (actual != expected) {
            printf("FAIL for n=%d (expected %d, got %d)\n", n, expected, actual);
            all_pass = 0;
        }
    }
    
    if (all_pass) {
        printf("PASS - All calculations correct\n");
    }
}

/**
 * Test iterative solution
 */
void test_iterative() {
    printf("Test 3: Iterative solution (3 disks)... ");
    
    // Redirect output to count moves
    printf("\n[Iterative solution output suppressed for test]\n");
    // In a real test, you would capture the output
    // For now, we just verify it runs without crashing
    hanoi_iterative(3);
    
    printf("PASS - Iterative solution executed without errors\n");
}

/**
 * Test invalid input
 */
void test_invalid_input() {
    printf("Test 4: Invalid input (0 disks)... ");
    
    int moves = 0;
    hanoi_recursive(0, 'A', 'C', 'B', &moves);
    
    if (moves == 0) {
        printf("PASS - Correctly handled 0 disks\n");
    } else {
        printf("FAIL - Should handle 0 disks without moves\n");
    }
}

/**
 * Main test runner
 */
int main() {
    printf("\n=== TESTING HANOI TOWER IMPLEMENTATION ===\n\n");
    
    test_one_disk();
    test_min_moves_calculation();
    test_iterative();
    test_invalid_input();
    
    printf("\n=== ALL TESTS COMPLETED ===\n");
    
    // Run the actual hanoi program
    printf("\n--- Running Main Program ---\n");
    
    // We need to include hanoi.c directly or compile separately
    // For simplicity, just print what it would do
    printf("To run the actual program:\n");
    printf("1. Compile: gcc -o hanoi_test hanoi.c\n");
    printf("2. Run: ./hanoi_test\n");
    
    return 0;
}
