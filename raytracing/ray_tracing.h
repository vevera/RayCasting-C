#ifndef RAY_TRACING_H
#define RAY_TRACING_H

#include "../vector/vector.h"
#include "../shapes/shape.h"
#include "../shapes/sphere.h"
#include "../light/light.h"
#include "../light/point_light.h"
#include "../utils.h"

#include <stdio.h>

void transform_objects_cordinates(Scene* scene, matrix* transformation_matrix);

bool ray_tracing(vector* output_color, vector* p0, vector* dr, double d_min, double d_max, 
                    ShapeArray* shapes, LightArray* lights);

void calculate_light_intensity( vector* output, LightArray* lights, 
                                vector* n, vector* v, vector* pi, 
                                ShapeArray* shapes, Shape* collided_shape);
bool is_light_blocked_by_object(ShapeArray* shapes, vector* pi, Light* light, vector* l);


void transform_objects_cordinates(Scene* scene, matrix* transformation_matrix) {
    shape_array_copy(scene->shapes, scene->original_shapes);
    light_array_copy(scene->lights, scene->original_lights);

    //vector_print(((Sphere *)(scene->shapes->shapes_[0].concrete_shape_))->center_);

    for (int i = 0; i < scene->shapes->size_; ++i) {
        Shape* curr_shape = scene->shapes->shapes_ + i;
        curr_shape->cordinates_transformation_(transformation_matrix, curr_shape);
    }


    for (int i = 0; i<scene->lights->size_; i++){
       Light* light = scene->lights->lights + i;
       light->light_cordinates_transformation(transformation_matrix, light);
    }
}


bool ray_tracing(vector* output_color, vector* p0, vector* dr, double d_min, double d_max, 
                    ShapeArray* shapes, LightArray* lights){
    
    vec_type zeros[] = {0 , 0, 0};                    
    vector_set(output_color, zeros);                 

    Shape* closest_shape_ = NULL;                    
    double closest_t = INFINITY;
    double t = 0;

    for (int i = 0; i < shapes->size_; ++i) {
        Shape* curr_shape = shapes->shapes_ + i;
        t = curr_shape->intersect_(p0, dr, curr_shape);
        if ((t > 0) && ((t >= d_min) && (t <= d_max)) && (t < closest_t)) {
            closest_t = t;
            closest_shape_ = curr_shape;
        }
    }

    if (closest_shape_ == NULL) {
        return 0;
    }

    vector* pi = vector_create_empty(THREE_DIM);
    vector* normal = vector_create_empty(THREE_DIM);
    vector* v = vector_create_empty(THREE_DIM);

    vector_scale(pi, dr, closest_t);
    vector_add(pi, pi, p0);

    closest_shape_->normal_(normal, pi, closest_shape_);

    // printf("normal: ");
    // vector_print(normal);

    vector_scale(v, dr, -1);
    vector_normalize(v, v);

    calculate_light_intensity(output_color, lights, normal, v, pi, shapes, closest_shape_);
  
    vector_delete(pi);
    vector_delete(normal);
    vector_delete(v);

    return 1;
}

void calculate_light_intensity( vector* output, LightArray* lights, 
                                vector* n, vector* v, vector* pi, 
                                ShapeArray* shapes, Shape* collided_shape) {

    Color* color = collided_shape->color_;

    vector* l = vector_create_empty(THREE_DIM);
    vector* r = vector_create_empty(THREE_DIM);
    vector* contribution = vector_create_empty(THREE_DIM);

    for (int i = 0; i<lights->size_; i++){
        Light* light = lights->lights + i;
        light->calc_light_l_from_point_p(l, pi, light);
        vector_scale(r, n, vector_dot(l, n) * 2);
        vector_sub(r, r, l);

        if (!is_light_blocked_by_object(shapes, pi, light, l)) {
            light->calc_light_contribution(contribution, color, l, n, v, r, light);
            vector_add(output, output, contribution);
        }

    }

    double max_v = vector_max(output);
   
    if (max_v > 1) {
        vector_scale(output, output, 1/max_v);
    }

    vector_delete(l);
    vector_delete(r);
    vector_delete(contribution);
}

bool is_light_blocked_by_object(ShapeArray* shapes, vector* pi, Light* light, vector* l) {
    double t, distance_from_pi;

    for (int i = 0; i < shapes->size_; i++) {
        t = shapes->shapes_[i].intersect_(pi, l, shapes->shapes_ + i);
        distance_from_pi = light->calc_light_distance_from_point_p(pi, light);

        if (t > 0.0001 && t < distance_from_pi)
            return true;
    }

    return false;
}

#endif