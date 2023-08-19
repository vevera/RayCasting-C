#ifndef SCENE_H
#define SCENE_H

#include "../canvas/canvas.h"
#include "../shapes/shape.h"
#include "../raytracing/ray_tracing.h"
#include "../light/light.h"

typedef struct scene {
    ShapeArray* shapes;
    LightArray* lights;
    Window* window;
} Scene;

void take_a_picture(Scene* scene, vector* camera, double viewp_w, 
                    double viewp_h, double viewp_z, vector* bgColor);

void take_a_picture(Scene* scene, vector* camera, double viewp_w, 
                    double viewp_h, double viewp_z, vector* bgColor){

    double dx = viewp_w/(double)scene->window->width;
    double dy = viewp_h/(double)scene->window->height; 

    double  yj, xj;

    vector* dr = vector_create_empty(); 
    vector* p0 = camera;  
    vector* raytrace_color = vector_create_empty();

    for (int l = 0; l < scene->window->height; l++) {
        yj = ((viewp_h - dy)/ 2.0) - (l * dy);
        for (int c = 0; c < scene->window->width; c++) { 
            xj = (-viewp_w / 2.0) + (dx / 2.0) + (c * dx);

            vec_type elements[] = {xj, yj, viewp_z};
            vector_set(dr, elements);

            vector_sub(dr, dr, camera);

            if(ray_tracing(raytrace_color, p0, dr, 
                                        viewp_z, 
                                        INFINITY, 
                                        scene->shapes,
                                        scene->lights))  {
                canvas_add_pixel(scene->window, raytrace_color);                                    
            }

            else {
                canvas_add_pixel(scene->window, bgColor); 
            }

            
        }    
    }
    vector_delete(dr);   
    vector_delete(raytrace_color);              
}

#endif