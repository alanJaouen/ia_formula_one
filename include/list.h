#ifndef H_LIST
#define H_LIST

extern struct list* g_list;

struct list
{
  struct vector2 *pos;
  struct list *next;
  struct list *prev;
};

struct list *list_add(struct list *l, float x, float y);

struct list *list_rm(struct list *l);

void print_list(struct list *l);

#endif /* !H_LIST*/
