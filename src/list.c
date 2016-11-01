#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "control.h"

struct list *g_list = NULL;

struct list *list_add(struct list *l, float x, float y)
{
  struct vector2 *v = malloc(sizeof (struct vector2));
  if (!v)
    return NULL;
  v->x = x;
  v->y = y;
  struct list *n = malloc(sizeof (struct list));
  //TODO verif (
  n->pos = v;
  n->next = l;
  n->prev = NULL;

  if (!l)
    return n;
  l->prev = n;
  return n;
}

struct list *list_rm(struct list *l)
{
  if (!l)
    return NULL;
  struct list *n = l->next;
  free(l->pos);
  free(l);
  return n;
}

void print_list(struct list *l)
{
  while (l)
  {
    printf("{x=%.2f y=%.2f}\n", l->pos->x, l->pos->y);
    l = l->next;
  }
}
