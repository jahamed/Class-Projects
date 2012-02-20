/**
 * CMSC 212, 2008 Fall, Project #5
 * Public Test #15, public15.c
 * 
 * Checks if NULL pointers are handled correctly.
 *
 * Link with list.o table implementation.
 */

#include <malloc.h>
#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

static void memory_leak_check(void (*function)());
static void test_function();
static int compare_strings(const void *a, const void *b);

int main() {
  memory_leak_check(test_function);
  return 0;
}

static void memory_leak_check(void (*function)()) {
  unsigned int memory_used;

  mcheck_pedantic(NULL);
  memory_used= mallinfo().uordblks;
  function();
  memory_used= mallinfo().uordblks - memory_used;

  if (memory_used != 0)
    printf("Memory leak detected (%d bytes)\n", memory_used);
  else printf("No memory leak detected.\n");
}

static void test_function() {
  Table t;
  void *ptr;
  
  reset(NULL);
  clear(NULL);
  t= create(compare_strings, NULL, compare_strings, NULL);
  get_values(t, NULL);
  printf("delete() = % d\n", delete(NULL, "key"));
  printf("delete() = % d\n", delete(NULL, NULL));
  printf("lookup() = % d\n", lookup(t, NULL, &ptr));
  printf("lookup() = % d\n", lookup(t, "key", NULL));
  printf("insert() = % d\n", insert(&t, NULL, "value"));
  printf("lookup() = % d\n", lookup(t, NULL, NULL));
  printf("delete() = % d\n", delete(&t, NULL));
  printf("delete() = % d\n", delete(&t, NULL));
  printf("lookup() = % d\n", lookup(t, NULL, NULL));
  printf("insert() = % d\n", insert(NULL, "key", "value"));
  printf("insert() = % d\n", insert(&t, "key", NULL));
  printf("insert() = % d\n", insert(&t, NULL, NULL));
  printf("insert() = % d\n", insert(NULL, "key", NULL));
  printf("insert() = % d\n", insert(NULL, NULL, "value"));
  printf("insert() = % d\n", insert(NULL, NULL, NULL));
  clear(&t);
}

static int compare_strings(const void *a, const void *b) {
  if (a == b)
    return 0;
  if (a == NULL)
    return -1;
  if (b == NULL)
    return 1;
  return strcmp(a, b);
}
