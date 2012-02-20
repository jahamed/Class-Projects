#if !defined(TABLE_H)
#define TABLE_H

typedef int (*Key_compare_fn)(const void *x, const void *y);
typedef void (*Key_delete_fn)(void *p);
typedef int (*Data_compare_fn)(const void *x, const void *y);
typedef void (*Data_delete_fn)(void *p);
typedef int (*Visit_fn)(void *key, void *data);

typedef struct table {
  Key_compare_fn key_compare_fn;
  Key_delete_fn key_delete_fn;
  Data_compare_fn data_compare_fn;
  Data_delete_fn data_delete_fn;
  void *contents;
} Table;

Table create(Key_compare_fn compare_key, Key_delete_fn delete_key,
             Data_compare_fn compare_data, Data_delete_fn delete_data);
void reset(Table *table);
int insert(Table *table, void *key, void *item);
int size(Table table);
int lookup(Table table, void *key, void **item);
void **get_keys(Table table);
void **get_values(Table table, int *num_values);
void visit(Table table, Visit_fn visitor_fn);
int delete(Table *table, void *key);
void clear(Table *table);

#endif
