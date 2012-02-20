/**
 * CMSC 212, 2008 Fall, Project #3
 * Public Test #9, public09.c
 * 
 * Tests compare() a few ways.
 */

#include <stdio.h>
#include "string.h"
#include "node.h"

int main() {
  Linked_string s, t;
  char *str1 = "cheezburger", *str2 = "cheeseburger", *str3 = "cheese";

  init(&s);
  init(&t);
  copy_from_char_array(&s, str1);
  copy_from_char_array(&t, str2);
  printf("compare(\"%s\", \"%s\") = %d\n", str1, str2, compare(s, t));
  printf("compare(\"%s\", \"%s\") = %d\n", str2, str1, compare(t, s));
  printf("compare(\"%s\", \"%s\") = %d\n", str2, str2, compare(t, t));
  copy_from_char_array(&s, str3);
  printf("compare(\"%s\", \"%s\") = %d\n", str3, str2, compare(s, t));
  clear(&s);
  clear(&t);

  return 0;
}
