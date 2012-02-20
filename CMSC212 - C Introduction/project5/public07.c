/**
 * CMSC 212, 2008 Fall, Project #5
 * Public Test #7, public07.c
 * 
 * Insert several items and call lookup() to see if correct data is in the
 * table and all return values are right.
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
  char *keys[] ={
    "two",
    "three",
    "five",
    "seven"
  };
  char *to_test[]= {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
  };
  int i, j;
  Table t;
  
  t= create(compare_strings, NULL, compare_strings, NULL);

  for (i= 0; i < sizeof(keys) / sizeof(*keys); i++)
    insert(&t, keys[i], "blah");

  for (i= 0; i < sizeof(to_test) / sizeof(*to_test); i++) {
    int ret_val= lookup(t, to_test[i], NULL);
    int correct_ret_val= -1;

    for (j= 0; correct_ret_val < 0 && j < sizeof(keys) / sizeof(*keys); j++)
      if (strcmp(keys[j], to_test[i]) == 0)
        correct_ret_val= 1;

    printf("\"%s\" %sfound", to_test[i], ret_val > 0 ? "" : "not ");
    printf(" - %scorrect.\n", ret_val == correct_ret_val ? "" : "in");
  }

  clear(&t);
}

static int compare_strings(const void *a, const void *b) {
  return strcmp(a, b);
}
