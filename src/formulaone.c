#include "control.h"
#include "list.h"
#include "vectors.h"

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
    float angle = 
            get_angle(car->direction, set_angle(car->direction, x, y));

    if (angle > -0.5 && angle < 0.5)
      return ACCELERATE;
    else if (angle < -0.5)
        return  TURN_LEFT;
    else
        return TURN_RIGHT;
    
    return TURN_LEFT;
}
