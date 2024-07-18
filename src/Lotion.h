#pragma once

#include "SDL2/SDL.h"
#include "Definitions.h"

void
SetColor(SDL_Renderer* renderer, color col) {
  SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, 255);
}
