#include "table.h"
#include <malloc.h>
#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * CMSC 212, Fall 2008, Project #6
 * Public Test #3, public03.c
 *
 * Tests the array implementation of insert and lookup.
 *
 * Link with the array table implementation using shared libraries.
 */

static void memory_leak_check();
static void test_function();

static void assert_equals(int truth, int putative, int line_no);
static int string_comprar(const void *a, const void *b);
static int int_comprar(const void *a, const void *b);

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
  const char* keys[]= {"donut", "eggplant", "banana", "apple", "coconut"};
  const int values[]= {5, 4, 10, 30, 6};
  const int num_keys= 5;
  void *value;

  t= create(string_comprar, NULL, int_comprar, NULL);

  /* Check if insert returns the right value */
  for (q= 0; q < num_keys; q++) {
    assert_equals(1, insert(&t, (void*)keys[q], (void*)(long)values[q]),
        __LINE__);
  }

  assert_equals(-1, insert(&t, (void*)keys[0], (void*)(long)values[0]),
      __LINE__);


  /* Check if lookup returns the proper value, and if the value set is
   * proper. */
  for (q= 0; q < num_keys; q++) {
    assert_equals(1, lookup(t, (void*)keys[q], &value), __LINE__);
    assert_equals(1, ((int)(long)value) == values[q], __LINE__);
  }

  assert_equals(-1, lookup(t, "grapefruit", &value), __LINE__);

  clear(&t);
}

void assert_equals(int truth, int putative, int line_no) {
  if (putative != truth) {
    printf("Expected %d, got %d at line %d\n", truth, putative, line_no);
  }
}

int string_comprar(const void *a, const void *b) {
  return strcmp(a, b);
}

int int_comprar(const void *a, const void *b) {
  if ((int)(long)a < (int)(long)b)
    return -1;
  if ((int)(long)a > (int)(long)b)
    return 1;
  return 0;
}
