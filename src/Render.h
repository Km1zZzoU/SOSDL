#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Source.h"
#include "Definitions.h"
#include <stdlib.h>

void
render(Ray sight, Map* map) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // установка цвета бг
  SDL_RenderClear(renderer); // чистка всего

  for (u16 i = 0; i < W_win; ++i) {
    Ray shoot = {sight.pos, rotateXY(sight.dir, FOV_h / W_win * (i - W_win / 2))};
    for (u16 j = 0; j < H_win; ++j) {
      shoot.dir = rotateUP(shoot.dir, FOV_v / H_win * (j - H_win / 2));

      crd* poi = (crd*) malloc(sizeof(crd));
      if (!poi) {
        puts("malloc poi");
        abort();
      }
      for (u16 k = 0; k < map->rects.count; ++k) {
        crd* testpoi = shoot_Rect(map->rects.Rectangles + k, shoot);
        poi = near(poi, testpoi);
      }
      if (poi != 0) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawPoint(renderer, i, H_win - j);
      } else {
        printf("%d %d\n", i, j);
      }
      free(poi);
    }
  }

  SDL_RenderPresent(renderer);
}
