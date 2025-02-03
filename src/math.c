#include "math.h"

vector2_t vector_scalar_multiplication(vector2_t v, int scalar) {
    vector2_t res;
    res.x = v.x * scalar;
    res.y = v.y * scalar;
    return res;
}

vector2_t vector_add(vector2_t u, vector2_t v) {
    vector2_t res;
    res.x = u.x + v.x;
    res.y = u.y + v.y;
    return res;
}

vector2_t vector_substract(vector2_t u, vector2_t v) {
    vector2_t res;
    res.x = u.x - v.x;
    res.y = u.y - v.y;
    return res;
}

int vector_dot_product(vector2_t u, vector2_t v) {
    return u.x * v.x + u.y * v.y;
}