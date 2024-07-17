#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Source.h"
#include "Definitions.h"
#include <stdlib.h>

void
render(Ray sight, Map* map) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // установка цвета бг
  SDL_RenderClear(renderer); // чистка всего

  f64 vapp = FOV_h / W_win;

  Ray startshoot = {sight.pos, rotateUP(sight.dir, vapp * (H_win / 2.0))};
  //printf("(%.3lf, %.3lf, %.3lf)\n", startshoot.dir.x, startshoot.dir.y, startshoot.dir.z);
  //abort();
  for (u16 i = 0; i < W_win; ++i) {
    Ray shoot = {startshoot.pos, rotateXY(startshoot.dir, (i - W_win / 2.0) * vapp)};

    //clock_t t0 = clock();
    for (u16 j = 0; j < H_win; ++j) {
      shoot.dir = rotateUP(shoot.dir, -vapp *pow(cos((i - W_win / 2.0) * (j - H_win / 2.0) * vapp / 250), 3));

      crd poi = {{0, 0, 0}, 0};
      for (u16 k = 0; k < map->rects.count; ++k) {
        crd testpoi = shoot_Rect(map->rects.Rectangles + k, shoot);
        /*
         */
        //poi = *near(&poi, testpoi);
        //poi = *near(&poi, testpoi);
        poi = testpoi;
      }

      if (poi.dist > q) {
        //printf("%.10lf\n", poi.dist);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawPoint(renderer, i, j);
      }
    }

    /*
    clock_t t = clock();
    f64 seconds = (f64)(t - t0) / CLOCKS_PER_SEC;
    printf("%.15lf\n", seconds);
  */
  }
  SDL_RenderPresent(renderer);
}
