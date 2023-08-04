#include <SDL2/SDL.h>
#include <stdlib.h>

typedef struct Window {
    SDL_Window *window = NULL;
    SDL_Surface *screen = NULL;
    SDL_Surface *surf = NULL;
    unsigned char * data_ = NULL;
    int width;
    int height;
} Window;

Window* init_window(int width, int height);

Window* init_window(int width, int height) {
    Window* window = (Window *)malloc(sizeof(Window));

    window->height = height;
    window->width - width;

    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
        window->window = SDL_CreateWindow("scene", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, width,
                                        height, SDL_WINDOW_ALLOW_HIGHDPI);
        if (window->window != NULL) {
            window->screen = SDL_GetWindowSurface(window->window);
        }

        if (window->screen != NULL) {
            window->data_ = (unsigned char *)malloc(width * height * sizeof(unsigned char));
        }
    }

    return window;
}

void destroy_window(Window* window) {
    if (window->screen != NULL)
        SDL_FreeSurface(window->screen);
    if (window->surf != NULL)
        SDL_FreeSurface(window->surf);
    if (window->window != NULL)
        SDL_DestroyWindow(window->window);

    free(window->data_);
    
    SDL_Quit();
}

void update_window(Window* window) {

    SDL_Rect offset;
    // Give the offsets to the rectangle
    offset.x = 0;
    offset.y = 0;

    window->surf = SDL_CreateRGBSurfaceFrom((void *) window->data_, window->width, window->height, 24,
                                    3 * window->width, 0x000000ff, 0x0000ff00,
                                    0x00ff0000, 0xff000000);
    // Blit the surface
    SDL_BlitSurface(window->surf, NULL, window->screen, &offset);
    SDL_FreeSurface(window->surf);
    SDL_UpdateWindowSurface(window->window);

    free(window->data_);
    free(window);
}