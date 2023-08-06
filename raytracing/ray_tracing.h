#ifndef RAY_TRACING_H
#define RAY_TRACING_H

#include "../vector/vector.h"
#include "../shapes/shape.h"
#include "../shapes/sphere.h"
#include "../light/light.h"
#include "../light/point_light.h"

#include <stdio.h>

bool ray_tracing(vector* output_color, vector* p0, vector* dr, double d_min, double d_max, 
                    ShapeArray* shapes, LightArray* lights);

void calculate_light_intensity( vector* output, LightArray* lights, 
                                vector* n, vector* v, vector* pi, 
                                ShapeArray* shapes, Shape* collided_shape);
bool is_light_blocked_by_object(ShapeArray* shapes, vector* pi, Light* light, vector* l);

bool ray_tracing(vector* output_color, vector* p0, vector* dr, double d_min, double d_max, 
                    ShapeArray* shapes, LightArray* lights){

    vec_type zeros[] = {0 , 0, 0};                    
    vector3d_set(output_color, zeros, THREE_DIM);                 

    Shape* closest_shape_ = NULL;                    
    double closest_t = INFINITY;
    double t = 0;

    for (int i = 0; i < shapes->length_; ++i) {
        Shape* curr_shape = shapes->shapes_[i];
        t = curr_shape->intersect_(p0, dr, curr_shape->shape_);
        if ((t > 0) && ((t >= d_min) && (t <= d_max)) && (t < closest_t)) {
            closest_t = t;
            closest_shape_ = curr_shape;
        }
    }

    if (closest_shape_ == NULL) {
        return 0;
    }

    vector* pi = vector3d_create_empty();
    vector* normal = vector3d_create_empty();
    vector* v = vector3d_create_empty();

    vector3d_scale(pi, dr, closest_t);
    vector3d_add(pi, pi, p0);

    closest_shape_->normal_(normal, pi, closest_shape_->shape_);

    vector3d_scale(v, dr, -1);
    vector3d_normalize(v, v);

    vector_delete(pi);
    vector_delete(normal);
    vector_delete(v);

    calculate_light_intensity(output_color, lights, normal, v, pi, shapes, closest_shape_);

    return 1;
}

void calculate_light_intensity( vector* output, LightArray* lights, 
                                vector* n, vector* v, vector* pi, 
                                ShapeArray* shapes, Shape* collided_shape) {

    Color* color = collided_shape->color_;

    vector* l = vector3d_create_empty();
    vector* r = vector3d_create_empty();
    vector* contribution = vector3d_create_empty();

    for (int i = 0; i<lights->size_; i++){
        Light* light = lights->lights[i];
        light->calc_light_l_from_point_p(l, pi, light);
        vector3d_scale(r, n, vector3d_dot(l, n) * 2);
        vector3d_sub(r, r, l);

        if (!is_light_blocked_by_object(shapes, pi, light, l)) {
            light->calc_light_contribution(contribution, color, l, n, v, r, light);
            vector3d_add(output, output, contribution);
        }

    }

    double max_v = max(VECTOR_AT(output, 0), VECTOR_AT(output, 1));
    max_v = max(VECTOR_AT(output, 2), max_v);

    if (max_v > 1) {
        vector3d_scale(output, output, 1/max_v);
    }

    vector_delete(l);
    vector_delete(r);
    vector_delete(contribution);
}

bool is_light_blocked_by_object(ShapeArray* shapes, vector* pi, Light* light, vector* l) {
    double t, distance_from_pi;

    for (int i = 0; i < shapes->length_; i++) {
        t = shapes->shapes_[i]->intersect_(pi, l, shapes->shapes_[i]);
        distance_from_pi = light->calc_light_distance_from_point_p(pi, light);

        if (t > 0.0001 && t < distance_from_pi)
            return true;
    }

    return false;
}

#endif