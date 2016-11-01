#include "vectors.h"

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

int is_colly(struct vector2 u, struct vector2 v)
{
  return (u.x * v.y - u.y * v.x < 0.215) ? 0 : 1;
}
