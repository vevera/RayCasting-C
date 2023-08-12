#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"
#include "../vector/vector.h"
#include "../utils.h"

typedef struct sphere
{
    double radius_;
    vector* center_;
} Sphere;


double sphere_intersect(vector* p0, vector* dr, struct shape* shape_);
void sphere_normal(vector* dest, vector* pi, struct shape* shape_);
Shape* shape_create_sphere(vector* center, double radius, Color* color);

double sphere_intersect(vector* p0, vector* dr, struct shape* shape_) {
    Sphere * sphere = (Sphere *)(shape_->concrete_shape_);
    
    double t1, t2, a, b, c, delta;

    vector* w = vector3d_create_empty();
    vector3d_sub(w, p0, sphere->center_);

    a = vector3d_dot(dr, dr);
    b = 2 * (vector3d_dot(w, dr));
    c = vector3d_dot(w, w) - pow(sphere->radius_, 2);

    vector_delete(w);
    
    delta = pow(b, 2) - 4 * a * c;

    if (delta < 0) {
        return INFINITY;
    }

    t1 = (-b + sqrt(delta))/ (2 * a);
    t2 = (-b - sqrt(delta))/ (2 * a);

    return min(t1, t2);
}

void sphere_normal(vector* dest, vector* pi, struct shape* shape_){
    Sphere * sphere = (Sphere *)shape_->concrete_shape_;
    vector3d_sub(dest, pi, sphere->center_);
    vector3d_scale(dest, dest, 1/sphere->radius_);
}

Shape* shape_create_sphere(vector* center, double radius, Color* color){

    Sphere * sphere = (Sphere *)malloc(sizeof(Sphere));
    Shape * shape = (Shape *)malloc(sizeof(Shape));

    sphere->center_ = center;
    sphere->radius_ = radius;

    shape->shape_type_ = SHAPE_SPHERE;
    shape->concrete_shape_ = sphere;
    shape->color_ = color;
    shape->intersect_ = sphere_intersect;
    shape->normal_ = sphere_normal;

    return shape;
}

void shape_delete_sphere(Shape* shape) {
    free(shape->concrete_shape_);
    free(shape);
}

#endif