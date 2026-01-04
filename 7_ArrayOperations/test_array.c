/**
*student name [meseud hadis redi]
 *student id[2210205530]
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Include the functions from array_ops.c
#include "array_ops.c"

/**
 * Test creation and basic insertion
 */
void test_creation_and_insert() {
    printf("Test 1: Creation and insertion... ");
    
    DynamicArray* arr = create_array();
    assert(arr != NULL);
    assert(arr->size == 0);
    assert(arr->capacity == INITIAL_CAPACITY);
    
    // Insert at end
    insert_at_end(arr, 10);
    assert(arr->size == 1);
    assert(arr->data[0] == 10);
    
    // Insert at beginning
    insert_at_beginning(arr, 5);
    assert(arr->size == 2);
    assert(arr->data[0] == 5);
    assert(arr->data[1] == 10);
    
    // Insert at position
    insert_at_position(arr, 7, 1);
    assert(arr->size == 3);
    assert(arr->data[0] == 5);
    assert(arr->data[1] == 7);
    assert(arr->data[2] == 10);
    
    free_array(arr);
    printf("PASS\n");
}

/**
 * Test deletion operations
 */
void test_deletion() {
    printf("Test 2: Deletion operations... ");
    
    DynamicArray* arr = create_array();
    
    // Add elements
    insert_at_end(arr, 10);
    insert_at_end(arr, 20);
    insert_at_end(arr, 30);
    insert_at_end(arr, 40);
    
    assert(arr->size == 4);
    
    // Delete from end
    int deleted = delete_from_end(arr);
    assert(deleted == 40);
    assert(arr->size == 3);
    
    // Delete from beginning
    deleted = delete_from_beginning(arr);
    assert(deleted == 10);
    assert(arr->size == 2);
    assert(arr->data[0] == 20);
    
    // Delete from position
    deleted = delete_from_position(arr, 0);
    assert(deleted == 20);
    assert(arr->size == 1);
    
    // Delete by value
    assert(delete_by_value(arr, 30) == 1);
    assert(arr->size == 0);
    
    free_array(arr);
    printf("PASS\n");
}

/**
 * Test search and update
 */
void test_search_and_update() {
    printf("Test 3: Search and update... ");
    
    DynamicArray* arr = create_array();
    
    insert_at_end(arr, 10);
    insert_at_end(arr, 20);
    insert_at_end(arr, 30);
    
    // Test search
    assert(search(arr, 20) == 1);
    assert(search(arr, 40) == -1);
    
    // Test get at position
    assert(get_at_position(arr, 1) == 20);
    
    // Test update
    int old_value = update_at_position(arr, 1, 25);
    assert(old_value == 20);
    assert(arr->data[1] == 25);
    
    free_array(arr);
    printf("PASS\n");
}

/**
 * Test reverse and sort
 */
void test_reverse_and_sort() {
    printf("Test 4: Reverse and sort... ");
    
    DynamicArray* arr = create_array();
    
    insert_at_end(arr, 30);
    insert_at_end(arr, 10);
    insert_at_end(arr, 20);
    
    // Test reverse
    reverse_array(arr);
    assert(arr->data[0] == 20);
    assert(arr->data[1] == 10);
    assert(arr->data[2] == 30);
    
    // Test sort
    sort_array(arr);
    assert(arr->data[0] == 10);
    assert(arr->data[1] == 20);
    assert(arr->data[2] == 30);
    
    free_array(arr);
    printf("PASS\n");
}

/**
 * Test remove duplicates
 */
void test_remove_duplicates() {
    printf("Test 5: Remove duplicates... ");
    
    DynamicArray* arr = create_array();
    
    insert_at_end(arr, 10);
    insert_at_end(arr, 20);
    insert_at_end(arr, 20);
    insert_at_end(arr, 30);
    insert_at_end(arr, 30);
    insert_at_end(arr, 30);
    
    remove_duplicates(arr);
    assert(arr->size == 3);
    assert(arr->data[0] == 10);
    assert(arr->data[1] == 20);
    assert(arr->data[2] == 30);
    
    free_array(arr);
    printf("PASS\n");
}

/**
 * Test rotation
 */
void test_rotation() {
    printf("Test 6: Rotation... ");
    
    DynamicArray* arr = create_array();
    
    for (int i = 1; i <= 5; i++) {
        insert_at_end(arr, i);
    }
    
    // Test left rotation
    rotate_left(arr, 2);
    assert(arr->data[0] == 3);
    assert(arr->data[1] == 4);
    assert(arr->data[2] == 5);
    assert(arr->data[3] == 1);
    assert(arr->data[4] == 2);
    
    // Test right rotation
    rotate_right(arr, 2);
    assert(arr->data[0] == 1);
    assert(arr->data[1] == 2);
    assert(arr->data[2] == 3);
    assert(arr->data[3] == 4);
    assert(arr->data[4] == 5);
    
    free_array(arr);
    printf("PASS\n");
}

/**
 * Test merge sorted arrays
 */
void test_merge_sorted_arrays() {
    printf("Test 7: Merge sorted arrays... ");
    
    DynamicArray* arr1 = create_array();
    insert_at_end(arr1, 1);
    insert_at_end(arr1, 3);
    insert_at_end(arr1, 5);
    
    DynamicArray* arr2 = create_array();
    insert_at_end(arr2, 2);
    insert_at_end(arr2, 4);
    insert_at_end(arr2, 6);
    
    DynamicArray* merged = merge_sorted_arrays(arr1, arr2);
    
    assert(merged->size == 6);
    for (int i = 0; i < 6; i++) {
        assert(merged->data[i] == i + 1);
    }
    
    free_array(arr1);
    free_array(arr2);
    free_array(merged);
    printf("PASS\n");
}

/**
 * Test dynamic resizing
 */
void test_dynamic_resizing() {
    printf("Test 8: Dynamic resizing... ");
    
    DynamicArray* arr = create_array();
    
    // Add more elements than initial capacity
    for (int i = 0; i < 20; i++) {
        insert_at_end(arr, i);
    }
    
    assert(arr->size == 20);
    assert(arr->capacity >= 20); // Should resize
    
    for (int i = 0; i < 20; i++) {
        assert(arr->data[i] == i);
    }
    
    free_array(arr);
    printf("PASS\n");
}

/**
 * Test edge cases
 */
void test_edge_cases() {
    printf("Test 9: Edge cases... ");
    
    // Test NULL array
    insert_at_end(NULL, 10);
    
    // Test empty array operations
    DynamicArray* arr = create_array();
    
    assert(delete_from_end(arr) == -1);
    assert(delete_from_beginning(arr) == -1);
    assert(delete_from_position(arr, 0) == -1);
    assert(delete_by_value(arr, 10) == 0);
    assert(search(arr, 10) == -1);
    
    // Test invalid positions
    assert(insert_at_position(arr, 10, -1) == 0);
    assert(insert_at_position(arr, 10, 1) == 0);
    assert(get_at_position(arr, 0) == -1);
    assert(update_at_position(arr, 0, 10) == 0);
    
    // Single element array
    insert_at_end(arr, 5);
    assert(delete_from_end(arr) == 5);
    assert(arr->size == 0);
    
    free_array(arr);
    printf("PASS\n");
}

/**
 * Main test runner
 */
int main() {
    printf("\n=== TESTING ARRAY OPERATIONS ===\n\n");
    
    test_creation_and_insert();
    test_deletion();
    test_search_and_update();
    test_reverse_and_sort();
    test_remove_duplicates();
    test_rotation();
    test_merge_sorted_arrays();
    test_dynamic_resizing();
    test_edge_cases();
    
    printf("\n=== ALL TESTS PASSED ===\n\n");
    
    printf("To run the main program:\n");
    printf("1. cd 7_ArrayOperations\n");
    printf("2. gcc -o array_ops array_ops.c\n");
    printf("3. ./array_ops\n");
    
    return 0;
}
