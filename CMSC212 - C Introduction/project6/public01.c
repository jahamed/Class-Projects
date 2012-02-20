#include "table.h"
#include <limits.h>
#include <malloc.h>
#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * CMSC 212, Fall 2008, Project #6
 * Public Test #1, public01.c
 *
 * Tests the proper implementation of current_capacity for list.c
 *
 * Link with the list table implementation using shared libraries.
 */

static void memory_leak_check();
static void test_function();

static int int_comprar(const void *a, const void *b);
static int void_comprar(const void *a, const void *b);

static void check_capacity(Table *t, int correct_cap);

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
  Table t= create(int_comprar, NULL, void_comprar, NULL);
  int q;
  const int num_ints= 128;

  check_capacity(&t, INT_MAX);

  for (q= 0; q < num_ints; q++) {
    insert(&t, (void*)(long)q, NULL);
    check_capacity(&t, INT_MAX);
  }

  for (q= 0; q < num_ints; q++) {
    delete(&t, (void*)(long)q);
    check_capacity(&t, INT_MAX);
  }
  clear(&t);
}

int int_comprar(const void *a, const void *b) {
  if ((int)(long)a < (int)(long)b)
    return -1;
  if ((int)(long)a > (int)(long)b)
    return 1;
  return 0;
}

int void_comprar(const void *a, const void *b) {
  /* Just return 0, everything is equal. */
  return 0;
}

void check_capacity(Table *t, int correct_cap) {
  int cap= current_capacity(*t);
  if (cap != correct_cap) {
    printf("Capacity is %d, should be %d\n", cap, correct_cap);
    exit(1);
  }
}
