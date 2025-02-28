#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 450
#define IMG_PATH "../assets/DVD.png"
#define SOUND_PATH "../assets/VineBoom.mp3"
#define STARTING_DX 5
#define STARTING_DY 5
#define FPS 60

typedef struct {
    SDL_Texture* img;
    int w, h;
    int dx, dy;
    SDL_Rect* texr;
} Image;

void init_lib();
void handle_input();
void update_image();
void draw_screen();
void destroy_exit();
void load_image();
void handle_collision();
