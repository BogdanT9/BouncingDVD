#include "app.h"

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Renderer* renderer = NULL;
bool running = true;
Image* img = NULL;

void init_lib() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        fprintf(stderr, "IMG_Init Error: %s\n", IMG_GetError());
        exit(1);
    }
    window = SDL_CreateWindow("Bouncing DVD Logo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        exit(1);
    }
    screenSurface = SDL_GetWindowSurface(window);
    if (screenSurface == NULL) {
        fprintf(stderr, "SDL_GetWindowSurface Error: %s\n", SDL_GetError());
        exit(1);
    }
}

Image* load_image(const char* path) {
    Image* img = (Image*)malloc(sizeof(Image));
    img->img = IMG_LoadTexture(renderer, path);
    SDL_QueryTexture(img->img, NULL, NULL, &img->w, &img->h);
    img->texr = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    img->texr->x = SCREEN_WIDTH / 2;
    img->texr->y = SCREEN_HEIGHT / 2;
    img->texr->w = img->w * 2;
    img->texr->h = img->h * 2;
    return img;
}

void handle_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }
            break;
        default:
            break;
    }
}

void update_image() {}

void draw_screen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void destroy_exit() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_FreeSurface(screenSurface);
    SDL_DestroyTexture(img->img);
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
    IMG_Quit();
}

int main() {
    init_lib();
    img = load_image(IMG_PATH);
    while (running) {
        handle_input();
        update_image();
        draw_screen();
    }
    destroy_exit();
    return 0;
}
