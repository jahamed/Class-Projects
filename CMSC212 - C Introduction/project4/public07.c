#include <stdio.h>

#include "ast.h"

/**
 * CMSC 212, 2008 Fall, Project #4
 * Public Test #7, public07.c
 *
 * Tests print_value() with some different combinations of field values.
 */

int main(int argc, char **argv) {

  Value v1, v2, v3, v4;

  v1.value_type= IS_INT_VALUE;
  v2.value_type= IS_DOUBLE_VALUE;
  v3.value_type= IS_INT_VALUE;
  v4.value_type= IS_DOUBLE_VALUE;

  v1.number.int_value= -7;
  v2.number.double_value= 4.2103;
  v3.number.int_value= 4;
  v4.number.double_value= -1234.56789;

  print_value(v1); printf("\n");
  print_value(v2); printf("\n");
  print_value(v3); printf("\n");
  print_value(v4); printf("\n");

  return 0;
}
