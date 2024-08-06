//
// Created by Brick on 7/3/2024.
//
#include <stdlib.h>
#ifndef OPERATINGSYSTEMS_VECTOR_H
#define OPERATINGSYSTEMS_VECTOR_H

typedef struct {
    char **data;
    int size;
    int capacity;
} Vector;

void initVector(Vector *vector, int capacity);
void addElement(Vector *vector, const char *element);
void printVector(Vector *vector);
void sortVector(Vector *vector);
int compareStrings(const void *a, const void *b);

#endif //OPERATINGSYSTEMS_VECTOR_H



