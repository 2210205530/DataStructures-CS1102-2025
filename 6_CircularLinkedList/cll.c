/**
 *student name [meseud hadis redi]
 *student id[2210205530]
 * Time Complexity:
 *   - Insert at head/tail: O(1)
 *   - Insert at position: O(n)
 *   - Delete: O(n) worst case
 *   - Search: O(n)
 * Space Complexity: O(n)
 */

#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Circular Linked List structure
typedef struct {
    Node* tail; 
    int size;
} CircularLinkedList;

/**
 * Create a new node
 */
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

/**
 * Create an empty circular linked list
 */
CircularLinkedList* create_cll() {
    CircularLinkedList* cll = (CircularLinkedList*)malloc(sizeof(CircularLinkedList));
    if (!cll) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    cll->tail = NULL;
    cll->size = 0;
    return cll;
}

/**
 * Check if list is empty
 */
int is_empty(CircularLinkedList* cll) {
    return cll == NULL || cll->size == 0;
}

/**
 * Get list size
 */
int get_size(CircularLinkedList* cll) {
    return cll ? cll->size : 0;
}

/**
 * Insert at the beginning (head)
 */
void insert_at_head(CircularLinkedList* cll, int data) {
    if (!cll) {
        printf("Error: List is NULL\n");
        return;
    }
    
    Node* new_node = create_node(data);
    if (!new_node) return;
    
    if (is_empty(cll)) {
        // First node - points to itself
        new_node->next = new_node;
        cll->tail = new_node;
    } else {
        // Insert after tail (which is before head in circular list)
        new_node->next = cll->tail->next;
        cll->tail->next = new_node;
    }
    cll->size++;
}

/**
 * Insert at the end (tail)
 */
void insert_at_tail(CircularLinkedList* cll, int data) {
    if (!cll) {
        printf("Error: List is NULL\n");
        return;
    }
    
    Node* new_node = create_node(data);
    if (!new_node) return;
    
    if (is_empty(cll)) {
        new_node->next = new_node;
        cll->tail = new_node;
    } else {
        new_node->next = cll->tail->next; // Point to head
        cll->tail->next = new_node;       // Old tail points to new node
        cll->tail = new_node;              // Update tail
    }
    cll->size++;
}

/**
 * Insert at specific position (0-based index)
 */
int insert_at_position(CircularLinkedList* cll, int data, int position) {
    if (!cll) {
        printf("Error: List is NULL\n");
        return 0;
    }
    
    if (position < 0 || position > cll->size) {
        printf("Error: Position out of bounds\n");
        return 0;
    }
    
    // Special cases
    if (position == 0) {
        insert_at_head(cll, data);
        return 1;
    }
    if (position == cll->size) {
        insert_at_tail(cll, data);
        return 1;
    }
    
    Node* new_node = create_node(data);
    if (!new_node) return 0;
    
    // Find the node before insertion point
    Node* current = cll->tail->next; // Start from head
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    // Insert after current
    new_node->next = current->next;
    current->next = new_node;
    cll->size++;
    
    return 1;
}

/**
 * Delete from head
 */
int delete_from_head(CircularLinkedList* cll) {
    if (is_empty(cll)) {
        printf("Error: List is empty\n");
        return -1;
    }
    
    Node* head = cll->tail->next;
    int data = head->data;
    
    if (cll->size == 1) {
        // Only one node
        free(head);
        cll->tail = NULL;
    } else {
        // Multiple nodes
        cll->tail->next = head->next;
        free(head);
    }
    
    cll->size--;
    return data;
}

/**
 * Delete from tail
 */
int delete_from_tail(CircularLinkedList* cll) {
    if (is_empty(cll)) {
        printf("Error: List is empty\n");
        return -1;
    }
    
    if (cll->size == 1) {
        return delete_from_head(cll);
    }
    
    // Find the node before tail
    Node* current = cll->tail->next; // Start from head
    while (current->next != cll->tail) {
        current = current->next;
    }
    
    int data = cll->tail->data;
    current->next = cll->tail->next; // Point to head
    free(cll->tail);
    cll->tail = current;
    cll->size--;
    
    return data;
}

/**
 * Delete by value (first occurrence)
 */
int delete_by_value(CircularLinkedList* cll, int value) {
    if (is_empty(cll)) {
        printf("Error: List is empty\n");
        return 0;
    }
    
    // Special case: delete head
    if (cll->tail->next->data == value) {
        delete_from_head(cll);
        return 1;
    }
    
    // Special case: delete tail
    if (cll->tail->data == value) {
        delete_from_tail(cll);
        return 1;
    }
    
    // Search for node to delete
    Node* current = cll->tail->next; // Head
    Node* prev = cll->tail;          // Previous starts at tail
    
    do {
        if (current->data == value) {
            prev->next = current->next;
            free(current);
            cll->size--;
            return 1;
        }
        prev = current;
        current = current->next;
    } while (current != cll->tail->next); // Until back to head
    
    printf("Error: Value %d not found\n", value);
    return 0;
}

/**
 * Delete at specific position
 */
int delete_at_position(CircularLinkedList* cll, int position) {
    if (is_empty(cll)) {
        printf("Error: List is empty\n");
        return -1;
    }
    
    if (position < 0 || position >= cll->size) {
        printf("Error: Position out of bounds\n");
        return -1;
    }
    
    // Special cases
    if (position == 0) {
        return delete_from_head(cll);
    }
    if (position == cll->size - 1) {
        return delete_from_tail(cll);
    }
    
    // Find the node before position
    Node* current = cll->tail->next; // Head
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    Node* to_delete = current->next;
    int data = to_delete->data;
    
    current->next = to_delete->next;
    free(to_delete);
    cll->size--;
    
    return data;
}

/**
 * Search for a value
 */
int search(CircularLinkedList* cll, int value) {
    if (is_empty(cll)) {
        return -1;
    }
    
    Node* current = cll->tail->next; // Start from head
    int position = 0;
    
    do {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        position++;
    } while (current != cll->tail->next); // Until back to head
    
    return -1;
}

/**
 * Traverse the list (print all elements)
 */
void traverse(CircularLinkedList* cll) {
    if (is_empty(cll)) {
        printf("List is empty\n");
        return;
    }
    
    printf("Circular List (%d elements): ", cll->size);
    
    Node* current = cll->tail->next; // Start from head
    
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != cll->tail->next); // Until back to head
    
    printf("\n");
}

/**
 * Traverse multiple cycles (for visualization)
 */
void traverse_multiple_cycles(CircularLinkedList* cll, int cycles) {
    if (is_empty(cll)) {
        printf("List is empty\n");
        return;
    }
    
    printf("Traversing %d cycles: ", cycles);
    
    Node* current = cll->tail->next; // Start from head
    int count = 0;
    int total_elements = cycles * cll->size;
    
    while (count < total_elements) {
        printf("%d ", current->data);
        current = current->next;
        count++;
    }
    printf("...\n");
}

/**
 * Get head node
 */
Node* get_head(CircularLinkedList* cll) {
    return is_empty(cll) ? NULL : cll->tail->next;
}

/**
 * Get tail node
 */
Node* get_tail(CircularLinkedList* cll) {
    return cll->tail;
}

int josephus_problem(int n, int k) {
    if (n <= 0 || k <= 0) {
        printf("Error: Invalid parameters\n");
        return -1;
    }
    
    // Create list with people 1 to n
    CircularLinkedList* cll = create_cll();
    for (int i = 1; i <= n; i++) {
        insert_at_tail(cll, i);
    }
    
    printf("Josephus Problem: n=%d, k=%d\n", n, k);
    printf("Elimination order: ");
    
    Node* current = get_head(cll);
    Node* prev = get_tail(cll); // Start with prev at tail
    
    while (cll->size > 1) {
        // Move k-1 steps
        for (int i = 0; i < k - 1; i++) {
            prev = current;
            current = current->next;
        }
        
        // Eliminate current node
        printf("%d ", current->data);
        
        // Remove current node
        prev->next = current->next;
        
        if (current == cll->tail) {
            cll->tail = prev;
        }
        
        Node* to_delete = current;
        current = current->next;
        free(to_delete);
        cll->size--;
    }
    
    int survivor = current->data;
    printf("\nSurvivor: %d\n", survivor);
    
    free(current);
    free(cll);
    
    return survivor;
}

/**
 * Free all memory
 */
void free_cll(CircularLinkedList* cll) {
    if (!cll || is_empty(cll)) {
        if (cll) free(cll);
        return;
    }
    
    // Store head before breaking circle
    Node* head = cll->tail->next;
    
    // Break the circle
    cll->tail->next = NULL;
    
    // Free all nodes starting from head
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    
    free(cll);
}

/**
 * Main function to demonstrate CLL operations
 */
int main() {
    printf("=== CIRCULAR LINKED LIST IMPLEMENTATION ===\n\n");
    
    // Create list
    CircularLinkedList* cll = create_cll();
    
    printf("Test 1: Basic insertions\n");
    printf("-------------------------\n");
    
    insert_at_head(cll, 10);
    insert_at_head(cll, 20);
    insert_at_tail(cll, 30);
    insert_at_tail(cll, 40);
    
    traverse(cll);
    printf("Size: %d\n\n", get_size(cll));
    
    printf("Test 2: Insert at position\n");
    printf("--------------------------\n");
    
    printf("Insert 50 at position 2: ");
    insert_at_position(cll, 50, 2);
    traverse(cll);
    
    printf("Insert 60 at position 0 (head): ");
    insert_at_position(cll, 60, 0);
    traverse(cll);
    
    printf("Insert 70 at position %d (tail): ", get_size(cll));
    insert_at_position(cll, 70, get_size(cll));
    traverse(cll);
    printf("\n");
    
    printf("Test 3: Delete operations\n");
    printf("-------------------------\n");
    
    printf("Delete from head: %d\n", delete_from_head(cll));
    traverse(cll);
    
    printf("Delete from tail: %d\n", delete_from_tail(cll));
    traverse(cll);
    
    printf("Delete value 50: %s\n", 
           delete_by_value(cll, 50) ? "Success" : "Failed");
    traverse(cll);
    
    printf("Delete at position 1: %d\n", delete_at_position(cll, 1));
    traverse(cll);
    printf("\n");
    
    printf("Test 4: Search and traversal\n");
    printf("----------------------------\n");
    
    printf("Search for 30: Position %d\n", search(cll, 30));
    printf("Search for 100: Position %d (not found)\n", search(cll, 100));
    
    printf("\nTraverse 2 cycles to show circular nature:\n");
    traverse_multiple_cycles(cll, 2);
    printf("\n");
    
    printf("Test 5: Josephus Problem\n");
    printf("------------------------\n");
    
    // Simple Josephus problem example
    josephus_problem(7, 3);
    printf("\n");
    
    printf("Test 6: Edge cases\n");
    printf("------------------\n");
    
    // Create empty list
    CircularLinkedList* empty_cll = create_cll();
    printf("Empty list size: %d\n", get_size(empty_cll));
    traverse(empty_cll);
    
    // Single element list
    insert_at_head(empty_cll, 99);
    printf("Single element list: ");
    traverse(empty_cll);
    printf("Head == Tail: %s\n", 
           get_head(empty_cll) == get_tail(empty_cll) ? "Yes" : "No");
    
    // Clean up
    free_cll(cll);
    free_cll(empty_cll);
    
    printf("\n=== PROGRAM COMPLETED ===\n");
    
    return 0;
}
