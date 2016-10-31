#include <stdlib.h>
#include "list.h"
#include "control.h"

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
  n->next = NULL;
  n->prev = NULL;

  if (!l)
    return n;
  struct list *m = l;
  while (m->next)
    m = m->next;
  m->next = n;
  n->prev = m;
  return l;
}

void list_rm(struct list *l)
{
  if (!l)
    return;
  if (l->prev)
    l->prev->next = l->next;
  if (l->next)
    l->next->prev = l->prev;
  free(l->pos);
  free(l);
}

