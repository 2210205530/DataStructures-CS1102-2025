/**
 *student name [meseud hadis redi]
 *student id[2210205530]
 */

#ifndef DLL_H
#define DLL_H

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

// Function declarations
DoublyLinkedList* create_dll();
Node* create_node(int data);
void insert_at_head(DoublyLinkedList* dll, int data);
void insert_at_tail(DoublyLinkedList* dll, int data);
int insert_at_position(DoublyLinkedList* dll, int data, int position);
int delete_from_head(DoublyLinkedList* dll);
int delete_from_tail(DoublyLinkedList* dll);
int delete_by_value(DoublyLinkedList* dll, int value);
int delete_at_position(DoublyLinkedList* dll, int position);
int search(DoublyLinkedList* dll, int value);
void traverse_forward(DoublyLinkedList* dll);
void traverse_backward(DoublyLinkedList* dll);
int get_size(DoublyLinkedList* dll);
int is_empty(DoublyLinkedList* dll);
void free_dll(DoublyLinkedList* dll);
void reverse(DoublyLinkedList* dll);

#endif
