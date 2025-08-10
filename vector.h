#ifndef VECTOR_H
#define VECTOR_H
#include <stddef.h>

typedef void* Type;
typedef struct {
    Type *data;
    size_t size;
    size_t capacity;
} Vector;

extern void initializeVector(Vector*);
extern int isEmpty(Vector*);
extern int size(Vector*);
extern int capacity(Vector*);
extern void push_back(Vector*, Type);
extern void freeVector(Vector*);
extern void erase(Vector*, size_t);

#endif