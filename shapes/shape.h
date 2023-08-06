#ifndef SHAPE_H
#define SHAPE_H

#include "../vector/vector.h"

typedef struct color {
    vector* kd;
    vector* ke;
    vector* ka;
    double shininess;
} Color;

typedef enum SHAPE_TYPE {
    SHAPE_UNKNOWN,
    SHAPE_SPHERE,
    SHAPE_PLANE,
    SHAPE_CONE,
    SHAPE_CYLINDER,
    SHAPE_MESH,
} SHAPE_TYPE;

typedef struct shape
{
    SHAPE_TYPE shape_type_;
    void* shape_;
    Color* color_;
    double (*intersect_)(vector* p0, vector*dr, void* shape_);
    void (*normal_)(vector* dest, vector* pi, void* shape_);
} Shape;

typedef struct shape_array {
    Shape** shapes_;
    int length_;
    int max_length_;
} ShapeArray;


Color* color_create(vector* kd, vector* ke, vector* ka, double shininess);
void color_delete(Color* color);

ShapeArray * shape_create_shape_array(int max_length);
void shape_add_shape_to_array(Shape** shape, ShapeArray * array);
double min(double a, double b);
double max(double a, double b);

Color* color_create(vector* kd, vector* ke, vector* ka, double shininess) {
    Color* color = (Color*)malloc(sizeof(Color));
    color->ka = ka;
    color->ke = ke;
    color->kd = kd;

    return color;
}

void color_delete(Color* color){
    free(color);
}

ShapeArray * shape_create_shape_array(int max_length) {
    ShapeArray* shape_arr = (ShapeArray*)malloc(sizeof(ShapeArray));
    shape_arr->shapes_ = (Shape **)malloc(max_length * sizeof(Shape*));
    shape_arr->length_ = 0;
    shape_arr->max_length_ = max_length;

    return shape_arr;
}

void shape_add_shape_to_array(Shape** shape, ShapeArray * array) {
    if (array->length_ < array->max_length_) {
        array->shapes_[array->length_++] = *shape;
    }
}


double min(double a, double b) {
    if (a < b) {
        return a;
    }
    return b;
}

double max(double a, double b) {
    if (a > b) {
        return a;
    }
    return b;
}

#endif