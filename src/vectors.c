#include "vectors.h"
#include <stdio.h>//TODO del this
#include <math.h>
float dot_product(struct vector2 u, struct vector2 v)
{
  return u.x * v.x + v.y * u.y;
}

float norm(struct vector2 u)
{
  return sqrt(u.x * u.x + u.y * u.y);
}

float get_angle(struct vector2 u, struct vector2 v)
{
  return acos(dot_product(u, v) / (norm(u) * norm(v)));
}

int sign(float x)
{
  if (x < 0)
    return -1;
  return 1;
}

float get_angle2(struct vector2 u, struct vector2 v)
{
  float na = sqrt(u.x * u.x + u.y * u.y);
  float nb = sqrt(v.x * v.x + v.y * v.y);
  float c = (u.x * u.y + v.x * v.y)/(na * nb);
  float s = (u.x * v.y - v.x * u.y);
  return sign(s) * acos(c);

  return acos(dot_product(u, v) / (norm(u) * norm(v)));
}
struct vector2 add_scal(struct vector2 u, int n)
{
  u.x += n;
  u.y += n;
  return u;
}


struct vector2 set_angle(struct vector2 u, float x, float y)
{
  u.x = x;
  u.y = y;
  return u;
}

struct vector2 compute_vect(struct vector2 u, struct vector2 v)
{
  v.x -= u.x;
  v.y -= u.y;
  return v;
}

int is_colly(struct vector2 u, struct vector2 v)
{
  return fabs(u.x * v.y - u.y * v.x) < 0.0968 ? 1 : 0;
}
