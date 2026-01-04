/**
 *student name [meseud hadis redi]
 *student id[2210205530]
 */
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

// Function declarations from heap.c
Heap* create_heap(int is_min_heap);
int heap_insert(Heap* heap, int value);
int heap_delete_root(Heap* heap);
int heap_peek(Heap* heap);
int is_valid_heap(Heap* heap);
Heap* build_heap(int arr[], int n, int is_min_heap);
void heap_sort(int arr[], int n, int ascending);

/**
 * Test min-heap basic operations
 */
void test_min_heap() {
    printf("Test 1: Min-Heap operations... ");
    
    Heap* heap = create_heap(1); // Min-heap
    
    // Insert elements
    heap_insert(heap, 5);
    heap_insert(heap, 3);
    heap_insert(heap, 8);
    heap_insert(heap, 1);
    heap_insert(heap, 10);
    
    // Check root should be 1
    if (heap_peek(heap) != 1) {
        printf("FAIL - Root should be 1, got %d\n", heap_peek(heap));
        free(heap);
        return;
    }
    
    // Check heap property
    if (!is_valid_heap(heap)) {
        printf("FAIL - Heap property violated\n");
        free(heap);
        return;
    }
    
    // Delete root and check
    int deleted = heap_delete_root(heap);
    if (deleted != 1) {
        printf("FAIL - Should delete 1, deleted %d\n", deleted);
        free(heap);
        return;
    }
    
    // New root should be 3
    if (heap_peek(heap) != 3) {
        printf("FAIL - New root should be 3, got %d\n", heap_peek(heap));
        free(heap);
        return;
    }
    
    free(heap);
    printf("PASS\n");
}

/**
 * Test max-heap basic operations
 */
void test_max_heap() {
    printf("Test 2: Max-Heap operations... ");
    
    Heap* heap = create_heap(0); // Max-heap
    
    heap_insert(heap, 5);
    heap_insert(heap, 3);
    heap_insert(heap, 8);
    heap_insert(heap, 1);
    heap_insert(heap, 10);
    
    // Root should be 10 (largest)
    if (heap_peek(heap) != 10) {
        printf("FAIL - Root should be 10, got %d\n", heap_peek(heap));
        free(heap);
        return;
    }
    
    if (!is_valid_heap(heap)) {
        printf("FAIL - Heap property violated\n");
        free(heap);
        return;
    }
    
    free(heap);
    printf("PASS\n");
}

/**
 * Test build_heap function
 */
void test_build_heap() {
    printf("Test 3: Build heap from array... ");
    
    int arr[] = {4, 10, 3, 5, 1, 7};
    int n = 6;
    
    // Build min-heap
    Heap* min_heap = build_heap(arr, n, 1);
    if (min_heap->data[0] != 1) { // Root should be 1
        printf("FAIL - Min-heap root should be 1, got %d\n", min_heap->data[0]);
        free(min_heap);
        return;
    }
    
    if (!is_valid_heap(min_heap)) {
        printf("FAIL - Min-heap property violated\n");
        free(min_heap);
        return;
    }
    
    free(min_heap);
    
    // Build max-heap
    Heap* max_heap = build_heap(arr, n, 0);
    if (max_heap->data[0] != 10) { // Root should be 10
        printf("FAIL - Max-heap root should be 10, got %d\n", max_heap->data[0]);
        free(max_heap);
        return;
    }
    
    if (!is_valid_heap(max_heap)) {
        printf("FAIL - Max-heap property violated\n");
        free(max_heap);
        return;
    }
    
    free(max_heap);
    printf("PASS\n");
}

/**
 * Test heap sort
 */
void test_heap_sort() {
    printf("Test 4: Heap sort... ");
    
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = 6;
    int sorted[] = {5, 6, 7, 11, 12, 13};
    
    // Test ascending sort (min-heap)
    int arr_copy[6];
    for (int i = 0; i < n; i++) arr_copy[i] = arr[i];
    
    heap_sort(arr_copy, n, 1); // Ascending
    
    for (int i = 0; i < n; i++) {
        if (arr_copy[i] != sorted[i]) {
            printf("FAIL - Ascending sort error at index %d\n", i);
            return;
        }
    }
    
    // Test descending sort (max-heap)
    int arr_copy2[6];
    for (int i = 0; i < n; i++) arr_copy2[i] = arr[i];
    
    heap_sort(arr_copy2, n, 0);
    
    // Check if descending (each element >= next)
    for (int i = 0; i < n - 1; i++) {
        if (arr_copy2[i] < arr_copy2[i + 1]) {
            printf("FAIL - Not properly descending at index %d\n", i);
            return;
        }
    }
    
    printf("PASS\n");
}

/**
 * Test edge cases
 */
void test_edge_cases() {
    printf("Test 5: Edge cases... ");
    
    // Test empty heap
    Heap* heap = create_heap(1);
    if (heap_peek(heap) != INT_MAX) { // Should return INT_MAX for empty min-heap
        printf("FAIL - Empty min-heap should return INT_MAX\n");
        free(heap);
        return;
    }
    
    // Test single element
    heap_insert(heap, 42);
    if (heap_peek(heap) != 42) {
        printf("FAIL - Single element heap peek error\n");
        free(heap);
        return;
    }
    
    if (!is_valid_heap(heap)) {
        printf("FAIL - Single element heap property\n");
        free(heap);
        return;
    }
    
    free(heap);
    printf("PASS\n");
}

/**
 * Main test runner
 */
int main() {
    printf("\n=== TESTING MIN/MAX HEAP IMPLEMENTATION ===\n\n");
    
    test_min_heap();
    test_max_heap();
    test_build_heap();
    test_heap_sort();
    test_edge_cases();
    
    printf("\n=== ALL TESTS COMPLETED ===\n\n");
    
    // Run the actual program
    printf("To run the main heap program:\n");
    printf("1. Compile: gcc -o heap_test heap.c\n");
    printf("2. Run: ./heap_test\n");
    
    return 0;
}
