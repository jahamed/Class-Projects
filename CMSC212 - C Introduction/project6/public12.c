#include "table.h"
#include <malloc.h>
#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * CMSC 212, Fall 2008, Project #6
 * Public Test #12, public12.c
 *
 * Tests the growing of an array, making sure its capacity is updated as it
 * expands from the initial 10.
 *
 * Link with the array table implementation using shared libraries.
 */

static void memory_leak_check();
static void test_function();

static void assert_equals(int truth, int putative, int line_no);
static int int_comprar(const void *a, const void *b);
static int dummy_comprar(const void *a, const void *b);

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
  Table t;
  int q;
  const int num_to_insert= 14;

  t= create(int_comprar, NULL, dummy_comprar, NULL);

  for (q= 0; q < num_to_insert; q++) {
    insert(&t, (void*)(long)q, NULL);
  }

  assert_equals(num_to_insert, size(t), __LINE__);

  /* Table capacity should have doubled from the original 10. */
  assert_equals(20, current_capacity(t), __LINE__);

  clear(&t);
}

void assert_equals(int truth, int putative, int line_no) {
  if (putative != truth) {
    printf("Expected %d, got %d at line %d\n", truth, putative, line_no);
  }
}

int int_comprar(const void *a, const void *b) {
  if ((int)(long)a < (int)(long)b)
    return -1;
  if ((int)(long)a > (int)(long)b)
    return 1;
  return 0;
}

/* Just a dummy comparison function, no sorting! */
int dummy_comprar(const void *a, const void *b) {
  return 0;
}
