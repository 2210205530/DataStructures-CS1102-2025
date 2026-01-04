/**
 *student name [meseud hadis redi]
 *student id[2210205530]
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Include the functions from cll.c
#include "cll.c"

/**
 * Test creation and basic insertion
 */
void test_creation_and_insert() {
    printf("Test 1: Creation and insertion... ");
    
    CircularLinkedList* cll = create_cll();
    assert(cll != NULL);
    assert(is_empty(cll) == 1);
    assert(get_size(cll) == 0);
    
    // Insert at head
    insert_at_head(cll, 10);
    assert(get_size(cll) == 1);
    assert(get_head(cll)->data == 10);
    assert(get_tail(cll)->data == 10);
    assert(get_head(cll)->next == get_head(cll)); // Should point to itself
    
    // Insert at tail
    insert_at_tail(cll, 20);
    assert(get_size(cll) == 2);
    assert(get_head(cll)->data == 10);
    assert(get_tail(cll)->data == 20);
    assert(get_tail(cll)->next == get_head(cll)); // Tail should point to head
    
    // Insert at position
    insert_at_position(cll, 15, 1);
    assert(get_size(cll) == 3);
    
    free_cll(cll);
    printf("PASS\n");
}

/**
 * Test deletion operations
 */
void test_deletion() {
    printf("Test 2: Deletion operations... ");
    
    CircularLinkedList* cll = create_cll();
    
    // Add elements
    insert_at_tail(cll, 10);
    insert_at_tail(cll, 20);
    insert_at_tail(cll, 30);
    insert_at_tail(cll, 40);
    
    assert(get_size(cll) == 4);
    
    // Delete from head
    int deleted = delete_from_head(cll);
    assert(deleted == 10);
    assert(get_size(cll) == 3);
    assert(get_head(cll)->data == 20);
    
    // Delete from tail
    deleted = delete_from_tail(cll);
    assert(deleted == 40);
    assert(get_size(cll) == 2);
    assert(get_tail(cll)->data == 30);
    
    // Delete by value
    assert(delete_by_value(cll, 20) == 1);
    assert(get_size(cll) == 1);
    assert(get_head(cll)->data == 30);
    assert(get_tail(cll)->data == 30);
    
    // Delete at position
    insert_at_tail(cll, 40);
    insert_at_tail(cll, 50);
    deleted = delete_at_position(cll, 1);
    assert(deleted == 40);
    assert(get_size(cll) == 2);
    
    free_cll(cll);
    printf("PASS\n");
}

/**
 * Test search function
 */
void test_search() {
    printf("Test 3: Search function... ");
    
    CircularLinkedList* cll = create_cll();
    
    insert_at_tail(cll, 10);
    insert_at_tail(cll, 20);
    insert_at_tail(cll, 30);
    insert_at_tail(cll, 40);
    
    assert(search(cll, 10) == 0);
    assert(search(cll, 30) == 2);
    assert(search(cll, 40) == 3);
    assert(search(cll, 99) == -1); // Not found
    
    free_cll(cll);
    printf("PASS\n");
}

/**
 * Test circular property
 */
void test_circular_property() {
    printf("Test 4: Circular property... ");
    
    CircularLinkedList* cll = create_cll();
    
    insert_at_tail(cll, 10);
    insert_at_tail(cll, 20);
    insert_at_tail(cll, 30);
    
    // Traverse 2 full cycles
    Node* current = get_head(cll);
    int values[6]; // 3 elements × 2 cycles
    int count = 0;
    
    do {
        values[count++] = current->data;
        current = current->next;
    } while (current != get_head(cll)); // First cycle
    
    // Continue for second cycle
    do {
        values[count++] = current->data;
        current = current->next;
    } while (current != get_head(cll)); // Second cycle
    
    // Verify both cycles have same values
    assert(count == 6);
    for (int i = 0; i < 3; i++) {
        assert(values[i] == values[i + 3]);
    }
    
    // Verify tail points to head
    assert(get_tail(cll)->next == get_head(cll));
    
    free_cll(cll);
    printf("PASS\n");
}

/**
 * Test Josephus problem
 */
void test_josephus() {
    printf("Test 5: Josephus problem... ");
    
    // Test known case: n=7, k=3, survivor should be 4
    int survivor = josephus_problem(7, 3);
    assert(survivor == 4);
    
    // Test simple case: n=1, k=anything, survivor should be 1
    survivor = josephus_problem(1, 5);
    assert(survivor == 1);
    
    printf("PASS\n");
}

/**
 * Test edge cases
 */
void test_edge_cases() {
    printf("Test 6: Edge cases... ");
    
    // Test empty list operations
    CircularLinkedList* cll = create_cll();
    
    assert(delete_from_head(cll) == -1);
    assert(delete_from_tail(cll) == -1);
    assert(delete_by_value(cll, 10) == 0);
    assert(delete_at_position(cll, 0) == -1);
    assert(search(cll, 10) == -1);
    
    // Test invalid positions
    assert(insert_at_position(cll, 10, -1) == 0);
    assert(insert_at_position(cll, 10, 1) == 0);
    
    // Single element list
    insert_at_head(cll, 5);
    assert(get_size(cll) == 1);
    assert(get_head(cll) == get_tail(cll));
    assert(get_head(cll)->next == get_head(cll));
    
    // Delete single element
    assert(delete_from_head(cll) == 5);
    assert(is_empty(cll));
    
    free_cll(cll);
    printf("PASS\n");
}

/**
 * Test memory management
 */
void test_memory_management() {
    printf("Test 7: Memory management... ");
    
    // Create large list
    CircularLinkedList* cll = create_cll();
    
    for (int i = 0; i < 100; i++) {
        insert_at_tail(cll, i);
    }
    assert(get_size(cll) == 100);
    
    // Verify circular property for large list
    Node* current = get_head(cll);
    for (int i = 0; i < 100; i++) {
        current = current->next;
    }
    assert(current == get_head(cll));
    
    // Delete half
    for (int i = 0; i < 50; i++) {
        delete_from_head(cll);
    }
    assert(get_size(cll) == 50);
    
    // Free should not crash
    free_cll(cll);
    
    printf("PASS\n");
}

/**
 * Main test runner
 */
int main() {
    printf("\n=== TESTING CIRCULAR LINKED LIST ===\n\n");
    
    test_creation_and_insert();
    test_deletion();
    test_search();
    test_circular_property();
    test_josephus();
    test_edge_cases();
    test_memory_management();
    
    printf("\n=== ALL TESTS PASSED ===\n\n");
    
    printf("To run the main program:\n");
    printf("1. cd 6_CircularLinkedList\n");
    printf("2. gcc -o cll cll.c\n");
    printf("3. ./cll\n");
    
    return 0;
}
