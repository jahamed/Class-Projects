/**
 * CMSC 212, 2008 Fall, Project #5
 * Public Test #11, public11.c
 * 
 * Check that delete() doesn't delete keys it shouldn't.
 *
 * Link with list.o table implementation.
 */

#include <malloc.h>
#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

static void memory_leak_check();
static void test_function();
static int compare_strings(const void *a, const void *b);

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
  Table t;
  int ret_val;
  
  t= create(compare_strings, NULL, compare_strings, NULL);
  ret_val= insert(&t, "key", "value");
  printf("insert() = %d\n", ret_val);
  ret_val= insert(&t, "other key", "value");
  printf("insert() = %d\n", ret_val);
  ret_val= delete(&t, "bad key");
  printf("delete() = %d\n", ret_val);
  ret_val= lookup(t, "key", NULL);
  printf("lookup() = %d\n", ret_val);
  printf("size() = %d\n", size(t));

  clear(&t);
}

static int compare_strings(const void *a, const void *b) {
  return strcmp(a, b);
}
