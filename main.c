#include <stdio.h>
#include "vector/vector.h"
#include "canvas/canvas.h"
#include "scene/scene.h"
#include "light/light.h"
#include "light/ambient_light.h"

int main(int argc, char *argv[]){
    //maxof(6, 1, 2, 3, 4);

    // matrix* mat = matrix_create(3, 3, 
    //                             1.0, 2.2, 3.3, 
    //                             3.0, 2.0, 4.1, 
    //                             3.0, 2.0, 2.0);

    // matrix* mat2 = matrix_create(3, 3, 
    //                             1.0, 2.2, 3.3, 
    //                             3.0, 2.0, 4.1, 
    //                             3.0, 2.0, 2.0);
    
    // matrix* matd = matrix_create_empty(3, 3);

    // matrix_mul(matd, mat, mat2);

    // matrix_print(matd);

    // vector* vec_1 = vector_create(2, 3, 4);
    // vector* dest = vector_create_empty();

    // matrix_vec_mul(dest, mat, vec_1);

    // vector_print(dest);


    // matrix_delete(mat);
    // matrix_delete(mat2);
    // matrix_delete(matd);

    //Sphere
    vector* center = vector_create(-0, -0, -500);
    vector* kd = vector_create(0.7, 0.1, 0.1);
    vector* ke = vector_create(0.6, 0.1, 0.1);//0.0, 0.0, 0.0
    Color* color = color_create(kd, ke, kd, 7);
    Shape* sphere = shape_create_sphere(center, 300, color);
   
    //Point Light
    vector* position = vector_create(500, 200, 100);
    vector* intensity = vector_create(0.7, 0.7, 0.7);
    Light* point_light = light_create_point_light(position, intensity);

    //Ambient Light
    vector* ambient_intensity = vector_create(0.2, 0.2, 0.2);
    Light* ambient_light =  light_create_ambient_light(ambient_intensity);

    // Shape Array
    ShapeArray* shapes = shape_create_shape_array(20);
    shape_add_shape_to_array(&sphere, shapes);
    
    // Light Array
    LightArray* lights = light_create_light_array(10);
    light_add_light_to_array(&point_light, lights);
    light_add_light_to_array(&ambient_light, lights);

    vec_type lx = 300;
    vec_type ly = 800;
    vec_type lz = -400;


    vector* camera = vector_create(0, 0, 0);
    vector* bg_color = vector_create(0, 0, 0);

    Window * window = canvas_init_window(500, 500);

    Scene scene;
    scene.window = window;
    scene.shapes = shapes;
    scene.lights = lights;

    take_a_picture(&scene, camera, 2, 2, -1, bg_color);
    canvas_update_window(scene.window);
    canvas_wait_event();
    canvas_destroy_window(window);
  
    vector_delete(center);
    vector_delete(kd);
    vector_delete(ke);
    color_delete(color);
    vector_delete(position);
    vector_delete(intensity);
    vector_delete(camera);
    vector_delete(bg_color);
    vector_delete(ambient_intensity);
    light_free_light_array(lights);

    return EXIT_SUCCESS;
}