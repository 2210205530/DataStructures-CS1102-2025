/**
 *student name [meseud hadis redi]
 *student id[2210205530]
 * Time Complexity:
 *   - Insert at head/tail: O(1)
 *   - Insert at position: O(n)
 *   - Delete: O(1) if node known, O(n) to find
 *   - Search: O(n)
 * Space Complexity: O(n)
 */

#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Doubly Linked List structure
typedef struct {
    Node* head;
    Node* tail;
    int size;
} DoublyLinkedList;

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
    new_node->prev = NULL;
    return new_node;
}

/**
 * Create an empty doubly linked list
 */
DoublyLinkedList* create_dll() {
    DoublyLinkedList* dll = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    if (!dll) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    dll->head = NULL;
    dll->tail = NULL;
    dll->size = 0;
    return dll;
}

/**
 * Insert at the beginning (head)
 */
void insert_at_head(DoublyLinkedList* dll, int data) {
    if (!dll) {
        printf("Error: List is NULL\n");
        return;
    }
    
    Node* new_node = create_node(data);
    if (!new_node) return;
    
    if (dll->size == 0) {
        // First node
        dll->head = new_node;
        dll->tail = new_node;
    } else {
        new_node->next = dll->head;
        dll->head->prev = new_node;
        dll->head = new_node;
    }
    dll->size++;
}

/**
 * Insert at the end (tail)
 */
void insert_at_tail(DoublyLinkedList* dll, int data) {
    if (!dll) {
        printf("Error: List is NULL\n");
        return;
    }
    
    Node* new_node = create_node(data);
    if (!new_node) return;
    
    if (dll->size == 0) {
        dll->head = new_node;
        dll->tail = new_node;
    } else {
        new_node->prev = dll->tail;
        dll->tail->next = new_node;
        dll->tail = new_node;
    }
    dll->size++;
}

/**
 * Insert at specific position (0-based index)
 */
int insert_at_position(DoublyLinkedList* dll, int data, int position) {
    if (!dll) {
        printf("Error: List is NULL\n");
        return 0;
    }
    
    if (position < 0 || position > dll->size) {
        printf("Error: Position out of bounds\n");
        return 0;
    }
    
    // Special cases
    if (position == 0) {
        insert_at_head(dll, data);
        return 1;
    }
    if (position == dll->size) {
        insert_at_tail(dll, data);
        return 1;
    }
    
    Node* new_node = create_node(data);
    if (!new_node) return 0;
    
    // Find the node before insertion point
    Node* current;
    if (position <= dll->size / 2) {
        // Start from head if position is in first half
        current = dll->head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
    } else {
        // Start from tail if position is in second half
        current = dll->tail;
        for (int i = dll->size - 1; i > position; i--) {
            current = current->prev;
        }
        current = current->prev;
    }
    
    // Insert after current node
    new_node->next = current->next;
    new_node->prev = current;
    current->next->prev = new_node;
    current->next = new_node;
    
    dll->size++;
    return 1;
}

/**
 * Delete node from head
 */
int delete_from_head(DoublyLinkedList* dll) {
    if (!dll || dll->size == 0) {
        printf("Error: List is empty\n");
        return -1;
    }
    
    Node* to_delete = dll->head;
    int data = to_delete->data;
    
    if (dll->size == 1) {
        dll->head = NULL;
        dll->tail = NULL;
    } else {
        dll->head = dll->head->next;
        dll->head->prev = NULL;
    }
    
    free(to_delete);
    dll->size--;
    return data;
}

/**
 * Delete node from tail
 */
int delete_from_tail(DoublyLinkedList* dll) {
    if (!dll || dll->size == 0) {
        printf("Error: List is empty\n");
        return -1;
    }
    
    Node* to_delete = dll->tail;
    int data = to_delete->data;
    
    if (dll->size == 1) {
        dll->head = NULL;
        dll->tail = NULL;
    } else {
        dll->tail = dll->tail->prev;
        dll->tail->next = NULL;
    }
    
    free(to_delete);
    dll->size--;
    return data;
}

/**
 * Delete node with specific value (first occurrence)
 */
int delete_by_value(DoublyLinkedList* dll, int value) {
    if (!dll || dll->size == 0) {
        printf("Error: List is empty\n");
        return 0;
    }
    
    // Check head
    if (dll->head->data == value) {
        delete_from_head(dll);
        return 1;
    }
    
    // Check tail
    if (dll->tail->data == value) {
        delete_from_tail(dll);
        return 1;
    }
    
    // Search for node
    Node* current = dll->head;
    while (current != NULL && current->data != value) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Error: Value %d not found\n", value);
        return 0;
    }
    
    // Delete the node
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
    dll->size--;
    
    return 1;
}

/**
 * Delete node at specific position
 */
int delete_at_position(DoublyLinkedList* dll, int position) {
    if (!dll || dll->size == 0) {
        printf("Error: List is empty\n");
        return -1;
    }
    
    if (position < 0 || position >= dll->size) {
        printf("Error: Position out of bounds\n");
        return -1;
    }
    
    // Special cases
    if (position == 0) {
        return delete_from_head(dll);
    }
    if (position == dll->size - 1) {
        return delete_from_tail(dll);
    }
    
    // Find the node to delete
    Node* to_delete;
    if (position <= dll->size / 2) {
        to_delete = dll->head;
        for (int i = 0; i < position; i++) {
            to_delete = to_delete->next;
        }
    } else {
        to_delete = dll->tail;
        for (int i = dll->size - 1; i > position; i--) {
            to_delete = to_delete->prev;
        }
    }
    
    int data = to_delete->data;
    to_delete->prev->next = to_delete->next;
    to_delete->next->prev = to_delete->prev;
    free(to_delete);
    dll->size--;
    
    return data;
}

/**
 * Search for a value in the list
 * return Position (0-based) or -1 if not found
 */
int search(DoublyLinkedList* dll, int value) {
    if (!dll || dll->size == 0) {
        return -1;
    }
    
    Node* current = dll->head;
    int position = 0;
    
    while (current != NULL) {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        position++;
    }
    
    return -1;
}

/**
 * Traverse forward (head to tail)
 */
void traverse_forward(DoublyLinkedList* dll) {
    if (!dll || dll->size == 0) {
        printf("List is empty\n");
        return;
    }
    
    printf("Forward: ");
    Node* current = dll->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

/**
 * Traverse backward (tail to head)
 */
void traverse_backward(DoublyLinkedList* dll) {
    if (!dll || dll->size == 0) {
        printf("List is empty\n");
        return;
    }
    
    printf("Backward: ");
    Node* current = dll->tail;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}

/**
 * Get list size
 */
int get_size(DoublyLinkedList* dll) {
    return dll ? dll->size : 0;
}

/**
 * Check if list is empty
 */
int is_empty(DoublyLinkedList* dll) {
    return dll ? (dll->size == 0) : 1;
}

/**
 * Free all memory
 */
void free_dll(DoublyLinkedList* dll) {
    if (!dll) return;
    
    Node* current = dll->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    
    free(dll);
}

/**
 * Reverse the doubly linked list
 */
void reverse(DoublyLinkedList* dll) {
    if (!dll || dll->size <= 1) {
        return;
    }
    
    Node* current = dll->head;
    Node* temp = NULL;
    
    // Swap next and prev for all nodes
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    
    // Swap head and tail
    temp = dll->head;
    dll->head = dll->tail;
    dll->tail = temp;
}

/**
 * Main function to demonstrate DLL operations
 */
int main() {
    printf("=== DOUBLY LINKED LIST IMPLEMENTATION ===\n\n");
    
    // Create list
    DoublyLinkedList* dll = create_dll();
    
    printf("Test 1: Insert at head and tail\n");
    printf("--------------------------------\n");
    
    insert_at_head(dll, 10);
    insert_at_head(dll, 20);
    insert_at_tail(dll, 30);
    insert_at_tail(dll, 40);
    
    printf("After inserts:\n");
    traverse_forward(dll);
    traverse_backward(dll);
    printf("Size: %d\n\n", get_size(dll));
    
    printf("Test 2: Insert at position\n");
    printf("--------------------------\n");
    
    printf("Insert 50 at position 2 (0-based)\n");
    insert_at_position(dll, 50, 2);
    traverse_forward(dll);
    
    printf("Insert 60 at position 0 (head)\n");
    insert_at_position(dll, 60, 0);
    traverse_forward(dll);
    
    printf("Insert 70 at position %d (tail)\n", get_size(dll));
    insert_at_position(dll, 70, get_size(dll));
    traverse_forward(dll);
    printf("\n");
    
    printf("Test 3: Delete operations\n");
    printf("-------------------------\n");
    
    printf("Delete from head: %d\n", delete_from_head(dll));
    traverse_forward(dll);
    
    printf("Delete from tail: %d\n", delete_from_tail(dll));
    traverse_forward(dll);
    
    printf("Delete value 50: %s\n", 
           delete_by_value(dll, 50) ? "Success" : "Failed");
    traverse_forward(dll);
    
    printf("Delete at position 1: %d\n", delete_at_position(dll, 1));
    traverse_forward(dll);
    printf("\n");
    
    printf("Test 4: Search and reverse\n");
    printf("--------------------------\n");
    
    printf("Search for 30: Position %d\n", search(dll, 30));
    printf("Search for 100: Position %d (not found)\n", search(dll, 100));
    
    printf("\nBefore reverse:\n");
    traverse_forward(dll);
    
    reverse(dll);
    printf("After reverse:\n");
    traverse_forward(dll);
    traverse_backward(dll);
    printf("\n");
    
    printf("Test 5: Edge cases\n");
    printf("------------------\n");
    
    printf("Is empty? %s\n", is_empty(dll) ? "Yes" : "No");
    
    // Create empty list
    DoublyLinkedList* empty_dll = create_dll();
    printf("Empty list size: %d\n", get_size(empty_dll));
    traverse_forward(empty_dll);
    
    // Try delete from empty list
    printf("Delete from empty list returns: %d\n", delete_from_head(empty_dll));
    
    // Clean up
    free_dll(dll);
    free_dll(empty_dll);
    
    printf("\n=== PROGRAM COMPLETED ===\n");
    
    return 0;
}
