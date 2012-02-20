/**
 * CMSC 212, 2008 Fall, Project #3
 * Public Test #16, public16.c
 * 
 * Tests clear(), checks for memory leaks.
 */

#include <stdio.h>
#include <malloc.h>
#include <mcheck.h>
#include "string.h"
#include "node.h"

static void print_check(Linked_string s);

int main() {
  Linked_string s;
  char *str = "ephemeral";
  int memory_used;

  mcheck_pedantic(NULL);
  memory_used = mallinfo().uordblks;  /* current free memory */

  init(&s);
  copy_from_char_array(&s, str);
  print_check(s);
  printf("clear(s)\n");
  clear(&s);

  memory_used = mallinfo().uordblks - memory_used;

  if (memory_used != 0)
    printf("Memory leak detected (%d bytes)\n", memory_used);
  else
    printf("No leak detected.\n");

  return 0;
}

static void print_check(Linked_string s) {
  printf("Output = \"");
  print(s);
  printf("\"\n");
}
