//
// Created by Brick on 7/3/2024.
//
#include <stdio.h>
#include "vector.h"

int main(){
    char name[100];
    Vector vector;
    initVector(&vector, 4);

    fprintf(stderr, "Enter student names. Press Ctrl+D to end input:\n");

    while (scanf("%s", name) != EOF) {
        addElement(&vector, name);
    }

    sortVector(&vector);
    printVector(&vector);
}
