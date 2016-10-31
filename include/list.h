#ifndef H_LIST
#define H_LIST

struct list
{
  struct vector2 *pos;
  struct list *next;
  struct list *prev;
};

struct list *list_add(struct list *l, float x, float y);

void list_rm(struct list *l);

#endif /* !H_LIST*/
