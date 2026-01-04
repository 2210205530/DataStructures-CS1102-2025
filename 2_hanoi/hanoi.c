/**
 * file hanoi.c
 * brief Tower of Hanoi implementation with recursive and iterative solutions
 * sstudent name [meseud hadis redi]
 * student id [2210205530]
 * Time Complexity: O(2^n) - exponential
 * Space Complexity: O(n) - recursion depth
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Recursive solution for Tower of Hanoi
 */
void hanoi_recursive(int n, char from, char to, char aux, int *move_count) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", from, to);
        (*move_count)++;
        return;
    }
    
    hanoi_recursive(n-1, from, aux, to, move_count);
    printf("Move disk %d from %c to %c\n", n, from, to);
    (*move_count)++;
    hanoi_recursive(n-1, aux, to, from, move_count);
}

/**
 * Structure for stack implementation (for iterative solution)
 */
typedef struct {
    int n;
    char from;
    char to;
    char aux;
    int state; 
} StackFrame;

/**
 * Iterative solution using explicit stack
 */
void hanoi_iterative(int n) {
    if (n <= 0) {
        printf("Error: Number of disks must be positive\n");
        return;
    }
    
    // Create stack
    StackFrame* stack = (StackFrame*)malloc((n * 2) * sizeof(StackFrame));
    if (!stack) {
        printf("Error: Memory allocation failed\n");
        return;
    }
    
    int top = 0;
    int move_count = 0;
    
    // Push initial frame
    stack[top].n = n;
    stack[top].from = 'A';
    stack[top].to = 'C';
    stack[top].aux = 'B';
    stack[top].state = 0;
    top++;
    
    while (top > 0) {
        top--;
        StackFrame current = stack[top];
        
        if (current.n == 1) {
            printf("Move disk 1 from %c to %c\n", current.from, current.to);
            move_count++;
        } else if (current.state == 0) {
            // Push frames for recursive calls
            // First push second recursive call
            stack[top].n = current.n;
            stack[top].from = current.from;
            stack[top].to = current.to;
            stack[top].aux = current.aux;
            stack[top].state = 1;
            top++;
            
            // Push first recursive call
            stack[top].n = current.n - 1;
            stack[top].from = current.from;
            stack[top].to = current.aux;
            stack[top].aux = current.to;
            stack[top].state = 0;
            top++;
        } else if (current.state == 1) {
            // Print current move
            printf("Move disk %d from %c to %c\n", current.n, current.from, current.to);
            move_count++;
            
            // Push third recursive call
            stack[top].n = current.n - 1;
            stack[top].from = current.aux;
            stack[top].to = current.to;
            stack[top].aux = current.from;
            stack[top].state = 0;
            top++;
        }
    }
    
    printf("\nTotal moves (iterative): %d\n", move_count);
    free(stack);
}

/**
 * Calculates minimum moves required (2^n - 1)
 * param n Number of disks
 * return Minimum moves required
 */
int calculate_min_moves(int n) {
    if (n <= 0) return 0;
    
    int moves = 1;
    for (int i = 0; i < n; i++) {
        moves *= 2;
    }
    return moves - 1;
}

/**
 * Main function to demonstrate Hanoi Tower
 */
int main() {
    int n = 3;
    int move_count = 0;
    
    printf("=== TOWER OF HANOI ===\n");
    printf("Number of disks: %d\n\n", n);
    
    printf("Recursive Solution:\n");
    printf("-------------------\n");
    hanoi_recursive(n, 'A', 'C', 'B', &move_count);
    printf("\nTotal moves (recursive): %d\n", move_count);
    
    printf("\nMinimum moves required (2^n - 1): %d\n", calculate_min_moves(n));
    
    printf("\nIterative Solution:\n");
    printf("-------------------\n");
    hanoi_iterative(n);
    
    return 0;
}
