#include "control.h"
#include "list.h"
#include "vectors.h"
#include <stdio.h>

enum move update(struct car *car)
{
    int x = 0;
    int y = 0;
    for (int i = 0; i < car->map->width; i++)
        for (int j = 0; j < car->map->height; j++)
        {
            if (map_get_floor(car->map, i, j) == FINISH)
            {
              x = i;
              y = j;
            }
        }
    struct vector2 tmp;
    tmp.x = x;
    tmp.y = y;
    struct vector2 cmp = compute_vect(car->position, tmp);
    float angle = 
            get_angle(car->position, tmp);
    printf("%f\n", angle);
        if (is_colly(tmp, cmp) == 0)
      return ACCELERATE;
    else if (angle < 0)
        return  TURN_LEFT;
    else
        return TURN_RIGHT;
    
    return TURN_LEFT;
}
