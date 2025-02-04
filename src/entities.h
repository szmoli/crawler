#ifndef ENTITIES_H
#define ENTITIES_H

#define MAX_ENTITIES 20

#include "math.h"

typedef struct {
    vector2_t positions[MAX_ENTITIES];
    int healths[MAX_ENTITIES];
    int types[MAX_ENTITIES];
} entities_t;

#endif