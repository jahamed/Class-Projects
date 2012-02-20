/**
 * CMSC 212, 2008 Fall, Project #3
 * Public Test #10, public10.c
 * 
 * Tests find() with a few strings.
 */

#include <stdio.h>
#include "string.h"
#include "node.h"

int main() {
  Linked_string s, t;
  char *str1 = "indefatigable", *str2 = "gab", *str3 = "able", *str4 = "fat";

  init(&s);
  init(&t);
  copy_from_char_array(&s, str1);
  copy_from_char_array(&t, str2);
  printf("find(\"%s\", \"%s\") = %d\n", str1, str2, find(s, t));
  copy_from_char_array(&t, str3);
  printf("find(\"%s\", \"%s\") = %d\n", str1, str3, find(s, t));
  copy_from_char_array(&t, str4);
  printf("find(\"%s\", \"%s\") = %d\n", str1, str4, find(s, t));
  clear(&s);
  clear(&t);

  return 0;
}
