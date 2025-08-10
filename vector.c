#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void initializeVector(Vector* v) {
    v->size = 0;
    v->capacity = 50; // Initial capacity
    v->data = malloc(v->capacity * sizeof(Type));
    if (!v->data) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
}

int size(Vector *v) {
    return (int)v->size;
}

int isEmpty(Vector *v) {
    return v->size == 0;
}

int capacity(Vector* v) {
    return (int)v->capacity;
}

void push_back(Vector* v, Type item) {
     if (v->size >= v->capacity) {
        v->capacity *= 2;
        v->data = realloc(v->data, v->capacity * sizeof(Type));
        if (!v->data) {
            fprintf(stderr, "Reallocation failed!\n");
            exit(1);
        }
    }
    v->data[v->size++] = item;
}

// Erase element at given index
void erase(Vector *v, size_t index) {
    if (index >= v->size) {
        fprintf(stderr, "Index out of bounds in vector_erase\n");
        return;
    }

    // Shift elements to the left
    for (size_t i = index; i < v->size - 1; ++i) {
        v->data[i] = v->data[i + 1];
    }

    v->size--; // Reduce size
}

void freeVector(Vector *v) {
    free(v->data);
    v->data = NULL;
    v->size = v->capacity = 0;
}