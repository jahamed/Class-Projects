/**
 * CMSC 212, 2008 Fall, Project #5
 * Public Test #9, public09.c
 * 
 * Check that multiple insertions on the same key don't overwrite data and
 * don't change size.
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
  char *str;
  
  t= create(compare_strings, NULL, compare_strings, NULL);
  ret_val= insert(&t, "key", "value");
  printf("insert() = %d\n", ret_val);
  ret_val= insert(&t, "key", "WRONG");
  printf("insert() = %d\n", ret_val);
  ret_val= lookup(t, "key", (void **) &str);
  printf("lookup() = %d; item = \"%s\"\n", ret_val, str);
  printf("size() = %d\n", size(t));

  clear(&t);
}

static int compare_strings(const void *a, const void *b) {
  return strcmp(a, b);
}
