/**
 * CMSC 212, 2008 Fall, Project #5
 * Public Test #1, public01.c
 * 
 * Tests int-list.c's get_keys() and get_values() functions.
 *
 * Link with int-list.o table implementation.
 */

#include <malloc.h>
#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>
#include "int-list.h"

static void memory_leak_check();
static void test_function();

int main() {
  memory_leak_check();
  return 0;
}

static void memory_leak_check() {
  unsigned int memory_used;

  mcheck_pedantic(NULL);
  memory_used= mallinfo().uordblks;
  test_function();
  memory_used= mallinfo().uordblks - memory_used;

  if (memory_used != 0)
    printf("Memory leak detected (%d bytes)\n", memory_used);
  else printf("No memory leak detected.\n");
}

static void test_function() {
  int keys[]= {1, 2, 3, 4, 5};
  int vals[]= {2, 3, 5, 7, 11};
  int i, sz;
  Table table;
  int *arr;

  table= create();
  for (i= 0; i < sizeof(keys) / sizeof(*keys); i++)
    insert(&table, keys[i], vals[i]);

  arr= get_keys(table);
  for (i= 0; i < size(table); i++)
    printf("Key = %d\n", arr[i]);
  free(arr);

  arr= get_values(table, &sz);
  for (i= 0; i < sz; i++)
    printf("Value = %d\n", arr[i]);
  free(arr);

  clear(&table);
}
