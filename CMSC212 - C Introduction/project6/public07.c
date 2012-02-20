#include "table.h"
#include <malloc.h>
#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * CMSC 212, Fall 2008, Project #6
 * Public Test #7, public07.c
 *
 * Tests insert when inserting the same key multiple times, ensuring that the
 * original value was kept.
 *
 * Link with the array table implementation using shared libraries.
 */

static void memory_leak_check();
static void test_function();

static void assert_equals(int truth, int putative, int line_no);
static int int_comprar(const void *a, const void *b);
static int dummy_comprar(const void *a, const void *b);
static int fib(int n);

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
  Table t= create(int_comprar, NULL, dummy_comprar, NULL);
  int q;
  const int num_entries= 20;
  void *value;

  for (q= 0; q < num_entries; q++) {
    insert(&t, (void*)(long)fib(q), (void*)(long)q);
  }

  /* Check the key 1, to see what value is being stored. */
  lookup(t, (void*)(long)1, &value);

  /* It should be designated the 1st fibonacci number, not the second based
   * upon the way insert works. */
  assert_equals(0, int_comprar((void*)(long)1, value), __LINE__);

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

/* Returns the nth fibonacci number. */
int fib(int n) {
  if (n == 0 || n == 1) return n;
  return fib(n-1) + fib(n-2);
}
