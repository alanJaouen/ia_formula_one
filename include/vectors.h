#ifndef VECTORS_H
#define VECTORS_H

#include <math.h>
#include <stdlib.h>
#include <control.h>
float dot_product(struct vector2 u, struct vector2 v);
float norm(struct vector2 u);
float get_angle(struct vector2 u, struct vector2 v);
struct vector2 add_scal(struct vector2 u, int n);
struct vector2 set_angle(struct vector2 u, float x, float y);
int is_colly(struct vector2 u, struct vector2 v);
struct vector2 compute_vect(struct vector2 u, struct vector2 v);

#endif /*VECTORS_H*/
