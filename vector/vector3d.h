#ifndef VECTOR3D_H
#define VECTOR3D_H

#ifndef VECTOR_TYPE
#define VECTOR_TYPE double
#endif

#define THREE_DIM 3

#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct vector3d {
    VECTOR_TYPE a;
    VECTOR_TYPE b;
    VECTOR_TYPE c;
} vector3d;

#ifndef VECTOR_AT
#define VECTOR_AT(vec, where) ((VECTOR_TYPE *)(vec))[(where)]
#endif

#define VECTOR3D_MAX(vec) (vec).a > (vec).b ? ((vec).a > (vec).c? (vec).a: (vec).c): ((vec).b > (vec).c? (vec).b: (vec).c)
//Vector 3d 
vector3d vector3d_create_empty();
vector3d vector3d_create(VECTOR_TYPE a, VECTOR_TYPE b, VECTOR_TYPE c);
void vector3d_set(vector3d* vec, VECTOR_TYPE elements[3]);
void vector3d_reset(vector3d* vector3d);
void vector3d_print(vector3d* vector);
void vector3d_add(vector3d* dest, vector3d* source1, vector3d* source2);
void vector3d_sub(vector3d* dest, vector3d* source1, vector3d* source2);
void vector3d_mul(vector3d* dest, vector3d* source1, vector3d* source2);
void vector3d_scale(vector3d* dest, vector3d* source1, double source2);
void vector3d_div(vector3d* dest, vector3d* source1, vector3d* source2);
void vector3d_normalize(vector3d* dest, vector3d* source);
void vector3d_crossproduct(vector3d* dest, vector3d* source1, vector3d* source2);
double vector3d_lenght(vector3d* source1);
VECTOR_TYPE vector3d_dot(vector3d* source1, vector3d* source2);

//Vector 3d 
vector3d vector3d_create_empty() {
    return vector3d_create(0, 0, 0);
}

vector3d vector3d_create(VECTOR_TYPE a, VECTOR_TYPE b, VECTOR_TYPE c) {
    vector3d vector = {
        .a = a,
        .b = b, 
        .c = c
    };
    return vector;
}

void vector3d_set(vector3d* vec, VECTOR_TYPE elements[3]) {
    memcpy(vec, elements, sizeof(VECTOR_TYPE) * THREE_DIM);
}

void vector3d_reset(vector3d* vector){
    memset(vector, 0, sizeof(VECTOR_TYPE) * THREE_DIM);
}

void vector3d_print(vector3d* vector) {
    printf("(%f, %f, %f)\n", VECTOR_AT(vector, 0), 
            VECTOR_AT(vector, 1),VECTOR_AT(vector, 2));
}

void vector3d_add(vector3d* dest, vector3d* source1, vector3d* source2){
    dest->a = source1->a + source2->a;
    dest->b = source1->b + source2->b;
    dest->c = source1->c + source2->c;
}
void vector3d_sub(vector3d* dest, vector3d* source1, vector3d* source2){
    dest->a = source1->a - source2->a;
    dest->b = source1->b - source2->b;
    dest->c = source1->c - source2->c;
}
void vector3d_mul(vector3d* dest, vector3d* source1, vector3d* source2){
    dest->a = source1->a * source2->a;
    dest->b = source1->b * source2->b;
    dest->c = source1->c * source2->c;
}
void vector3d_scale(vector3d* dest, vector3d* source1, double source2){
    dest->a = source1->a * source2;
    dest->b = source1->b * source2;
    dest->c = source1->c * source2;
}
void vector3d_div(vector3d* dest, vector3d* source1, vector3d* source2){
    dest->a = source1->a / source2->a;
    dest->b = source1->b / source2->b;
    dest->c = source1->c / source2->c;
}
void vector3d_normalize(vector3d* dest, vector3d* source){
    vector3d_scale(dest, source, 1/vector3d_lenght(source));
}

void vector3d_crossproduct(vector3d* dest, vector3d* source1, vector3d* source2){
    dest->a = (source1->b * source2->c) - (source1->c * source2->b); 
    dest->b = (source1->c * source2->a) - (source1->a * source2->c);
    dest->c = (source1->a * source2->b) - (source1->b * source2->a);                                           
}

double vector3d_lenght(vector3d* source1){
    VECTOR_TYPE dot_prod = vector3d_dot(source1, source1);
    return sqrt(dot_prod);
}

VECTOR_TYPE vector3d_dot(vector3d* source1, vector3d* source2){
    return (source1->a * source2->a) + (source1->b * source2->b) + (source1->c * source2->c);
}

#endif