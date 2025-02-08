#include "custom_math.h"

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

bool are_vectors_equal(vector2_t u, vector2_t v) {
    return u.x == v.x && u.y == v.y;
}

int max_int(int a, int b) {
    if (a < b) {
        return b;
    }
    else {
        return a;
    }
}

int min_int(int a, int b) {
    if (a > b) {
        return b;
    }
    else {
        return a;
    }
}

int abs_int(int a) {
    if (a < 0) {
        return -a;
    }
    else {
        return a;
    }
}

int vector_distance(vector2_t u, vector2_t v) {
    int dist_x = u.x - v.x;
    int dist_y = u.y - v.y;
    int pow_dist_x = dist_x * dist_x;
    int pow_dist_y = dist_y * dist_y;
    int add_res = pow_dist_x + pow_dist_y;
    return (int) sqrt((double) add_res);
}