/**
 * CMSC 212, 2008 Fall, Project #5
 * Public Test #13, public13.c
 * 
 * Checks if get_values() returns everything it should.
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

typedef struct {
  char *name;
  int wins;
  int losses;
} Team;

static void memory_leak_check();
static void test_function();
static int compare_strings(const void *a, const void *b);
static int compare_teams(const void *a, const void *b);

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
  Team teams[]= {
    { "Boston",      72, 90 },
    { "Kansas City", 74, 86 },
    { "Detroit",     88, 74 },
    { "Chicago",     83, 79 },
    { "Cleveland",   81, 81 },
    { "Minnesota",   89, 73 },
    { "Washington",  71, 88 },
    { "California",  80, 82 },
    { "Baltimore",   97, 63 },
    { "New York",    70, 89 },
  };
  Table t;
  Team **standings;
  int i, j, count;

  
  t= create(compare_strings, NULL, compare_teams, NULL);

  for (i= 0; i < sizeof(teams) / sizeof(*teams); i++)
    insert(&t, teams[i].name, teams + i);
  standings= (Team **) get_values(t, &count);

  for (i= count - 1; i >= 0; i--) {
    int found= 0;

    for (j= 0; !found && j < sizeof(teams) / sizeof(*teams); j++)
      if (compare_teams(standings[i], teams + j) == 0)
        found= 1;

    if (!found)
      printf("Value missing from get_values() array.\n");
  }

  free(standings);

  clear(&t);
}

static int compare_strings(const void *a, const void *b) {
  return strcmp(a, b);
}

static int compare_teams(const void *a, const void *b) {
  Team x= * (Team *) a;
  Team y= * (Team *) b;
  double x_pct= (x.wins * 1.0) / (x.wins + x.losses);
  double y_pct= (y.wins * 1.0) / (y.wins + y.losses);
  double diff= x_pct - y_pct;

  if ((diff < 0 ? -diff : diff) < EPSILON)
    return 0;
  if (diff < 0)
    return -1;
  else return 1;
}
