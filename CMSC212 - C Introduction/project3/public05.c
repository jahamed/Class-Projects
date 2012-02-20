/**
 * CMSC 212, 2008 Fall, Project #3
 * Public Test #5, public05.c
 * 
 * Tests copy() a few times.
 */

#include <stdio.h>
#include "string.h"
#include "node.h"

static void print_check(Linked_string s);

int main() {
  Linked_string s, t;
  char *strs[] = { "a", "B", "c", "D", "e", NULL };
  char **ptr;

  init(&s);
  init(&t);
  for (ptr = strs; *ptr != NULL; ptr++) {
    copy_from_char_array(&t, *ptr);
    copy(&s, t);
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
