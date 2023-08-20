#include <stdio.h>
#include "vector/vector.h"
#include "canvas/canvas.h"
#include "scene/scene.h"
#include "light/light.h"
#include "light/ambient_light.h"
#include "camera/camera.h"

int main(int argc, char *argv[]){
    //Sphere
    vector* center = vector_create(THREE_DIM, -0.0, -0.0, -500.0);
    vector* kd = vector_create(THREE_DIM, 0.7, 0.1, 0.1);
    vector* ke = vector_create(THREE_DIM, 0.6, 0.1, 0.1);//0.0, 0.0, 0.0
    Color* color = color_create(kd, ke, kd, 7);
    Shape* sphere = shape_create_sphere(center, 300, color);
   
    //Point Light
    vector* position = vector_create(THREE_DIM, 500.0, 200.0, 100.0);
    vector* intensity = vector_create(THREE_DIM, 0.7, 0.7, 0.7);
    Light* point_light = light_create_point_light(position, intensity);

    //Ambient Light
    vector* ambient_intensity = vector_create(THREE_DIM, 0.2, 0.2, 0.2);
    Light* ambient_light =  light_create_ambient_light(ambient_intensity);

    // Shape Array
    ShapeArray* shapes = shape_create_shape_array(20);
    shape_add_shape_to_array(&sphere, shapes);
    
    // Light Array
    LightArray* lights = light_create_light_array(10);
    light_add_light_to_array(&point_light, lights);
    light_add_light_to_array(&ambient_light, lights);

    vec_type lx = 300.0;
    vec_type ly = 800.0;
    vec_type lz = -400.0;

    vector* eye = vector_create(FOUR_DIM, lx, ly, lz, 1.0);
    vector* at = vector_create(FOUR_DIM, -0.0, -0.0, -500.0, 1.0);
    vector* up =  vector_create(FOUR_DIM, lx, ly + 100.0, lz, 1.0);

    matrix* wc = matrix_create_empty(FOUR_DIM, FOUR_DIM);
    camera_calculate_wc_mat(wc, eye, at, up);

    vector* eye_t = vector_create_empty(FOUR_DIM);
    matrix_vec_mul(eye_t, wc, eye);

    printf("wc: \n");
    matrix_print(wc);

    printf("eye_t: \n");
    vector_print(eye_t);
    printf("%f", eye_t->data_[3]);

    vector* camera = vector_create(THREE_DIM, 0.0, 0.0, 0.0);
    vector* bg_color = vector_create(THREE_DIM, 0.0, 0.0, 0.0);

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