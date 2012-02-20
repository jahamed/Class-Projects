/**
 * CMSC 212, 2008 Fall, Project #3
 * Public Test #1, public01.c
 * 
 * Simple test of init(), append_char(), and print() functions.
 */

#include <stdio.h>
#include "string.h"
#include "node.h"

static void print_check(Linked_string s);

int main() {
  Linked_string s;
  char *str = "ABCDE";
  char *ptr;

  init(&s);
  for (ptr = str; *ptr != '\0'; ptr++) {
    append_char(&s, *ptr);
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
