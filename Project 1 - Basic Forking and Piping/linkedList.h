//
// Created by Brick on 7/3/2024.
//

#ifndef OPERATINGSYSTEMS_LINKEDLIST_H
#define OPERATINGSYSTEMS_LINKEDLIST_H

struct Node {
    char *name;
    double gpa;
    struct Node* next;
};

void insertAtEnd(struct Node** head, const char* name, double gpa);
void printAboveGPA(struct Node* node, double target_gpa);

#endif //OPERATINGSYSTEMS_LINKEDLIST_H