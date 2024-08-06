//
// Created by Brick on 7/3/2024.
//
#include <stdio.h>
#include "linkedList.h"

int main() {
    char name[100];
    double gpa;
    struct Node *head = NULL;

    fprintf(stderr, "Enter student names and GPAs. Press Ctrl+D to end input:\n");

    while (scanf("%s %lf", name, &gpa) != EOF) {
        insertAtEnd(&head, name, gpa);
    }

    printAboveGPA(head, 3.0);
    return 0;
}