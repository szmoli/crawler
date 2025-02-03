#ifndef MATH_H
#define MATH_H

typedef struct {
    int x;
    int y;
} vector2_t;

vector2_t vector_scalar_multiplication(vector2_t v, int scalar);
vector2_t vector_add(vector2_t u, vector2_t v);
int vector_dot_product(vector2_t u, vector2_t v);

#endif