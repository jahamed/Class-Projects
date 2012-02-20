/**
 * CMSC 212, 2008 Fall, Project #3
 * Public Test #12, public12.c
 * 
 * Tests search_in().
 */

#include <stdio.h>
#include "string.h"
#include "node.h"

int main() {
  Linked_string s, t;
  char *str1 = "chihuahua", *str2 = "mouse";

  init(&s);
  init(&t);
  copy_from_char_array(&s, str1);
  copy_from_char_array(&t, str2);
  printf("search_in(\"%s\", \"%s\") = %d\n", str1, str2, search_in(s, t));
  clear(&s);
  clear(&t);

  return 0;
}
