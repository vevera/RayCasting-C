#include <stdio.h>
#include "vector/vector.h"
#include "canvas/canvas.h"
#include "scene/scene.h"
#include "light/light.h"
#include "light/ambient_light.h"
#include "camera/camera.h"
// #include "state.h"


#define CREATE_SPHERE(sphere_name, center_x, center_y, center_z, radius, kd_r, kd_g, kd_b, ke_r, ke_g, ke_b, ka_r, ka_g, ka_b, shininess) \
    vector* center_##sphere_name = vector_create(THREE_DIM, (center_x), (center_y), (center_z)); \
    vector* kd_##sphere_name = vector_create(THREE_DIM, (kd_r), (kd_g), (kd_b)); \
    vector* ke_##sphere_name = vector_create(THREE_DIM, (ke_r), (ke_g), (ke_b)); \
    vector* ka_##sphere_name = vector_create(THREE_DIM, (ka_r), (ka_g), (ka_b)); \
    Color* color_##sphere_name = color_create(kd_##sphere_name, ke_##sphere_name, ka_##sphere_name, (shininess)); \
    Shape* sphere_name = shape_create_sphere(center_##sphere_name, (radius), color_##sphere_name)

#define DELETE_SPHERE(sphere_name) \
    do { \
        vector_delete(center_##sphere_name); \
        vector_delete(kd_##sphere_name); \
        vector_delete(ke_##sphere_name); \
        vector_delete(ka_##sphere_name); \
        color_delete(color_##sphere_name); \
        shape_delete_sphere(sphere_name); \
    } while (0)
   
int main(int argc, char *argv[]){

    CREATE_SPHERE(sphere1, 
                    -0.0, -0.0, -500.0, 
                    300, 
                    0.0, 0.6, 0.7,
                    0.0, 0.6, 0.7,
                    0.0, 0.6, 0.7, 
                    7
                    );

    // CREATE_SPHERE(sphere2, 
    //                 -0.0, 200.0, -800.0, 
    //                 300, 
    //                 0.7, 0.1, 0.1,
    //                 0.6, 0.1, 0.1,
    //                 0.7, 0.1, 0.1, 
    //                 7
    //                 );

    // CREATE_SPHERE(sphere3, 
    //                 60.0, 50.0, -200.0, 
    //                 30, 
    //                 0.7, 0.0, 0.8,
    //                 0.7, 0.0, 0.8,
    //                 0.7, 0.0, 0.8, 
    //                 5
    //                 );



    //Sphere 2
    //vector* center = vector_create(THREE_DIM, -40.0, -0.0, -700.0);
    //vector* kd = vector_create(THREE_DIM, 0.0, 0.1, 0.1);
    //vector* ke = vector_create(THREE_DIM, 0.0, 0.1, 0.1);//0.0, 0.0, 0.0
    //Color* color = color_create(kd, ke, kd, 7);
    //Shape* sphere2 = shape_create_sphere(center, 300, color);
   
   
    //Point Light
    vector* position = vector_create(THREE_DIM, 900.0, 1200.0, 100.0);
    vector* intensity = vector_create(THREE_DIM, 0.7, 0.7, 0.7);
    Light* point_light = light_create_point_light(position, intensity);

    //Ambient Light
    vector* ambient_intensity = vector_create(THREE_DIM, 0.2, 0.2, 0.2);
    Light* ambient_light =  light_create_ambient_light(ambient_intensity);

    // Shape Array
    ShapeArray* shapes = shape_create_shape_array(20);
    shape_add_shape_to_array(&sphere1, shapes);
    // shape_add_shape_to_array(&sphere2, shapes);
    // shape_add_shape_to_array(&sphere3, shapes);

    
    // Light Array
    LightArray* lights = light_create_light_array(10);
    light_add_light_to_array(&point_light, lights);
    light_add_light_to_array(&ambient_light, lights);

    vec_type lx = 2.0;
    vec_type ly = 200.0;
    vec_type lz = -500.0;

    vector* eye = vector_create(FOUR_DIM, lx, ly, lz, 1.0);
    vector* at = vector_create(FOUR_DIM, -0.0, -0.0, -500.0, 1.0);
    vector* up =  vector_create(FOUR_DIM, lx, ly + 100.0, lz, 1.0);
    Camera camera = {
        .eye = eye,
        .at = at,
        .up = up
    };

    matrix* wc = matrix_create_empty(FOUR_DIM, FOUR_DIM);
    matrix* cw = matrix_create_empty(FOUR_DIM, FOUR_DIM);
    camera_calculate_wc_mat(wc, cw, &camera);

    transform_objects_cordinates(shapes, lights, wc);
    //transform_objects_cordinates(shapes, lights, cw);

    vector* eye_t = vector_create_empty(FOUR_DIM);
    matrix_vec_mul(eye_t, wc, eye);

    printf("wc: \n");
    matrix_print(wc);

    printf("cw: \n");
    matrix_print(cw);

    printf("eye_t: \n");
    vector_print(eye_t);
    printf("%f", eye_t->data_[3]);

    vector* bg_color = vector_create(THREE_DIM, 0.0, 0.0, 0.0);

    Window * window = canvas_init_window(500, 500);

    Scene scene;
    scene.window = window;
    scene.shapes = shapes;
    scene.lights = lights;


    State state = { 

        .scene = &scene, 
        .camera = &camera,
        .background_color = bg_color,
        .vp_h = 10,
        .vp_w = 10, 
        .vp_z = -1,
        .eye = eye_t,
        .cw = cw,
        .wc = wc
    };

    take_a_picture(&scene, eye_t, 10, 10, -1, bg_color);
    canvas_update_window(scene.window);
    canvas_wait_event(&state);
    canvas_destroy_window(window);
  
    DELETE_SPHERE(sphere1);
    // DELETE_SPHERE(sphere2);
    // DELETE_SPHERE(sphere3);

    vector_delete(position);
    vector_delete(intensity);
    vector_delete(bg_color);
    vector_delete(ambient_intensity);
    vector_delete(eye);
    vector_delete(at);
    vector_delete(up);
    matrix_delete(wc);
    vector_delete(eye_t);
    light_free_light_array(lights);

    return EXIT_SUCCESS;
}