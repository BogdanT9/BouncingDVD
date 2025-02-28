#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 450

void init();
void setup();
void handle_input();
void update();
void draw();
void close();
