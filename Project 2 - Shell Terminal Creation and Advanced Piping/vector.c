//
// Created by Brick on 7/3/2024.
//
// vector.c
// vector.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

//initialize vector
void initVector(Vector *vector, int capacity) {
    vector->data = (char **)malloc(capacity * sizeof(char *));
    if (vector->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    vector->size = 0;
    vector->capacity = capacity;
}

//add element to vector
void addElement(Vector *vector, const char *element) {
    if (vector->size == vector->capacity) {
        vector->capacity *= 2;
        vector->data = (char **)realloc(vector->data, vector->capacity * sizeof(char *));
        if (vector->data == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(1);
        }
    }
    vector->data[vector->size] = (char *)malloc(strlen(element) + 1);
    if (vector->data[vector->size] == NULL) {
        fprintf(stderr, "Memory allocation for string failed\n");
        exit(1);
    }
    strcpy(vector->data[vector->size], element);
    vector->size++;
}

//Compare function uses by qsort
int compareStrings(const void *a, const void *b) {
    const char *strA = *(const char **)a;
    const char *strB = *(const char **)b;
    return strcmp(strA, strB);
}

//Sorting function using built in qsort with compareStrings
void sortVector(Vector *vector) {
    qsort(vector->data, vector->size, sizeof(char *), compareStrings);
}

//prints all elements of vector
void printVector(Vector *vector) {
    printf("Sorted Names: \n");
    for (int i = 0; i < vector->size; i++) {
        printf("%s\n", vector->data[i]);
    }
}

