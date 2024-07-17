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

double globl = 1.5;
#include "Render.h"
#include "Math.h"


int main() {
  Ray cam = {{1, -10, 13}, {0, 1, -1}};
  Map_Rectangle rect = {{0, 1, 0}, 10, 10, 10};
  /*
  crd a = shoot_Rect(&rect, cam);
   */
  Map map = {{1, &rect}};
  gir = initialize_window();

  int wasdshsp[6] = {0, 0, 0, 0, 0, 0};
  int rot[4] = {0, 0, 0, 0};

  while (gir) {
    clock_t t0 = clock();
    render(cam, &map);
    //printf("%.1lf, %.1lf, %.1lf | %.1lf, %.1lf, %.1lf\n", cam.pos.x, cam.pos.y, cam.pos.z, cam.dir.x, cam.dir.y, cam.dir.z);

    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
      switch (ev.type) {
        case SDL_KEYDOWN:
          switch (ev.key.keysym.sym) {
            case 'c':
              globl += 0.1;
              break;
            case 'x':
              globl -= 0.1;
              break;
          }
        case SDL_KEYUP:
          switch (ev.key.keysym.sym) {
            case 'w':
              wasdshsp[0] = ev.type == SDL_KEYDOWN;
              break;
            case 'a':
              wasdshsp[1] = ev.type == SDL_KEYDOWN;
              break;
            case 's':
              wasdshsp[2] = ev.type == SDL_KEYDOWN;
              break;
            case 'd':
              wasdshsp[3] = ev.type == SDL_KEYDOWN;
              break;
            case 'q':
              wasdshsp[4] = ev.type == SDL_KEYDOWN;
              break;
            case 'e':
              wasdshsp[5] = ev.type == SDL_KEYDOWN;
              break;

            case SDLK_ESCAPE:
              gir = 0;
              break;

            case SDLK_UP:
              rot[0] = ev.type == SDL_KEYDOWN;
              break;
            case SDLK_LEFT:
              rot[1] = ev.type == SDL_KEYDOWN;
              break;
            case SDLK_DOWN:
              rot[2] = ev.type == SDL_KEYDOWN;
              break;
            case SDLK_RIGHT:
              rot[3] = ev.type == SDL_KEYDOWN;
              break;
            default:
              break;
          }
          break;
        case SDL_QUIT:
          gir = 0;
          break;
      }
    }

    point teorpos = {cam.pos.x, cam.pos.y, cam.pos.z};

    if (wasdshsp[0]) {
      teorpos.x += cam.dir.x * movespeed * 1.2;
      teorpos.y += cam.dir.y * movespeed * 1.2;
      teorpos.z += cam.dir.z * movespeed * 1.2;
    }

    if (wasdshsp[1]) {
      teorpos.x += rotateXY(cam.dir, -pi / 2).x * movespeed;
      teorpos.y += rotateXY(cam.dir, -pi / 2).y * movespeed;
    }

    if (wasdshsp[2]) {
      teorpos.x -= cam.dir.x * movespeed * 1.2;
      teorpos.y -= cam.dir.y * movespeed * 1.2;
      teorpos.z -= cam.dir.z * movespeed * 1.2;
    }

    if (wasdshsp[3]) {
      teorpos.x += rotateXY(cam.dir, pi / 2).x * movespeed;
      teorpos.y += rotateXY(cam.dir, pi / 2).y * movespeed;
    }

    if (wasdshsp[4]) {
      teorpos.z -= movespeed/2.0;
    }

    if (wasdshsp[5]) {
      teorpos.z += movespeed/2.0;
    }

    if (rot[0]) {
      cam.dir = rotateUP(cam.dir, -rotatespeed);
    }

    if (rot[1]) {
      cam.dir = rotateXY(cam.dir, -rotatespeed);
    }

    if (rot[2]) {
      cam.dir = rotateUP(cam.dir, rotatespeed);
    }

    if (rot[3]) {
      cam.dir = rotateXY(cam.dir, rotatespeed);
    }

    cam.pos = teorpos;

    clock_t t = clock();
    f64 seconds = (f64)(t - t0) / CLOCKS_PER_SEC;
    printf(" %.2lf %.15lf\n", globl, 1.0 / seconds);
  }
  return 0;
}

