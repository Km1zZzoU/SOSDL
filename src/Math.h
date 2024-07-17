#pragma once
#include "Definitions.h"

#include <math.h>

#define q 0.000001

#define min(a, b)                                                              \
  ({                                                                           \
    typeof(a) _a = (a), _b = (b);                                              \
    _a < _b ? _a : _b;                                                         \
  })
#define max(a, b)                                                              \
  ({                                                                           \
    typeof(a) _a = (a), _b = (b);                                              \
    _a > _b ? _a : _b;                                                         \
  })
#define sign(a)                                                                \
  ({                                                                           \
    typeof(a) _a = (a);                                                        \
    (typeof(a))(_a < 0 ? -1 : (_a > 0 ? 1 : 0));                               \
  })

f64
dist(point p1, point p2) {
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

v3
mul(v3 v, f64 cons) {
  v3 w = {v.x * cons, v.y * cons, v.z * cons};
  return w;
}

v3
normalize(v3 v) {
  f64 len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  return mul(v, 1 / len);
}

v3
rotateXY(v3 v, f64 r) {
  v3 w = {v.x * cos(r) - v.y * sin(r),v.y * cos(r) + v.x * sin(r), v.z};
  return w;
  return normalize(w);
}

v3
rotateUP(v3 v, f64 r) {
  f64 xy = sqrt(v.x * v.x + v.y * v.y);
  f64 newxy = xy * cos(r) - v.z * sin(r);
  f64 k = newxy / xy;
  v3 w = {k * v.x, k * v.y, xy * sin(r) + v.z * cos(r)};
  return w;
  return normalize(w);
}

void
shoot_Side(crd* coord, int maincord,
                int cord1, int cord2, int l1, int l2,
                f64 dirx, f64 diry, f64 dirz,
                f64 posx, f64 posy, f64 posz) {
  if (!dirx)
    return;

  f64 len = (maincord - posx) / dirx;
  if (len < 0)
    return;

  point p1 = {maincord, diry * len + posy, dirz * len + posz};
  if (p1.y < cord1 || p1.y > cord1 + l1)
    return;
  if (p1.z < cord2 || p1.z > cord2 + l2)
    return;
  point p2 = {posx, posy, posz};
  coord->p = p1;
  coord->dist = dist(p1, p2);
}

crd
near(crd coord, crd tmp) {
  if (tmp.dist < q)
    return coord;

  if (coord.dist < q)
    return tmp;

  if (coord.dist > tmp.dist) {
    return tmp;
  }

  return coord;
}

crd
shoot_Rect(Map_Rectangle* rect, Ray ray) {

  crd coord = {{0, 0, 0}, 0};
  crd tmp   = {{0, 0, 0}, 0};

  if ((ray.pos.x > rect->pos.x + rect->x) || (ray.pos.x < rect->pos.x)) {
    shoot_Side(&tmp, rect->pos.x + rect->x * (ray.pos.x > rect->pos.x),
               rect->pos.y, rect->pos.z, rect->y, rect->z,
               ray.dir.x, ray.dir.y, ray.dir.z,
               ray.pos.x, ray.pos.y, ray.pos.z);
    coord = near(coord, tmp);
  }

  if ((ray.pos.y > rect->pos.y + rect->y) || (ray.pos.y < rect->pos.y)) {
    shoot_Side(&tmp, rect->pos.y + rect->y * (ray.pos.y > rect->pos.y),
               rect->pos.x, rect->pos.z, rect->x, rect->z,
               ray.dir.y, ray.dir.x, ray.dir.z,
               ray.pos.y, ray.pos.x, ray.pos.z);
    coord = near(coord, tmp);
  }

  if ((ray.pos.z > rect->pos.z + rect->z) || (ray.pos.z < rect->pos.z)) {
    shoot_Side(&tmp, rect->pos.z + rect->z * (ray.pos.z > rect->pos.z),
               rect->pos.y, rect->pos.x, rect->y, rect->x,
               ray.dir.z, ray.dir.y, ray.dir.x,
               ray.pos.z, ray.pos.y, ray.pos.x);
    coord = near(coord, tmp);
  }
/*
*/
  return coord;
}
