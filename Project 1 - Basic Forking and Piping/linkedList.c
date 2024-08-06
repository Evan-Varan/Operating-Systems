// linkedlist.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Singly Linked List with a double and string per node
struct Node {
    char *name;
    double gpa;
    struct Node* next;
};

// Insert node at end
void insertAtEnd(struct Node** head, const char* name, double gpa) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->name = (char*)malloc(strlen(name) + 1);
    strcpy(newNode->name, name);
    newNode->gpa = gpa;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* last = *head;
    while (last->next != NULL) {
        last = last->next;
    }

    last->next = newNode;
}

// Print all nodes above a gpa
void printAboveGPA(struct Node* node, double target_gpa) {
    while (node != NULL) {
        if (node->gpa >= target_gpa) {
            printf("%s\n", node->name);
        }
        node = node->next;
    }
}