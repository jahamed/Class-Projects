#if !defined(INT_LIST_H)
#define INT_LIST_H

#include "int-list-implementation.h"

typedef int (*Visit_fn)(int key, int data);

Table create(void);
void reset(Table *table);
int insert(Table *table, int key, int item);
int size(Table table);
int lookup(Table table, int key, int *item);
int *get_keys(Table table);
int *get_values(Table table, int *num_values);
void visit(Table table, Visit_fn visitor_fn);
int delete(Table *table, int key);
void clear(Table *table);

#endif
