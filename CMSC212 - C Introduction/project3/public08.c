/**
 * CMSC 212, 2008 Fall, Project #3
 * Public Test #8, public08.c
 * 
 * Tests that reset() sets string to empty string.
 */

#include <stdio.h>
#include "string.h"
#include "node.h"

static void print_check(Linked_string s);

int main() {
  Linked_string s;
  char *str = "interwebs";

  init(&s);
  copy_from_char_array(&s, str);
  reset(&s);
  print_check(s);
  clear(&s);

  return 0;
}

static void print_check(Linked_string s) {
  printf("Output = \"");
  print(s);
  printf("\"\n");
}
