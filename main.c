#include <stdio.h>
#include "vector/vector.h"
#include "canvas/canvas.h"
#include "scene/scene.h"
#include "light/light.h"

int main(int argc, char *argv[]){
    //Sphere
    vector* center = vector3d_create(-0, -0, -500);
    vector* kd = vector3d_create(0.1, 0.1, 0.2);
    vector* ke = vector3d_create(0.8, 0.8, 0.8);
    Color* color = color_create(kd, ke, ke, 1);
    Shape* sphere = shape_create_sphere(center, 300, color);
    
    //Sphere
    vector* center_shre_1 = vector3d_create(100, 0, -100);
    vector* kd_shre_1 = vector3d_create(0.8, 0.8, 0.8);
    vector* ke_shre_1 = vector3d_create(1, 1, 1);
    Color* color_shre_1 = color_create(kd_shre_1, ke_shre_1, ke_shre_1, 1);
    Shape* shre_1 = shape_create_sphere(center_shre_1, 50, color_shre_1);
   
    //Point Light
    vector* position = vector3d_create(0, 100, -300);
    vector* intensity = vector3d_create(1, 1, 1);
    Light* point_light = light_create_point_light(position, intensity);
    
    // Shape Array
    ShapeArray* shapes = shape_create_shape_array(20);
    shape_add_shape_to_array(&sphere, shapes);
    shape_add_shape_to_array(&shre_1, shapes);


    // Light Array
    LightArray* lights = light_create_light_array(10);
    light_add_light_to_array(&point_light, lights);


    vector* camera = vector3d_create(0, 0, 0);
    vector* bg_color = vector3d_create(0, 0, 0);

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

    return EXIT_SUCCESS;
}