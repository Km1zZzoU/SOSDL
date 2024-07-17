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

    for (u16 j = 0; j < H_win; ++j) {
      shoot.dir = rotateUP(shoot.dir, -vapp);

      crd* poi;
      for (u16 k = 0; k < map->rects.count; ++k) {
        //clock_t t0 = clock();
        crd* testpoi = shoot_Rect(map->rects.Rectangles + k, shoot);
        /*
        clock_t t = clock();
        f64 seconds = (f64)(t - t0) / CLOCKS_PER_SEC;
        printf("%.15lf\n", seconds);
         */
        //poi = near(poi, testpoi);
        poi = testpoi;
      }

      if (poi) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawPoint(renderer, i, j);
      }
      /*
      if ((i == 0 || i == W_win - 1) && (j == 0 || j == H_win - 1))
        printf("(%.3lf, %.3lf, %.3lf)\n", shoot.dir.x, shoot.dir.y, shoot.dir.z);
      */
    }
  }
  SDL_RenderPresent(renderer);
}
