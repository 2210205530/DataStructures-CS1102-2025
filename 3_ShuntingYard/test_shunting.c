/**
*student name [meseud hadis redi]
 *student id[2210205530]
 * file test_shunting.c
 * brief Test cases for Shunting Yard Algorithm
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "shunting_yard.h"

// Function declarations (from shunting_yard.c)
int infix_to_postfix(const char *infix, char *postfix);
int evaluate_postfix(const char *postfix);

/**
 * Compare postfix output with expected result
 */
int compare_postfix(const char *infix, const char *expected) {
    char postfix[200];
    
    if (!infix_to_postfix(infix, postfix)) {
        return 0; // Conversion failed
    }
    
    return strcmp(postfix, expected) == 0;
}

/**
 * Test basic operators
 */
void test_basic_operators() {
    printf("Test 1: Basic operators... ");
    
    struct {
        char infix[50];
        char postfix[50];
    } tests[] = {
        {"A + B", "A B +"},
        {"A - B", "A B -"},
        {"A * B", "A B *"},
        {"A / B", "A B /"},
        {"A ^ B", "A B ^"}
    };
    
    int all_pass = 1;
    for (int i = 0; i < 5; i++) {
        if (!compare_postfix(tests[i].infix, tests[i].postfix)) {
            printf("FAIL at test %d\n", i + 1);
            all_pass = 0;
            break;
        }
    }
    
    if (all_pass) {
        printf("PASS\n");
    }
}

/**
 * Test operator precedence
 */
void test_precedence() {
    printf("Test 2: Operator precedence... ");
    
    if (compare_postfix("A + B * C", "A B C * +") &&
        compare_postfix("A * B + C", "A B * C +") &&
        compare_postfix("A + B - C * D / E", "A B + C D * E / -")) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
}

/**
 * Test parentheses
 */
void test_parentheses() {
    printf("Test 3: Parentheses... ");
    
    if (compare_postfix("(A + B) * C", "A B + C *") &&
        compare_postfix("A * (B + C)", "A B C + *") &&
        compare_postfix("(A + B) * (C - D)", "A B + C D - *")) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
}

/**
 * Test evaluation with numbers
 */
void test_evaluation() {
    printf("Test 4: Postfix evaluation... ");
    
    // Test simple expression
    char infix[] = "3 + 4 * 2";
    char postfix[100];
    
    if (infix_to_postfix(infix, postfix)) {
        int result = evaluate_postfix(postfix);
        if (result == 11) { // 3 + (4*2) = 11
            printf("PASS (3+4*2=%d)\n", result);
        } else {
            printf("FAIL (expected 11, got %d)\n", result);
        }
    } else {
        printf("FAIL (conversion error)\n");
    }
}

/**
 * Main test runner
 */
int main() {
    printf("\n=== TESTING SHUNTING YARD ALGORITHM ===\n\n");
    
    test_basic_operators();
    test_precedence();
    test_parentheses();
    test_evaluation();
    
    printf("\n=== ALL TESTS COMPLETED ===\n");
    
    return 0;
}
