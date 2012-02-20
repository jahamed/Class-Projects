#include "table.h"
#include <malloc.h>
#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * CMSC 212, Fall 2008, Project #6
 * Public Test #2, public02.c
 *
 * Tests create and clear methods on array implementation, checking for memory
 * leaks.
 *
 * Link with the array table implementation using shared libraries.
 */

static void memory_leak_check();
static void test_function();

static int void_comprar(const void *a, const void *b); 

int main(int argc, char **argv) {
  memory_leak_check();
  return 0;
}

void memory_leak_check() {
  unsigned int memory_used;

  mcheck_pedantic(NULL);
  memory_used= mallinfo().uordblks;
  test_function();
  memory_used= mallinfo().uordblks - memory_used;

  if (memory_used != 0)
    printf("Memory leak detected (%d bytes)\n", memory_used);
  else printf("No memory leak detected.\n");
}

void test_function() {
  Table t= create(void_comprar, NULL, void_comprar, NULL);
  clear(&t);
}

int void_comprar(const void *a, const void *b) {
  /* Just return 0, everything is equal. */
  return 0;
}
