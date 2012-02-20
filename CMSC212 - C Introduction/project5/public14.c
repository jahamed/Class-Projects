/**
 * CMSC 212, 2008 Fall, Project #5
 * Public Test #14, public14.c
 * 
 * Checks get_keys() on an empty table.
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
  void **keys;
  
  t= create(compare_strings, NULL, compare_strings, NULL);
  keys= get_keys(t);
  clear(&t);
}

static int compare_strings(const void *a, const void *b) {
  return strcmp(a, b);
}
