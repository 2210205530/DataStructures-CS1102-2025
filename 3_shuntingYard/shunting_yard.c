/**
 * student name [meseud hadis redi]
 * student id[2210205530]
 * file shunting_yard.c
 * brief Shunting Yard Algorithm for infix to postfix conversion
 * Time Complexity: O(n) where n is expression length
 * Space Complexity: O(n) for stack and output
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

// Stack structure
typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

/**
 * Initialize stack
 */
void init_stack(Stack *s) {
    s->top = -1;
}

/**
 * Check if stack is empty
 */
int is_empty(Stack *s) {
    return s->top == -1;
}

/**
 * Check if stack is full
 */
int is_full(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

/**
 * Push element to stack
 */
void push(Stack *s, char value) {
    if (is_full(s)) {
        printf("Error: Stack overflow\n");
        return;
    }
    s->data[++(s->top)] = value;
}

/**
 * Pop element from stack
 */
char pop(Stack *s) {
    if (is_empty(s)) {
        printf("Error: Stack underflow\n");
        return '\0';
    }
    return s->data[(s->top)--];
}

/**
 * Peek top element
 */
char peek(Stack *s) {
    if (is_empty(s)) {
        return '\0';
    }
    return s->data[s->top];
}

/**
 * Get precedence of operator
 * op Operator character
 * return Precedence value (higher = more precedence)
 */
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

/**
 * Check if character is operator
 */
int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

/**
 * Check if character is left parenthesis
 */
int is_left_parenthesis(char c) {
    return c == '(' || c == '[' || c == '{';
}

/**
 * Check if character is right parenthesis
 */
int is_right_parenthesis(char c) {
    return c == ')' || c == ']' || c == '}';
}

/**
 * Get matching parenthesis
 */
char get_matching_parenthesis(char c) {
    switch (c) {
        case '(': return ')';
        case ')': return '(';
        case '[': return ']';
        case ']': return '[';
        case '{': return '}';
        case '}': return '{';
        default: return '\0';
    }
}

/**
 * Shunting Yard Algorithm: Convert infix to postfix
 *  infix Input expression in infix notation
 *  postfix Output buffer for postfix expression
 * return 1 if successful, 0 if error
 */
int infix_to_postfix(const char *infix, char *postfix) {
    Stack stack;
    init_stack(&stack);
    
    int i, j = 0;
    char token, top;
    
    for (i = 0; infix[i] != '\0'; i++) {
        token = infix[i];
        
        // Skip spaces
        if (token == ' ') {
            continue;
        }
        
        // If operand (letter or digit), add to output
        if (isalnum(token)) {
            postfix[j++] = token;
            postfix[j++] = ' '; // Add space for readability
        }
        // If left parenthesis, push to stack
        else if (is_left_parenthesis(token)) {
            push(&stack, token);
        }
        // If right parenthesis
        else if (is_right_parenthesis(token)) {
            char matching = get_matching_parenthesis(token);
            
            // Pop until matching left parenthesis
            while (!is_empty(&stack) && peek(&stack) != matching) {
                postfix[j++] = pop(&stack);
                postfix[j++] = ' ';
            }
            
            // Check for mismatched parentheses
            if (is_empty(&stack)) {
                printf("Error: Mismatched parentheses\n");
                return 0;
            }
            
            // Pop the left parenthesis
            pop(&stack);
        }
        // If operator
        else if (is_operator(token)) {
            while (!is_empty(&stack) && 
                   precedence(peek(&stack)) >= precedence(token) &&
                   !is_left_parenthesis(peek(&stack))) {
                // Special case: '^' is right-associative
                if (token == '^' && peek(&stack) == '^') {
                    break;
                }
                postfix[j++] = pop(&stack);
                postfix[j++] = ' ';
            }
            push(&stack, token);
        }
        else {
            printf("Error: Invalid character '%c'\n", token);
            return 0;
        }
    }
    
    // Pop all remaining operators
    while (!is_empty(&stack)) {
        top = pop(&stack);
        
        // Check for mismatched parentheses
        if (is_left_parenthesis(top)) {
            printf("Error: Mismatched parentheses\n");
            return 0;
        }
        
        postfix[j++] = top;
        postfix[j++] = ' ';
    }
    
    // Remove trailing space and null-terminate
    if (j > 0) {
        postfix[j - 1] = '\0';
    } else {
        postfix[0] = '\0';
    }
    
    return 1;
}

/**
 * Evaluate postfix expression
 * postfix Postfix expression
 * Result of evaluation
 */
int evaluate_postfix(const char *postfix) {
    Stack stack;
    init_stack(&stack);
    
    int i, operand1, operand2, result;
    char token;
    
    for (i = 0; postfix[i] != '\0'; i++) {
        token = postfix[i];
        
        // Skip spaces
        if (token == ' ') {
            continue;
        }
        
        // If digit, push to stack (convert char to int)
        if (isdigit(token)) {
            push(&stack, token - '0'); // Convert '0' -> 0, '1' -> 1, etc.
        }
        // If operator
        else if (is_operator(token)) {
            // Pop two operands
            operand2 = pop(&stack);
            operand1 = pop(&stack);
            
            // Perform operation
            switch (token) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        printf("Error: Division by zero\n");
                        return 0;
                    }
                    result = operand1 / operand2;
                    break;
                case '^':
                    result = 1;
                    for (int k = 0; k < operand2; k++) {
                        result *= operand1;
                    }
                    break;
            }
            
            // Push result back to stack
            push(&stack, result);
        }
    }
    
    // Final result is on top of stack
    return pop(&stack);
}

/**
 * Main function to demonstrate Shunting Yard Algorithm
 */
int main() {
    printf("=== SHUNTING YARD ALGORITHM ===\n");
    printf("Infix to Postfix Conversion\n\n");
    
    // Test case 1: Simple expression
    char infix1[] = "A + B * C";
    char postfix1[100];
    
    printf("Test 1:\n");
    printf("Infix:   %s\n", infix1);
    
    if (infix_to_postfix(infix1, postfix1)) {
        printf("Postfix: %s\n", postfix1);
    }
    printf("\n");
    
    // Test case 2: With parentheses
    char infix2[] = "(A + B) * C";
    char postfix2[100];
    
    printf("Test 2:\n");
    printf("Infix:   %s\n", infix2);
    
    if (infix_to_postfix(infix2, postfix2)) {
        printf("Postfix: %s\n", postfix2);
    }
    printf("\n");
    
    // Test case 3: Complex expression
    char infix3[] = "3 + 4 * 2 / (1 - 5) ^ 2";
    char postfix3[100];
    
    printf("Test 3:\n");
    printf("Infix:   %s\n", infix3);
    
    if (infix_to_postfix(infix3, postfix3)) {
        printf("Postfix: %s\n", postfix3);
        
        // Evaluate since it has numbers
        int result = evaluate_postfix(postfix3);
        printf("Result:  %d\n", result);
    }
    
    return 0;
}
