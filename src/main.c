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

void load_image() {
    SDL_Surface* imageSurface = IMG_Load(IMG_PATH);
    img = (Image*)malloc(sizeof(Image));
    img->dx = STARTING_DX;
    img->dy = STARTING_DY;
    img->img = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    int w, h;
    SDL_QueryTexture(img->img, NULL, NULL, &w, &h);
    img->texr = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    img->texr->x = SCREEN_WIDTH / 2;
    img->texr->y = SCREEN_HEIGHT / 2;
    img->texr->w = w / 8;
    img->texr->h = h / 8;
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

void handle_collision() {
    if (img->texr->x <= 0 || img->texr->x + img->texr->w >= SCREEN_WIDTH) {
        img->dx = -img->dx;
    }
    if (img->texr->y <= 0 || img->texr->y + img->texr->h >= SCREEN_HEIGHT) {
        img->dy = -img->dy;
    }
}

void update_image() {
    img->texr->x += img->dx;
    img->texr->y += img->dy;
    handle_collision();
}

void draw_screen() {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_RenderFillRect(renderer, img->texr);
    SDL_RenderCopy(renderer, img->img, NULL, img->texr);

    SDL_RenderPresent(renderer);
}

void destroy_exit() {
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(screenSurface);
    SDL_DestroyTexture(img->img);
    free(img->texr);
    free(img);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
}

int main() {
    init_lib();
    load_image();

    unsigned int start_time = SDL_GetTicks();
    unsigned int end_time = 0;
    double delta = 0;

    while (running) {
        handle_input();

        start_time = SDL_GetTicks();
        delta = (double)(start_time - end_time);

        if (delta >= 1000 / (double)FPS) {
            update_image();
            draw_screen();
            end_time = start_time;
        }
    }

    destroy_exit();
    return 0;
}
