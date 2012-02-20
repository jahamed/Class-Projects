#if !defined(LIST_H)
#define LIST_H

typedef struct list_node {
  void *key;
  void *data;
  struct list_node *next;
} List_node;

typedef struct list {
  List_node *head;
} List;

#endif
