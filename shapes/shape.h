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

typedef struct shape_array {
    Sphere* spheres_;
    int size_;
    int max_size_;
} ShapeArray;


Color* color_create(vector* kd, vector* ke, vector* ka, double shininess);
void color_delete(Color* color);
ShapeArray* shape_create_shape_array(int max_length);
void shape_array_copy(ShapeArray* dest, ShapeArray* src);
//void * shape_free_shape_array(ShapeArray* shapes);
void shape_add_shape_to_array(Sphere* sphere, ShapeArray * array);

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
    shape_arr->spheres_ = (Sphere *)malloc(max_length * sizeof(Sphere));
    shape_arr->size_ = 0;
    shape_arr->max_size_ = max_length;

    return shape_arr;
}

void shape_array_copy(ShapeArray* dest, ShapeArray* src) {
    assert(dest->max_size_ == src->max_size_);
    memcpy(dest->spheres_, src->spheres_, src->max_size_ * sizeof(Sphere));
    // for (size_t idx = 0; idx < src->max_size_ ; idx++) {
    //     Shape* dest_shape = dest->shapes_[idx];
    //     memcpy(dest_shape, src->shapes_[idx], sizeof(Shape));
    //     dest_shape->concrete_shape_ = dest_shape->copy_shape(dest_shape);
    // }
    dest->size_ = src->size_;
}

// void * shape_free_shape_array(ShapeArray* shapes) {
//     for (int i = 0; i<shapes->size_; i++){
//         shape_dele
//     }

// }

void shape_add_shape_to_array(Sphere* sphere, ShapeArray * array) {
    if (array->size_ < array->max_size_) {
        array->spheres_[array->size_++] = *sphere;
    }
}

#endif