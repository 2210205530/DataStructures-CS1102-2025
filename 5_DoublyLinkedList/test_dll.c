/**
 *student name [meseud hadis redi]
 *student id[2210205530]
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Include the functions from dll.c
// We'll include the source directly for testing
#include "dll.h"

/**
 * Test creation and basic insertion
 */
void test_creation_and_insert() {
    printf("Test 1: Creation and insertion... ");
    
    DoublyLinkedList* dll = create_dll();
    assert(dll != NULL);
    assert(get_size(dll) == 0);
    assert(is_empty(dll) == 1);
    
    // Insert at head
    insert_at_head(dll, 10);
    assert(get_size(dll) == 1);
    assert(dll->head->data == 10);
    assert(dll->tail->data == 10);
    
    // Insert at tail
    insert_at_tail(dll, 20);
    assert(get_size(dll) == 2);
    assert(dll->head->data == 10);
    assert(dll->tail->data == 20);
    
    // Insert at position
    insert_at_position(dll, 15, 1);
    assert(get_size(dll) == 3);
    
    // Verify order
    assert(dll->head->data == 10);
    assert(dll->head->next->data == 15);
    assert(dll->tail->data == 20);
    
    free_dll(dll);
    printf("PASS\n");
}

/**
 * Test deletion operations
 */
void test_deletion() {
    printf("Test 2: Deletion operations... ");
    
    DoublyLinkedList* dll = create_dll();
    
    // Add elements
    insert_at_tail(dll, 10);
    insert_at_tail(dll, 20);
    insert_at_tail(dll, 30);
    insert_at_tail(dll, 40);
    
    assert(get_size(dll) == 4);
    
    // Delete from head
    int deleted = delete_from_head(dll);
    assert(deleted == 10);
    assert(get_size(dll) == 3);
    assert(dll->head->data == 20);
    
    // Delete from tail
    deleted = delete_from_tail(dll);
    assert(deleted == 40);
    assert(get_size(dll) == 2);
    assert(dll->tail->data == 30);
    
    // Delete by value
    assert(delete_by_value(dll, 20) == 1);
    assert(get_size(dll) == 1);
    assert(dll->head->data == 30);
    assert(dll->tail->data == 30);
    
    // Delete at position
    insert_at_tail(dll, 40);
    insert_at_tail(dll, 50);
    deleted = delete_at_position(dll, 1);
    assert(deleted == 40);
    assert(get_size(dll) == 2);
    
    free_dll(dll);
    printf("PASS\n");
}

/**
 * Test search function
 */
void test_search() {
    printf("Test 3: Search function... ");
    
    DoublyLinkedList* dll = create_dll();
    
    insert_at_tail(dll, 10);
    insert_at_tail(dll, 20);
    insert_at_tail(dll, 30);
    insert_at_tail(dll, 40);
    
    assert(search(dll, 10) == 0);
    assert(search(dll, 30) == 2);
    assert(search(dll, 40) == 3);
    assert(search(dll, 99) == -1); // Not found
    
    free_dll(dll);
    printf("PASS\n");
}

/**
 * Test traversal functions
 */
void test_traversal() {
    printf("Test 4: Forward and backward traversal... ");
    
    DoublyLinkedList* dll = create_dll();
    
    insert_at_tail(dll, 10);
    insert_at_tail(dll, 20);
    insert_at_tail(dll, 30);
    
    // Manually check forward traversal
    Node* current = dll->head;
    assert(current->data == 10);
    current = current->next;
    assert(current->data == 20);
    current = current->next;
    assert(current->data == 30);
    assert(current->next == NULL);
    
    // Manually check backward traversal
    current = dll->tail;
    assert(current->data == 30);
    current = current->prev;
    assert(current->data == 20);
    current = current->prev;
    assert(current->data == 10);
    assert(current->prev == NULL);
    
    free_dll(dll);
    printf("PASS\n");
}

/**
 * Test reverse function
 */
void test_reverse() {
    printf("Test 5: Reverse list... ");
    
    DoublyLinkedList* dll = create_dll();
    
    insert_at_tail(dll, 10);
    insert_at_tail(dll, 20);
    insert_at_tail(dll, 30);
    
    reverse(dll);
    
    // Check reversed order
    assert(dll->head->data == 30);
    assert(dll->head->next->data == 20);
    assert(dll->tail->data == 10);
    
    // Reverse back
    reverse(dll);
    assert(dll->head->data == 10);
    assert(dll->tail->data == 30);
    
    free_dll(dll);
    printf("PASS\n");
}

/**
 * Test edge cases
 */
void test_edge_cases() {
    printf("Test 6: Edge cases... ");
    
    // Test empty list operations
    DoublyLinkedList* dll = create_dll();
    
    // Delete from empty list
    assert(delete_from_head(dll) == -1);
    assert(delete_from_tail(dll) == -1);
    assert(delete_by_value(dll, 10) == 0);
    assert(delete_at_position(dll, 0) == -1);
    
    // Search empty list
    assert(search(dll, 10) == -1);
    
    // Insert at invalid position
    assert(insert_at_position(dll, 10, -1) == 0);
    assert(insert_at_position(dll, 10, 1) == 0);
    
    // Single element list
    insert_at_head(dll, 5);
    assert(get_size(dll) == 1);
    assert(dll->head == dll->tail);
    
    // Delete single element
    assert(delete_from_head(dll) == 5);
    assert(is_empty(dll));
    
    free_dll(dll);
    printf("PASS\n");
}

/**
 * Test memory management
 */
void test_memory_management() {
    printf("Test 7: Memory management... ");
    
    // Create large list
    DoublyLinkedList* dll = create_dll();
    
    for (int i = 0; i < 100; i++) {
        insert_at_tail(dll, i);
    }
    assert(get_size(dll) == 100);
    
    // Delete half
    for (int i = 0; i < 50; i++) {
        delete_from_head(dll);
    }
    assert(get_size(dll) == 50);

  
    free_dll(dll);
    
    // Test NULL list
    insert_at_head(NULL, 10); 
    
    printf("PASS\n");
}

/**
 * Main test runner
 */
int main() {
    printf("\n=== TESTING DOUBLY LINKED LIST ===\n\n");
    
    test_creation_and_insert();
    test_deletion();
    test_search();
    test_traversal();
    test_reverse();
    test_edge_cases();
    test_memory_management();
    
    printf("\n=== ALL TESTS PASSED ===\n\n");
    
    printf("To run the main program:\n");
    printf("1. cd 5_DoublyLinkedList\n");
    printf("2. gcc -o dll dll.c\n");
    printf("3. ./dll\n");
    
    return 0;
}
