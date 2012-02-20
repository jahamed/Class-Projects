/**
 * CMSC 212, 2008 Fall, Project #3
 * Public Test #15, public15.c
 * 
 * Tests append(s, s).  Same string used for both arguments.
 */

#include <stdio.h>
#include "string.h"
#include "node.h"

static void print_check(Linked_string s);

int main() {
  Linked_string s;
  char *str = "redundant";

  init(&s);
  copy_from_char_array(&s, str);
  print_check(s);
  append(&s, s);
  print_check(s);
  clear(&s);

  return 0;
}

static void print_check(Linked_string s) {
  printf("Output = \"");
  print(s);
  printf("\"\n");
}
