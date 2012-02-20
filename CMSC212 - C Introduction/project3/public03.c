/**
 * CMSC 212, 2008 Fall, Project #3
 * Public Test #3, public03.c
 * 
 * Tests length() with a few strings.
 */

#include <stdio.h>
#include "string.h"
#include "node.h"

int main() {
  Linked_string s;
  char *strs[] = { "", "a", "bc", "def", "ghijklmnopqrstuvwxyz", NULL };
  char **ptr;

  init(&s);
  for (ptr = strs; *ptr != NULL; ptr++) {
    copy_from_char_array(&s, *ptr);
    printf("Length of \"%s\" = %d\n", *ptr, length(s));
  }
  clear(&s);

  return 0;
}
