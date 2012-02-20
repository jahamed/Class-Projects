#include "table.h"
#include <malloc.h>
#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * CMSC 212, Fall 2008, Project #6
 * Public Test #5, public05.c
 *
 * Tests the array implementation, checking that the size and capacity upon
 * creation are correct per the project spec.
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

  assert_equals(0, size(t), __LINE__);
  assert_equals(10, current_capacity(t), __LINE__);

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
