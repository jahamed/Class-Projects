/**
 * CMSC 212, 2008 Fall, Project #3
 * Public Test #2, public02.c
 * 
 * Tests copy_from_char_array() and print() with a few strings.
 */

#include <stdio.h>
#include "string.h"
#include "node.h"

static void print_check(Linked_string s);

int main() {
  Linked_string s;
  char *strs[] = { "A", "B", "CD", "EFG", "HIJKL", NULL };
  char **ptr;

  init(&s);
  for (ptr = strs; *ptr != NULL; ptr++) {
    copy_from_char_array(&s, *ptr);
    print_check(s);
  }
  clear(&s);

  return 0;
}

static void print_check(Linked_string s) {
  printf("Output = \"");
  print(s);
  printf("\"\n");
}
