#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>
#include "Math.h"
#include "Definitions.h"

bool gir = false; // game is running
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;


#define H_win 270
#define W_win 430
#define pi 3.1415926535897932384626433832795028841971
f64 FOV_v = pi / 2;
f64 FOV_h = 80 / 180 * pi;

typedef struct {
  u16 count;
  Map_Rectangle* Rectangles;
} Map_Rectangles;

typedef struct {
  Map_Rectangles rects;
} Map;

bool
initialize_window() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return false;
  }

  window = SDL_CreateWindow("<=-=||=-=>", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_win, H_win, 0);
  if (!window) {
		fprintf(stderr, "Error creating SDL Window.\n");
		return false;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
		fprintf(stderr, "Error creating SDL Renderer.\n");
		return false;
  }

  return true;
}