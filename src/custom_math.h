#ifndef CUSTOM_MATH_H
#define CUSTOM_MATH_H

#include <stdbool.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} vector2_t;

// Function declarations
vector2_t vector_scalar_multiplication(vector2_t v, int scalar);
vector2_t vector_add(vector2_t u, vector2_t v);
vector2_t vector_substract(vector2_t u, vector2_t v);
int vector_dot_product(vector2_t u, vector2_t v);
bool are_vectors_equal(vector2_t u, vector2_t v);
int max_int(int a, int b);
int min_int(int a, int b);
int abs_int(int a);
int vector_distance(vector2_t u, vector2_t v);

#endif