#include "table.h"
#include <malloc.h>
#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * CMSC 212, Fall 2008, Project #6
 * Public Test #4, public04.c
 *
 * Tests the array implementation of get_keys and get_values.
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
  void **key_list;
  void **value_list;
  int q;
  const char* keys[]= {"donut", "eggplant", "banana", "apple", "coconut"};
  const int values[]= {6, 4, 10, 30, 6};
  const int num_keys= 5;
  int num_values;

  t= create(string_comprar, NULL, int_comprar, NULL);

  /* First just insert some stuff. */
  for (q= 0; q < num_keys; q++) {
    insert(&t, (void*)keys[q], (void*)(long)values[q]);
  }

  /* Now test get_keys. */
  key_list= get_keys(t);
  for (q= 0; q < size(t); q++) {
    void *value;
    lookup(t, key_list[q], &value);
    printf("%s --> %d\n", (char*)key_list[q], (int)(long)value);
  }

  /* Now testing get_values. */
  value_list= get_values(t, &num_values);

  assert_equals(4, num_values, __LINE__);

  for (q= 0; q < num_values; q++) {
    printf("Value: %d\n", (int)(long)value_list[q]);
  }

  /* Free stuff. */
  clear(&t);
  free(key_list);
  free(value_list);
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
