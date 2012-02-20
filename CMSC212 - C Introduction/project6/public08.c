#include "table.h"
#include <malloc.h>
#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * CMSC 212, Fall 2008, Project #6
 * Public Test #8, public08.c
 *
 * Tests proper functionality of delete using array implementation, including
 * testing return values.
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
  Table t= create(string_comprar, NULL, int_comprar, NULL);
  int q;
  const char* keys[]= {"donut", "eggplant", "banana", "apple", "coconut"};
  const int values[]= {5, 4, 10, 30, 6};
  const int num_entries= 5;

  /* Populate the array first. */
  for (q= 0; q < num_entries; q++) {
    insert(&t, (void*)keys[q], (void*)(long)values[q]);
  }

  /* Check delete for a couple of cases. */
  assert_equals(-1, delete(&t, "not in the array!"), __LINE__);

  for (q= 0; q < num_entries; q++) {
    assert_equals(1, delete(&t, (void*)keys[q]), __LINE__);
  }

  assert_equals(-1, delete(&t, "still not in the array!"), __LINE__);

  /* Size should be 0, since we (hopefully) deleted all the elements from the
   * array. */
  assert_equals(0, size(t), __LINE__);

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
