#include "control.h"
#include "list.h"
#include "vectors.h"

enum move update(struct car *car)
{
    float angle = 
            get_angle(car->direction, set_angle(car->direction, 44, 3));

    if (angle > -0.5 && angle < 0.5)
      return ACCELERATE;
    else if (angle < -0.5)
        return  TURN_LEFT;
    else
        return TURN_RIGHT;
    
    return TURN_LEFT;
}
