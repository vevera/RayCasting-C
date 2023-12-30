#ifndef CANVAS_H
#define CANVAS_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../shapes/shape.h"
#include "../light/light.h"
#include "../camera/camera.h"

typedef struct window {
    SDL_Window *window;
    SDL_Surface *screen;
    unsigned char * data_;
    int width;
    int height;
    int last_modified_idx;
} Window;

#include "../state.h"

Window* canvas_init_window(int width, int height);
void canvas_destroy_window(Window* window);
void canvas_update_window(Window* window);
void canvas_wait_event(State* state);

Window* canvas_init_window(int width, int height) {
    Window* window = (Window *)malloc(sizeof(Window));

    window->window = NULL;
    window->screen = NULL;
    window->data_ = NULL;
    window->height = height;
    window->width = width;
    window->last_modified_idx = 0;
    
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
        window->window = SDL_CreateWindow("scene", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, width,
                                        height, SDL_WINDOW_ALLOW_HIGHDPI);
        if (window->window != NULL) {
            window->screen = SDL_GetWindowSurface(window->window);
        }

        if (window->screen != NULL) {
            window->data_ = (unsigned char *)malloc(3* width * height * sizeof(unsigned char));
        }
    }

    return window;
}

void canvas_destroy_window(Window* window) {
    if (window->screen != NULL)
        SDL_FreeSurface(window->screen);
    if (window->window != NULL)
        SDL_DestroyWindow(window->window);

    free(window->data_);
    free(window);
    
    SDL_Quit();
}

void canvas_update_window(Window* window) {

    SDL_Rect offset;
    // Give the offsets to the rectangle
    offset.x = 0;
    offset.y = 0;

    SDL_Surface *surf = SDL_CreateRGBSurfaceFrom((void *) window->data_, window->width, window->height, 24,
                                    3 * window->width, 0x000000ff, 0x0000ff00,
                                    0x00ff0000, 0xff000000);
    // Blit the surface
    SDL_BlitSurface(surf, NULL, window->screen, &offset);
    SDL_FreeSurface(surf);
    SDL_UpdateWindowSurface(window->window);
}

void canvas_wait_event(State* state) {
    SDL_Event windowEvent;
    while (true) {
        if (SDL_PollEvent(&windowEvent)) {
            if (SDL_QUIT == windowEvent.type) {
                break;
            }
            if (SDL_MOUSEBUTTONDOWN == windowEvent.type) {
                //TO DO PICKING
            }

            if (SDL_KEYDOWN == windowEvent.type) {
                const double t = 10;
                //printf("%d key code\n", windowEvent.key.keysym.sym);
                bool updated = false;
                vector3d td = vector3d_create_empty();
                switch (windowEvent.key.keysym.sym)
                {
                case SDLK_DOWN:
                    vector3d_scale(&td, &state->camera->jc, t);
                    updated = true;
                    break;
                case SDLK_UP:
                    vector3d_scale(&td, &state->camera->jc, -t);
                    //vector_add(state->camera->eye, td, state->camera->eye);
                    updated = true;
                    break;
                case SDLK_LEFT:
                    vector3d_scale(&td, &state->camera->ic, -t);
                    // vector_add(state->camera->eye, td, state->camera->eye);
                    // vector_add(state->camera->up, td, state->camera->up);
                    updated = true;
                    break;
                case SDLK_RIGHT:
                    vector3d_scale(&td, &state->camera->ic, t);
                    // vector_add(state->camera->eye, td, state->camera->eye);
                    // vector_add(state->camera->up, td, state->camera->up);
                    updated = true;
                    break;
                default:
                    break;
                }

                if (updated) {
                    //transform_objects_cordinates(state->scene, state->cw);

                    vector_add(state->camera->eye, td, state->camera->eye);
                    vector_add(state->camera->at, td, state->camera->at);
                    vector_add(state->camera->up, td, state->camera->up);
                    vector_delete(td);

                    camera_calculate_wc_mat(state->wc, state->cw, state->camera);

                    transform_objects_cordinates(state->scene, state->wc);
                    printf("sphere center after: \n");
                    vector_print(((Sphere *)(state->scene->shapes->shapes_[0].concrete_shape_))->center_);

                    // printf("camera positions: \n");
                    // vector_print(state->camera->eye);
                    // vector_print(state->camera->at);
                    // vector_print(state->camera->up);

                  

                    take_a_picture(state->scene, state->eye, state->vp_w, state->vp_h, state->vp_z, state->background_color);
                    canvas_update_window(state->scene->window);
                }
            }  
        }
    }
}

void canvas_add_pixel(Window* window, vector3d* color) {
    window->data_[window->last_modified_idx++] = VECTOR_AT(color, 0) * 255;
    window->data_[window->last_modified_idx++] = VECTOR_AT(color, 1) * 255;
    window->data_[window->last_modified_idx++] = VECTOR_AT(color, 2) * 255;
}


#endif