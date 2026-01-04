/**
 *student name [meseud hadis redi]
 *student id[2210205530]
 *Array insertion, deletion, and manipulation operations
 * Time Complexity:
 *   - Insert/delete at beginning: O(n)
 *   - Insert/delete at end: O(1) with capacity, O(n) with resize
 *   - Insert/delete at position: O(n)
 * Space Complexity: O(n)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2

// Dynamic Array structure
typedef struct {
    int* data;
    int size;
    int capacity;
} DynamicArray;

/**
 * Create a new dynamic array
 */
DynamicArray* create_array() {
    DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (!arr) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    
    arr->data = (int*)malloc(INITIAL_CAPACITY * sizeof(int));
    if (!arr->data) {
        free(arr);
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    
    arr->size = 0;
    arr->capacity = INITIAL_CAPACITY;
    return arr;
}

/**
 * Resize array if needed
 */
void resize_if_needed(DynamicArray* arr) {
    if (arr->size >= arr->capacity) {
        int new_capacity = arr->capacity * GROWTH_FACTOR;
        int* new_data = (int*)realloc(arr->data, new_capacity * sizeof(int));
        
        if (!new_data) {
            printf("Error: Memory reallocation failed\n");
            return;
        }
        
        arr->data = new_data;
        arr->capacity = new_capacity;
        printf("Array resized to capacity %d\n", new_capacity);
    }
}

/**
 * Insert at the end (append)
 */
void insert_at_end(DynamicArray* arr, int value) {
    if (!arr) {
        printf("Error: Array is NULL\n");
        return;
    }
    
    resize_if_needed(arr);
    arr->data[arr->size] = value;
    arr->size++;
}

/**
 * Insert at the beginning
 */
void insert_at_beginning(DynamicArray* arr, int value) {
    if (!arr) {
        printf("Error: Array is NULL\n");
        return;
    }
    
    resize_if_needed(arr);
    
    // Shift all elements to the right
    for (int i = arr->size; i > 0; i--) {
        arr->data[i] = arr->data[i - 1];
    }
    
    arr->data[0] = value;
    arr->size++;
}

/**
 * Insert at specific position (0-based index)
 */
int insert_at_position(DynamicArray* arr, int value, int position) {
    if (!arr) {
        printf("Error: Array is NULL\n");
        return 0;
    }
    
    if (position < 0 || position > arr->size) {
        printf("Error: Position %d out of bounds (size: %d)\n", position, arr->size);
        return 0;
    }
    
    // Special cases
    if (position == 0) {
        insert_at_beginning(arr, value);
        return 1;
    }
    if (position == arr->size) {
        insert_at_end(arr, value);
        return 1;
    }
    
    resize_if_needed(arr);
    
    // Shift elements from position to end
    for (int i = arr->size; i > position; i--) {
        arr->data[i] = arr->data[i - 1];
    }
    
    arr->data[position] = value;
    arr->size++;
    return 1;
}

/**
 * Delete from the end
 */
int delete_from_end(DynamicArray* arr) {
    if (!arr || arr->size == 0) {
        printf("Error: Array is empty\n");
        return -1;
    }
    
    int value = arr->data[arr->size - 1];
    arr->size--;
    return value;
}

/**
 * Delete from the beginning
 */
int delete_from_beginning(DynamicArray* arr) {
    if (!arr || arr->size == 0) {
        printf("Error: Array is empty\n");
        return -1;
    }
    
    int value = arr->data[0];
    
    // Shift all elements to the left
    for (int i = 0; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    
    arr->size--;
    return value;
}

/**
 * Delete from specific position
 */
int delete_from_position(DynamicArray* arr, int position) {
    if (!arr || arr->size == 0) {
        printf("Error: Array is empty\n");
        return -1;
    }
    
    if (position < 0 || position >= arr->size) {
        printf("Error: Position %d out of bounds (size: %d)\n", position, arr->size);
        return -1;
    }
    
    // Special cases
    if (position == 0) {
        return delete_from_beginning(arr);
    }
    if (position == arr->size - 1) {
        return delete_from_end(arr);
    }
    
    int value = arr->data[position];
    
    // Shift elements to fill the gap
    for (int i = position; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    
    arr->size--;
    return value;
}

/**
 * Delete first occurrence of value
 */
int delete_by_value(DynamicArray* arr, int value) {
    if (!arr || arr->size == 0) {
        printf("Error: Array is empty\n");
        return 0;
    }
    
    // Find the position
    int position = -1;
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i] == value) {
            position = i;
            break;
        }
    }
    
    if (position == -1) {
        printf("Error: Value %d not found\n", value);
        return 0;
    }
    
    delete_from_position(arr, position);
    return 1;
}

/**
 * Search for a value
 */
int search(DynamicArray* arr, int value) {
    if (!arr) return -1;
    
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i] == value) {
            return i;
        }
    }
    return -1;
}

/**
 * Get value at position
 */
int get_at_position(DynamicArray* arr, int position) {
    if (!arr || position < 0 || position >= arr->size) {
        printf("Error: Invalid position\n");
        return -1;
    }
    return arr->data[position];
}

/**
 * Update value at position
 */
int update_at_position(DynamicArray* arr, int position, int new_value) {
    if (!arr || position < 0 || position >= arr->size) {
        printf("Error: Invalid position\n");
        return 0;
    }
    
    int old_value = arr->data[position];
    arr->data[position] = new_value;
    return old_value;
}

/**
 * Reverse the array in-place
 */
void reverse_array(DynamicArray* arr) {
    if (!arr || arr->size <= 1) {
        return;
    }
    
    int start = 0;
    int end = arr->size - 1;
    
    while (start < end) {
        // Swap
        int temp = arr->data[start];
        arr->data[start] = arr->data[end];
        arr->data[end] = temp;
        
        start++;
        end--;
    }
}

/**
 * Sort array using bubble sort (simple demonstration)
 */
void sort_array(DynamicArray* arr) {
    if (!arr || arr->size <= 1) {
        return;
    }
    
    for (int i = 0; i < arr->size - 1; i++) {
        for (int j = 0; j < arr->size - i - 1; j++) {
            if (arr->data[j] > arr->data[j + 1]) {
                // Swap
                int temp = arr->data[j];
                arr->data[j] = arr->data[j + 1];
                arr->data[j + 1] = temp;
            }
        }
    }
}

/**
 * Remove duplicates from sorted array
 */
void remove_duplicates(DynamicArray* arr) {
    if (!arr || arr->size <= 1) {
        return;
    }
    
    // First, sort the array
    sort_array(arr);
    
    // Remove duplicates
    int new_size = 1;
    for (int i = 1; i < arr->size; i++) {
        if (arr->data[i] != arr->data[new_size - 1]) {
            arr->data[new_size] = arr->data[i];
            new_size++;
        }
    }
    
    arr->size = new_size;
}

/**
 * Rotate array left by k positions
 */
void rotate_left(DynamicArray* arr, int k) {
    if (!arr || arr->size <= 1 || k == 0) {
        return;
    }
    
    k = k % arr->size; // Handle k larger than size
    
    // Create temporary array for first k elements
    int* temp = (int*)malloc(k * sizeof(int));
    if (!temp) {
        printf("Error: Memory allocation failed\n");
        return;
    }
    
    // Store first k elements
    for (int i = 0; i < k; i++) {
        temp[i] = arr->data[i];
    }
    
    // Shift remaining elements left
    for (int i = 0; i < arr->size - k; i++) {
        arr->data[i] = arr->data[i + k];
    }
    
    // Copy temp elements to the end
    for (int i = 0; i < k; i++) {
        arr->data[arr->size - k + i] = temp[i];
    }
    
    free(temp);
}

/**
 * Rotate array right by k positions
 */
void rotate_right(DynamicArray* arr, int k) {
    if (!arr || arr->size <= 1 || k == 0) {
        return;
    }
    
    k = k % arr->size;
    
    // Create temporary array for last k elements
    int* temp = (int*)malloc(k * sizeof(int));
    if (!temp) {
        printf("Error: Memory allocation failed\n");
        return;
    }
    
    // Store last k elements
    for (int i = 0; i < k; i++) {
        temp[i] = arr->data[arr->size - k + i];
    }
    
    // Shift elements right
    for (int i = arr->size - 1; i >= k; i--) {
        arr->data[i] = arr->data[i - k];
    }
    
    // Copy temp elements to the beginning
    for (int i = 0; i < k; i++) {
        arr->data[i] = temp[i];
    }
    
    free(temp);
}

/**
 * Merge two sorted arrays
 */
DynamicArray* merge_sorted_arrays(DynamicArray* arr1, DynamicArray* arr2) {
    if (!arr1 && !arr2) return create_array();
    if (!arr1) return arr2;
    if (!arr2) return arr1;
    
    DynamicArray* result = create_array();
    
    int i = 0, j = 0;
    
    while (i < arr1->size && j < arr2->size) {
        if (arr1->data[i] <= arr2->data[j]) {
            insert_at_end(result, arr1->data[i]);
            i++;
        } else {
            insert_at_end(result, arr2->data[j]);
            j++;
        }
    }
    
    // Add remaining elements
    while (i < arr1->size) {
        insert_at_end(result, arr1->data[i]);
        i++;
    }
    
    while (j < arr2->size) {
        insert_at_end(result, arr2->data[j]);
        j++;
    }
    
    return result;
}

/**
 * Print array
 */
void print_array(DynamicArray* arr) {
    if (!arr) {
        printf("Array is NULL\n");
        return;
    }
    
    if (arr->size == 0) {
        printf("Array is empty\n");
        return;
    }
    
    printf("Array (size=%d, capacity=%d): ", arr->size, arr->capacity);
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}

/**
 * Get array size
 */
int get_size(DynamicArray* arr) {
    return arr ? arr->size : 0;
}

/**
 * Free array memory
 */
void free_array(DynamicArray* arr) {
    if (!arr) return;
    
    if (arr->data) {
        free(arr->data);
    }
    free(arr);
}

/**
 * Main function to demonstrate array operations
 */
int main() {
    printf("=== ARRAY OPERATIONS IMPLEMENTATION ===\n\n");
    
    // Create array
    DynamicArray* arr = create_array();
    
    printf("Test 1: Basic insertions\n");
    printf("-------------------------\n");
    
    insert_at_end(arr, 10);
    insert_at_end(arr, 20);
    insert_at_end(arr, 30);
    print_array(arr);
    
    insert_at_beginning(arr, 5);
    insert_at_beginning(arr, 1);
    print_array(arr);
    
    printf("\nTest 2: Insert at position\n");
    printf("--------------------------\n");
    
    printf("Insert 15 at position 2: ");
    insert_at_position(arr, 15, 2);
    print_array(arr);
    
    printf("Insert 25 at position 5: ");
    insert_at_position(arr, 25, 5);
    print_array(arr);
    
    printf("\nTest 3: Delete operations\n");
    printf("-------------------------\n");
    
    printf("Delete from end: %d\n", delete_from_end(arr));
    print_array(arr);
    
    printf("Delete from beginning: %d\n", delete_from_beginning(arr));
    print_array(arr);
    
    printf("Delete from position 2: %d\n", delete_from_position(arr, 2));
    print_array(arr);
    
    printf("Delete value 15: %s\n", delete_by_value(arr, 15) ? "Success" : "Failed");
    print_array(arr);
    
    printf("\nTest 4: Search and update\n");
    printf("-------------------------\n");
    
    printf("Search for 20: Position %d\n", search(arr, 20));
    printf("Search for 100: Position %d (not found)\n", search(arr, 100));
    
    printf("Update position 1 (was %d) to 99: ", update_at_position(arr, 1, 99));
    print_array(arr);
    
    printf("\nTest 5: Reverse and sort\n");
    printf("------------------------\n");
    
    printf("Original: ");
    print_array(arr);
    
    reverse_array(arr);
    printf("Reversed: ");
    print_array(arr);
    
    sort_array(arr);
    printf("Sorted:   ");
    print_array(arr);
    
    printf("\nTest 6: Remove duplicates\n");
    printf("-------------------------\n");
    
    // Add duplicates
    insert_at_end(arr, 20);
    insert_at_end(arr, 20);
    insert_at_end(arr, 30);
    insert_at_end(arr, 30);
    printf("With duplicates: ");
    print_array(arr);
    
    remove_duplicates(arr);
    printf("Without duplicates: ");
    print_array(arr);
    
    printf("\nTest 7: Rotation\n");
    printf("----------------\n");
    
    printf("Original: ");
    print_array(arr);
    
    rotate_left(arr, 2);
    printf("Rotated left by 2: ");
    print_array(arr);
    
    rotate_right(arr, 2);
    printf("Rotated right by 2: ");
    print_array(arr);
    
    printf("\nTest 8: Merge sorted arrays\n");
    printf("---------------------------\n");
    
    // Create two sorted arrays
    DynamicArray* arr1 = create_array();
    insert_at_end(arr1, 1);
    insert_at_end(arr1, 3);
    insert_at_end(arr1, 5);
    
    DynamicArray* arr2 = create_array();
    insert_at_end(arr2, 2);
    insert_at_end(arr2, 4);
    insert_at_end(arr2, 6);
    
    printf("Array 1: ");
    print_array(arr1);
    printf("Array 2: ");
    print_array(arr2);
    
    DynamicArray* merged = merge_sorted_arrays(arr1, arr2);
    printf("Merged:  ");
    print_array(merged);
    
    printf("\nTest 9: Dynamic resizing\n");
    printf("------------------------\n");
    
    printf("Adding 15 elements to test resizing:\n");
    DynamicArray* test_arr = create_array();
    for (int i = 0; i < 15; i++) {
        insert_at_end(test_arr, i * 10);
        printf("Added %d, size=%d, capacity=%d\n", i*10, test_arr->size, test_arr->capacity);
    }
    
    // Clean up
    free_array(arr);
    free_array(arr1);
    free_array(arr2);
    free_array(merged);
    free_array(test_arr);
    
    printf("\n=== PROGRAM COMPLETED ===\n");
    
    return 0;
}
