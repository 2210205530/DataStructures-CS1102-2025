/**
 *student name [meseud hadis redi]
 * student id[2210205530]
 * Time Complexity:
 *   - Insert: O(log n)
 *   - Delete: O(log n)  
 *   - Build Heap: O(n)
 * Space Complexity: O(n)
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_HEAP_SIZE 100

// Heap structure
typedef struct {
    int data[MAX_HEAP_SIZE];
    int size;
    int is_min_heap; // 1 for min-heap, 0 for max-heap
} Heap;

/**
 * Create a new heap
 * is_min_heap 1 for min-heap, 0 for max-heap
 * return Pointer to new heap
 */
Heap* create_heap(int is_min_heap) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    if (!heap) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    
    heap->size = 0;
    heap->is_min_heap = is_min_heap;
    return heap;
}

/**
 * Get parent index
 */
int parent(int i) {
    return (i - 1) / 2;
}

/**
 * Get left child index
 */
int left_child(int i) {
    return 2 * i + 1;
}

/**
 * Get right child index  
 */
int right_child(int i) {
    return 2 * i + 2;
}

/**
 * Swap two elements in heap
 */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Compare two elements based on heap type
 * return 1 if a should be above b in the heap
 */
int compare(Heap* heap, int a, int b) {
    if (heap->is_min_heap) {
        return a < b; // For min-heap: parent < child
    } else {
        return a > b; // For max-heap: parent > child
    }
}

/**
 * Heapify up (used after insertion)
 */
void heapify_up(Heap* heap, int index) {
    while (index > 0 && 
           compare(heap, heap->data[index], heap->data[parent(index)])) {
        swap(&heap->data[index], &heap->data[parent(index)]);
        index = parent(index);
    }
}

/**
 * Heapify down (used after deletion)
 */
void heapify_down(Heap* heap, int index) {
    int smallest_or_largest = index;
    int left = left_child(index);
    int right = right_child(index);
    
    // Check left child
    if (left < heap->size && 
        compare(heap, heap->data[left], heap->data[smallest_or_largest])) {
        smallest_or_largest = left;
    }
    
    // Check right child
    if (right < heap->size && 
        compare(heap, heap->data[right], heap->data[smallest_or_largest])) {
        smallest_or_largest = right;
    }
    
    // If current index is not correct, swap and continue
    if (smallest_or_largest != index) {
        swap(&heap->data[index], &heap->data[smallest_or_largest]);
        heapify_down(heap, smallest_or_largest);
    }
}

/**
 * Insert element into heap
 * return 1 if successful, 0 if heap is full
 */
int heap_insert(Heap* heap, int value) {
    if (heap->size >= MAX_HEAP_SIZE) {
        printf("Error: Heap is full\n");
        return 0;
    }
    
    // Insert at the end
    heap->data[heap->size] = value;
    heap->size++;
    
    // Fix heap property
    heapify_up(heap, heap->size - 1);
    
    return 1;
}

/**
 * Delete root element from heap
 * return Deleted element, INT_MIN/INT_MAX if heap is empty
 */
int heap_delete_root(Heap* heap) {
    if (heap->size <= 0) {
        printf("Error: Heap is empty\n");
        return heap->is_min_heap ? INT_MAX : INT_MIN;
    }
    
    if (heap->size == 1) {
        heap->size--;
        return heap->data[0];
    }
    
    // Store root value
    int root = heap->data[0];
    
    // Move last element to root
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    
    // Fix heap property
    heapify_down(heap, 0);
    
    return root;
}

/**
 * Get root element without deleting
 */
int heap_peek(Heap* heap) {
    if (heap->size <= 0) {
        printf("Error: Heap is empty\n");
        return heap->is_min_heap ? INT_MAX : INT_MIN;
    }
    return heap->data[0];
}

/**
 * Build heap from array
 */
Heap* build_heap(int arr[], int n, int is_min_heap) {
    Heap* heap = create_heap(is_min_heap);
    if (!heap) return NULL;
    
    // Copy array to heap
    for (int i = 0; i < n; i++) {
        heap->data[i] = arr[i];
    }
    heap->size = n;
    
    // Heapify from last non-leaf node
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify_down(heap, i);
    }
    
    return heap;
}

/**
 * Heap sort (ascending for min-heap, descending for max-heap)
 */
void heap_sort(int arr[], int n, int ascending) {
    // Build heap
    Heap* heap = build_heap(arr, n, ascending ? 1 : 0);
    if (!heap) return;
    
    // Extract elements one by one
    for (int i = 0; i < n; i++) {
        arr[i] = heap_delete_root(heap);
    }
    
    free(heap);
}

/**
 * Print heap as array
 */
void print_heap(Heap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty\n");
        return;
    }
    
    printf("Heap (%s): ", heap->is_min_heap ? "Min" : "Max");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

/**
 * Check if heap property is satisfied
 */
int is_valid_heap(Heap* heap) {
    for (int i = 0; i < heap->size; i++) {
        int left = left_child(i);
        int right = right_child(i);
        
        if (left < heap->size) {
            if (heap->is_min_heap && heap->data[i] > heap->data[left]) {
                return 0;
            }
            if (!heap->is_min_heap && heap->data[i] < heap->data[left]) {
                return 0;
            }
        }
        
        if (right < heap->size) {
            if (heap->is_min_heap && heap->data[i] > heap->data[right]) {
                return 0;
            }
            if (!heap->is_min_heap && heap->data[i] < heap->data[right]) {
                return 0;
            }
        }
    }
    return 1;
}

/**
 * Main function to demonstrate heap operations
 */
int main() {
    printf("=== MIN/MAX HEAP IMPLEMENTATION ===\n\n");
    
    // Test 1: Min-Heap
    printf("Test 1: Min-Heap Operations\n");
    printf("---------------------------\n");
    
    Heap* min_heap = create_heap(1); // 1 = min-heap
    
    printf("Inserting: 10, 20, 5, 30, 1\n");
    heap_insert(min_heap, 10);
    heap_insert(min_heap, 20);
    heap_insert(min_heap, 5);
    heap_insert(min_heap, 30);
    heap_insert(min_heap, 1);
    
    print_heap(min_heap);
    printf("Root (min): %d\n", heap_peek(min_heap));
    printf("Valid heap: %s\n\n", is_valid_heap(min_heap) ? "Yes" : "No");
    
    printf("Deleting root...\n");
    int deleted = heap_delete_root(min_heap);
    printf("Deleted: %d\n", deleted);
    print_heap(min_heap);
    printf("New root: %d\n\n", heap_peek(min_heap));
    
    // Test 2: Max-Heap
    printf("Test 2: Max-Heap Operations\n");
    printf("---------------------------\n");
    
    Heap* max_heap = create_heap(0); // 0 = max-heap
    
    printf("Inserting: 10, 20, 5, 30, 1\n");
    heap_insert(max_heap, 10);
    heap_insert(max_heap, 20);
    heap_insert(max_heap, 5);
    heap_insert(max_heap, 30);
    heap_insert(max_heap, 1);
    
    print_heap(max_heap);
    printf("Root (max): %d\n", heap_peek(max_heap));
    printf("Valid heap: %s\n\n", is_valid_heap(max_heap) ? "Yes" : "No");
    
    // Test 3: Build heap from array
    printf("Test 3: Build Heap from Array\n");
    printf("-----------------------------\n");
    
    int arr[] = {4, 10, 3, 5, 1};
    int n = 5;
    
    printf("Original array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    Heap* built_heap = build_heap(arr, n, 1); // Min-heap
    printf("Built as min-heap: ");
    print_heap(built_heap);
    free(built_heap);
    
    // Test 4: Heap Sort
    printf("Test 4: Heap Sort\n");
    printf("-----------------\n");
    
    int sort_arr[] = {12, 11, 13, 5, 6, 7};
    int sort_n = 6;
    
    printf("Original: ");
    for (int i = 0; i < sort_n; i++) printf("%d ", sort_arr[i]);
    
    // Ascending sort (using min-heap)
    heap_sort(sort_arr, sort_n, 1);
    printf("\nAscending: ");
    for (int i = 0; i < sort_n; i++) printf("%d ", sort_arr[i]);
    
    // Reset array
    int sort_arr2[] = {12, 11, 13, 5, 6, 7};
    
    // Descending sort (using max-heap)
    heap_sort(sort_arr2, sort_n, 0);
    printf("\nDescending: ");
    for (int i = 0; i < sort_n; i++) printf("%d ", sort_arr2[i]);
    printf("\n");
    
    // Clean up
    free(min_heap);
    free(max_heap);
    
    return 0;
}
