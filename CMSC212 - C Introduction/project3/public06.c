/**
 * CMSC 212, 2008 Fall, Project #3
 * Public Test #6, public06.c
 * 
 * Tests safe_append() a few times.
 */

#include <stdio.h>
#include "string.h"
#include "node.h"

static void print_check(Linked_string s);

int main() {
  Linked_string s, t;
  char *strs[] = { "disc", "oven", "error", NULL };
  char **ptr;

  init(&s);
  init(&t);
  copy_from_char_array(&s, *strs);
  print_check(s);
  for (ptr = strs + 1; *ptr != NULL; ptr++) {
    copy_from_char_array(&t, *ptr);
    safe_append(&s, t, 2);
    print_check(s);
  }
  clear(&s);
  clear(&t);

  return 0;
}

static void print_check(Linked_string s) {
  printf("Output = \"");
  print(s);
  printf("\"\n");
}
