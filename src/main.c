//
// Created by ezhe on 09.07.24.
//

#include <SDL2/SDL.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

#include "Render.h"
#include "Math.h"

int main() {
  Ray signt = {{0, 0, 10}, {3, 2, -10}};
  Map_Rectangle rect = {{1, 1, 0}, 10, 10, 2};
  Map map = {{1, &rect}};
  /*
  crd* a = shoot_Rect(&rect, signt);
   */
  gir = initialize_window();
  while (gir) {
    render(signt, &map);
    SDL_Delay(10);
  }
  return 0;
}

