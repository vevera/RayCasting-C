#ifndef VECTOR4D_H
#define VECTOR4D_H

#include "vector3d.h"

#ifndef VECTOR_TYPE
#define VECTOR_TYPE double
#endif

#define FOUR_DIM 4

#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct vector4d {
    VECTOR_TYPE a;
    VECTOR_TYPE b;
    VECTOR_TYPE c;
    VECTOR_TYPE d;
} vector4d;

#ifndef VECTOR_AT
#define VECTOR_AT(vec, where) ((VECTOR_TYPE *)(vec))[(where)]
#endif

#ifdef VECTOR3D_MAX
#ifndef VECTOR4D_MAX
#define VECTOR4D_MAX(vec) VECTOR3D_MAX(vec) > (vec).d? VECTOR3D_MAX(vec) : (vec).d
#endif
#endif

//Vector 4d 
vector4d vector4d_create_empty();
vector4d vector4d_create(VECTOR_TYPE a, VECTOR_TYPE b, VECTOR_TYPE c, VECTOR_TYPE d);
void vector4d_set(vector4d* vec, VECTOR_TYPE elements[4]);
void vector4d_reset(vector4d* vector4d);
void vector4d_print(vector4d* vector);
void vector4d_add(vector4d* dest, vector4d* source1, vector4d* source2);
void vector4d_sub(vector4d* dest, vector4d* source1, vector4d* source2);
void vector4d_mul(vector4d* dest, vector4d* source1, vector4d* source2);
void vector4d_scale(vector4d* dest, vector4d* source1, double source2);
void vector4d_div(vector4d* dest, vector4d* source1, vector4d* source2);
void vector4d_normalize(vector4d* dest, vector4d* source);
double vector4d_lenght(vector4d* source1);
VECTOR_TYPE vector4d_dot(vector4d* source1, vector4d* source2);

//Vector 4d 
vector4d vector4d_create_empty() {
    return vector4d_create(0, 0, 0, 0);
}

vector4d vector4d_create(VECTOR_TYPE a, VECTOR_TYPE b, VECTOR_TYPE c, VECTOR_TYPE d) {
    vector4d vector = {
        .a = a,
        .b = b, 
        .c = c,
        .d = d
    };
    return vector;
}

void vector4d_set(vector4d* vec, VECTOR_TYPE elements[4]) {
    memcpy(vec, elements, sizeof(VECTOR_TYPE) * FOUR_DIM);
}

void vector4d_reset(vector4d* vector){
    memset(vector, 0, sizeof(VECTOR_TYPE) * FOUR_DIM);
}

void vector4d_print(vector4d* vector) {
    printf("(%f, %f, %f, %f)\n", VECTOR_AT(vector, 0), 
            VECTOR_AT(vector, 1),VECTOR_AT(vector, 2), VECTOR_AT(vector, 3));
}

void vector4d_add(vector4d* dest, vector4d* source1, vector4d* source2){
    dest->a = source1->a + source2->a;
    dest->b = source1->b + source2->b;
    dest->c = source1->c + source2->c;
    dest->d = source1->d + source2->d;
}
void vector4d_sub(vector4d* dest, vector4d* source1, vector4d* source2){
    dest->a = source1->a - source2->a;
    dest->b = source1->b - source2->b;
    dest->c = source1->c - source2->c;
    dest->d = source1->d - source2->d;
}
void vector4d_mul(vector4d* dest, vector4d* source1, vector4d* source2){
    dest->a = source1->a * source2->a;
    dest->b = source1->b * source2->b;
    dest->c = source1->c * source2->c;
    dest->d = source1->d * source2->d;
}
void vector4d_scale(vector4d* dest, vector4d* source1, double source2){
    dest->a = source1->a * source2;
    dest->b = source1->b * source2;
    dest->c = source1->c * source2;
    dest->d = source1->d * source2;
}
void vector4d_div(vector4d* dest, vector4d* source1, vector4d* source2){
    dest->a = source1->a / source2->a;
    dest->b = source1->b / source2->b;
    dest->c = source1->c / source2->c;
    dest->d = source1->d / source2->d;
}
void vector4d_normalize(vector4d* dest, vector4d* source){
    vector4d_scale(dest, source, 1/vector4d_lenght(source));
}

double vector4d_lenght(vector4d* source1){
    VECTOR_TYPE dot_prod = vector4d_dot(source1, source1);
    return sqrt(dot_prod);
}

VECTOR_TYPE vector4d_dot(vector4d* source1, vector4d* source2){
    return (source1->a * source2->a) + (source1->b * source2->b) + (source1->c * source2->c) + (source1->d * source2->d);
}

#endif