/**
 * CMSC 212, 2008 Fall, Project #3
 * Public Test #11, public11.c
 * 
 * Tests find_char().
 */

#include <stdio.h>
#include "string.h"
#include "node.h"

int main() {
  Linked_string s;
  Node *np;
  char *str1 = "abcd", target = 'c';

  init(&s);
  copy_from_char_array(&s, str1);
  np = find_char(s, target);
  printf("find_char(\"%s\", '%c') = [%c]->[%c]\n", str1, target, np->ch,
      np->next->ch);
  clear(&s);

  return 0;
}
