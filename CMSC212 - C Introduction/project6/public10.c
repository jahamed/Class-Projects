#include "table.h"
#include <malloc.h>
#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * CMSC 212, Fall 2008, Project #6
 * Public Test #10, public10.c
 *
 * Tests the delete function is called on each element of the list when clear
 * and reset are called.
 *
 * Exact same test as in public09, just with the list implementation instead of
 * array.
 *
 * Link with the list table implementation using shared libraries.
 */

static void memory_leak_check();
static void test_function();

static int string_comprar(const void *a, const void *b);
static void string_delete(void *str);
static void dummy_string_delete(void *str);
static void populate_table(Table *t, void **values, int num);
static void check_alloc(void *p);

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
  Table t= create(string_comprar, string_delete, string_comprar,
      dummy_string_delete);
  const char *values[]= {"BWI: Baltimore, MD", "BOS: Boston, MA",
                          "IAD: DC - Dulles", "DCA: DC - Reagan National",
                          "PHI: Philadelphia, PA", "JFK: New York, NY"};
  const int num_entries= 6;

  populate_table(&t, (void**)values, num_entries);

  reset(&t);

  populate_table(&t, (void**)values, num_entries);

  clear(&t);
}

int string_comprar(const void *a, const void *b) {
  return strcmp(a, b);
}

/* We allocated the string somewhere, so free it! */
void string_delete(void *str) {
  free(str);
}

void dummy_string_delete(void *str) {
  static int count= 1;
  printf("This is string #%d that I've deleted.\n", count++);
}

void populate_table(Table *t, void **values, int num) {
  int q;

  for (q= 0; q < num; q++) {
    /* Create space for the three letter acronym, plus null terminator. */
    char *key= calloc(4, sizeof(char));
    check_alloc(key);
    strncpy(key, values[q], 3);

    insert(t, (void*)key, (void*)values[q]);
  }
}

void check_alloc(void *p) {
  if (p == NULL) {
    fprintf(stderr, "Error: couldn't allocate memory.\n");
    exit(1);
  }
}
