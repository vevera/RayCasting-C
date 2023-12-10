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
    void* concrete_shape_;
    Color* color_;
    double (*intersect_)(vector* p0, vector*dr, struct shape* shape_);
    void (*normal_)(vector* dest, vector* pi, struct shape* shape_);
    void (*cordinates_transformation_)(matrix* transformation_matrix, struct shape* shape_);
} Shape;

typedef struct shape_array {
    Shape** shapes_;
    int size_;
    int max_size_;
} ShapeArray;


Color* color_create(vector* kd, vector* ke, vector* ka, double shininess);
void color_delete(Color* color);
ShapeArray* shape_create_shape_array(int max_length);
//void * shape_free_shape_array(ShapeArray* shapes);
void shape_add_shape_to_array(Shape** shape, ShapeArray * array);

Color* color_create(vector* kd, vector* ke, vector* ka, double shininess) {
    Color* color = (Color*)malloc(sizeof(Color));
    color->ka = ka;
    color->ke = ke;
    color->kd = kd;
    color->shininess = shininess;
    return color;
}

void color_delete(Color* color){
    free(color);
}

ShapeArray * shape_create_shape_array(int max_length) {
    ShapeArray* shape_arr = (ShapeArray*)malloc(sizeof(ShapeArray));
    shape_arr->shapes_ = (Shape **)malloc(max_length * sizeof(Shape*));
    shape_arr->size_ = 0;
    shape_arr->max_size_ = max_length;

    return shape_arr;
}

// void * shape_free_shape_array(ShapeArray* shapes) {
//     for (int i = 0; i<shapes->size_; i++){
//         shape_dele
//     }

// }

void shape_add_shape_to_array(Shape** shape, ShapeArray * array) {
    if (array->size_ < array->max_size_) {
        array->shapes_[array->size_++] = *shape;
    }
}

#endif