#include "control.h"

enum move update(struct car *car)
{
  car = car;
  struct car *clone = car_clone(car);
  if(car_move(clone, ACCELERATE) != CRASH)
  { 
    car_delete(clone);
    return ACCELERATE;
  }


 
  return TURN_LEFT;
}
