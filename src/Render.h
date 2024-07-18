#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Source.h"
#include "Definitions.h"
#include <stdlib.h>

void
render(Ray sight, Map* map) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  Ray startshoot = {sight.pos, normalize(sight.dir)};

  for (u16 i = 0; i < W_win; ++i) {
    for (u16 j = 0; j < H_win; ++j) {
      v3 biasXY = mul((v3){-startshoot.dir.y, startshoot.dir.x, 0},(i - W_win / 2.0) / W_win);
      f64 poXY = projectionXY(startshoot.dir);

      v3 biasZ  = mul((v3){startshoot.dir.x * startshoot.dir.z / poXY,
                          startshoot.dir.y * startshoot.dir.z / poXY,
                          poXY},(H_win / 2.0 - j) / W_win);

      Ray shoot = {startshoot.pos, sum(sum(biasXY, biasZ), startshoot.dir)};

      crd poi = {{0, 0, 0}, 0};
      for (u16 k = 0; k < map->rects.count; ++k) {
        crd testpoi = ShootRect(map->rects.Rectangles + k, shoot);
        poi = near(poi, testpoi);
      }

      if (poi.dist > q) {
        SetColor(renderer, poi.col);
        SDL_RenderDrawPoint(renderer, i, j);
      }
    }
  }
  SDL_RenderPresent(renderer);
}
