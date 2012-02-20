#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

/**
 * CMSC 212, 2008 Fall, Project #4
 * Public Test #10, public10.c
 *
 * Tests evaluate() on single-node trees.
 */

static void test_failed(int line_no);

int main(int argc, char **argv) {

  AST_node *expr1, *expr2, *expr3;
  
  int node1= 4;
  double node2= 10.2;
  char *node3= "my_var";

  Eval_return ret_status;
  Value val;

  expr1= create_int_constant_node(node1);
  expr2= create_double_constant_node(node2);
  expr3= create_variable_node(node3);


  ret_status= evaluate(expr1, &val);
  if(ret_status != EVALUATED || val.value_type != IS_INT_VALUE ||
      val.number.int_value != node1)
    test_failed(__LINE__);

  ret_status= evaluate(expr2, &val);
  if(ret_status != EVALUATED || val.value_type != IS_DOUBLE_VALUE ||
      val.number.double_value != node2)
    test_failed(__LINE__);

  ret_status= evaluate(expr3, &val);
  if(ret_status != NOT_EVALUATED)
    test_failed(__LINE__);

  clear(&expr1);
  clear(&expr2);
  clear(&expr3);
  
  printf("Test passed!\n");

  return 0;
}

void test_failed(int line_no) {
  printf("Test failed at line number %d!\n", line_no);
  exit(1);
}
