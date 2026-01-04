/**
*student name [meseud hadis redi]
 *student id[2210205530]
 */

#ifndef CLL_H
#define CLL_H

#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Circular Linked List structure
typedef struct {
    Node* tail; // Maintain tail for O(1) insert at end
    int size;
} CircularLinkedList;

// Function declarations
CircularLinkedList* create_cll();
Node* create_node(int data);
int is_empty(CircularLinkedList* cll);
int get_size(CircularLinkedList* cll);
void insert_at_head(CircularLinkedList* cll, int data);
void insert_at_tail(CircularLinkedList* cll, int data);
int insert_at_position(CircularLinkedList* cll, int data, int position);
int delete_from_head(CircularLinkedList* cll);
int delete_from_tail(CircularLinkedList* cll);
int delete_by_value(CircularLinkedList* cll, int value);
int delete_at_position(CircularLinkedList* cll, int position);
int search(CircularLinkedList* cll, int value);
void traverse(CircularLinkedList* cll);
void traverse_multiple_cycles(CircularLinkedList* cll, int cycles);
Node* get_head(CircularLinkedList* cll);
Node* get_tail(CircularLinkedList* cll);
int josephus_problem(int n, int k);
void free_cll(CircularLinkedList* cll);

#endif
