/**
 * CMSC 212, 2008 Fall, Project #5
 * Public Test #4, public04.c
 * 
 * Simple test with just create() and clear().  Make sure no memory leaks or
 * segmentation faults occur.
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
  Table t= create(compare_strings, NULL, compare_strings, NULL);
  clear(&t);
}

static int compare_strings(const void *a, const void *b) {
  return strcmp(a, b);
}
