/**
 * CMSC 212, 2008 Fall, Project #5
 * Public Test #12, public12.c
 * 
 * Checks if get_keys() returns everything it should.
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
  char *keys[]= {
    "one", "two", "three", "four", "five", "six", "seven", "eight"
  };
  Table t;
  int i, j;
  char **arr;
  
  t= create(compare_strings, NULL, compare_strings, NULL);

  for (i= 0; i < sizeof(keys) / sizeof(*keys); i++)
    insert(&t, keys[i], "number");

  arr= (char **) get_keys(t);

  for (i= 0; i < size(t); i++) {
    int found= 0;

    for (j= 0; !found && j < sizeof(keys) / sizeof(*keys); j++)
      if (strcmp((char *) arr[i], keys[j]) == 0)
        found= 1;

    if (!found)
      printf("Key missing from get_keys() array.\n");
  }

  free(arr);

  clear(&t);
}

static int compare_strings(const void *a, const void *b) {
  return strcmp(a, b);
}
