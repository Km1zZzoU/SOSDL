#pragma once

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float_t  f32;
typedef double_t f64;

typedef struct {
  f64 x, y, z;
} point;

typedef struct {
  point* p;
  f64    dist;
} crd;

typedef struct {
  i32 x, y, z;
} point_i;

typedef struct {
  point_i* p;
  f64      dist;
} crd_i;

typedef struct {
  i32 x, y, z;
} v3_i;

typedef struct {
  f64 x, y, z;
} v3;

typedef struct {
  point_i pos;
  v3  dir;
} Ray;

typedef struct {
  point_i pos;
  v3 norm;
} Map_plane;

typedef struct {
  i32 maincord;
  i32 cord1, cord2;
  i32 l1, l2;
} Map_Side;

typedef struct {
  point_i pos;
  i32 x, y, z;
} Map_Rectangle;

