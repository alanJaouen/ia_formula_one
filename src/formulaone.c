#include "control.h"
#include "list.h"
#include "vectors.h"
#include <stdio.h>
#include <stdlib.h>
#define ROUTE 1
#define HERBE 1.2
#define INF 99999

void dijkstra(struct map *map);

enum move update(struct car *car)
{
  if (!g_list)
    dijkstra(car->map);
  if (car->position.x < g_list->pos->x + 0.9
      && car->position.x > g_list->pos->x - 0.9
      && car->position.y < g_list->pos->y + 0.9
      && car->position.y > g_list->pos->x - 0.9
      )
  {
    g_list = list_rm(g_list);
    printf("============\n");
  }
  printf("direction %f %f\n actuel %f %f\n========\n", g_list->pos->x, g_list->pos->y, car->position.x, car->position.y );
  struct vector2 tmp;
  tmp.x = g_list->pos->x;
  tmp.y = g_list->pos->y;
  struct vector2 cmp = compute_vect(car->position, tmp);
  if (is_colly(car->direction, cmp)
      && fabs(car->speed.x) + fabs(car->speed.y) < 2)
    return ACCELERATE;

   if (get_angle2(car->direction, cmp) < 0)
      return  TURN_LEFT;
  else
      return TURN_RIGHT;
  return BRAKE;
}

struct node
{
  struct vector2 v;
  char marked;
  double cost;
  struct node *parent;
};

struct node *get_min(struct map *map, struct node *tab)
{
  struct node *n = NULL;
  for (int i = 0; i < map->width; i++)
    for (int j = 0; j < map->height; j++)
    {

      if (tab[i * map->height + j].cost != INF
        && !tab[i * map->height + j].marked
        && (!n || tab[i * map->height + j].cost < n->cost))
      n = tab +(i * map->height +j);
  }
  return n;
}

void makepath(struct node *pos)
{
  while (pos)
  {
    g_list = list_add(g_list, pos->v.x + 0.5, pos->v.y + 0.5);
    pos = pos->parent;
  }
  print_list(g_list);
}

int compare(struct map *map, struct node *pos, struct node *n)
{
  switch (map_get_floor(map, n->v.x, n->v.y))
  {
    case FINISH:
      makepath(pos);
      return 1;
      break;
    case GRASS:
      if ((pos->cost) + HERBE < n->cost)
      {
        n->cost = pos->cost + HERBE;
        n->parent = pos;
      }
      break;
    case ROAD:
      if ((pos->cost) + ROUTE < n->cost)
      {
        n->cost = pos->cost + ROUTE;
        n->parent = pos;
      }
      break;
    case BLOCK:
      n->marked = 1;
      break;
  }
  return 0;
}

void dijkstra(struct map *map)
{
  struct node tab[(map->width ) * (map->height )];

  for (int i = 0; i < map->width; i++)
    for (int j = 0; j < map->height; j++)
    {
      tab[i * map->height + j].v.x = i;
      tab[i * map->height + j].v.y = j;
      tab[i * map->height + j].marked = 0;
      tab[i * map->height + j].cost = INF;
      tab[i * map->height + j].parent = NULL;
    }
  int x = map_get_start_x(map);
  int y = map_get_start_y(map);
  struct node *n = tab + (x * map->height + y);
  n->cost = 0;
  while (n)
  {
    x = n->v.x;
    y = n->v.y;
    int sum = 0;
    if (x != 0)
      sum += compare(map, n, tab + ((x - 1) * map->height + y));
    if (x != map->width - 1)
      sum += compare(map, n, tab + ((x + 1) * map->height + y));
    if (y != 0)
      sum += compare(map, n, tab + (x * map->height + y - 1));
    if (y != map->height - 1)
      sum += compare(map, n, tab + (x * map->height + y + 1));
    if (sum)
      return;
    n->marked = 1;
    n = get_min(map, tab);
    continue;//TODO del this after
    for (int j = 0; j < map->height; j++)
      printf("%6d ", j);
    printf("\n");
    for (int i = 0; i < map->width; i++)
    {
      for (int j = 0; j < map->height; j++)
      {
        if (tab[i * map->height + j].marked)
          printf("%6.1f ", tab[i * map->height + j].cost);
        else printf("   .   ");
      }
      printf("\n");
    }
  }
}
