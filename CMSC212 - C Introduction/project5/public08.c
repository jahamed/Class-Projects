/**
 * CMSC 212, 2008 Fall, Project #5
 * Public Test #8, public08.c
 * 
 * Insert several items and call visit with a function to make
 * sure everything is there.
 *
 * Link with list.o table implementation.
 */

#include <malloc.h>
#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

#define EPSILON 1e-6
#define DOUBLE_LIST { 1.61803, 3.14159, 2.71828 }

static void memory_leak_check();
static void test_function();
static int compare_doubles(const void *a, const void *b);
static int visitor(void *key, void *val);

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
  double keys[]= DOUBLE_LIST;
  int i;
  Table t;
  
  t= create(compare_doubles, NULL, compare_doubles, NULL);

  for (i= 0; i < sizeof(keys) / sizeof(*keys); i++)
    insert(&t, keys + i, keys);

  visit(t, visitor);

  clear(&t);
}

static int compare_doubles(const void *a, const void *b) {
  double diff= * (double *) a - * (double *) b;
  if ((diff < 0 ? -diff : diff) <= EPSILON)  /* fabs() w/o -lm */
    return 0;
  if (diff < 0)
    return -1;
  else return 1;
}

static int visitor(void *key, void *val) {
  static double targets[]= DOUBLE_LIST;
  static int missing_ct= sizeof(targets) / sizeof(*targets);
  int i;

  for (i= 0; i < missing_ct; i++)  /* Attempt to find key in target list */
    if (compare_doubles(targets + i, key) == 0) {
      printf("Found a target.\n");
      break;
    }

  if (i == missing_ct) {  /* Key not in list! */
    printf("Strange key in list.\n");
    return 1;
  }

  targets[i]= targets[--missing_ct];  /* Removes found element from list */

  return 0;
}
