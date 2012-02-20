#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

/**
 * CMSC 212, 2008 Fall, Project #4
 * Public Test #14, public14.c
 *
 * Tests evaluate()'s proper handling of invalid ASTs.
 */

static void test_failed(int line_no);

int main(int argc, char **argv) {

  AST_node *expr1, *expr2, *expr3;
  
  Eval_return ret_status;
  Value val;

  expr1= create_operator_node(DIVIDE,
            create_int_constant_node(3),
            create_double_constant_node(0));

  expr2= create_operator_node(POWER,
            create_int_constant_node(-2),
            create_double_constant_node(3.25));

  expr3= create_operator_node(ASSIGN_TIMES,
            create_double_constant_node(2.01),
            create_variable_node("x"));

  ret_status= evaluate(expr1, &val);
  if(ret_status != INVALID_AST)
    test_failed(__LINE__);

  ret_status= evaluate(expr2, &val);
  if(ret_status != INVALID_AST)
    test_failed(__LINE__);

  ret_status= evaluate(expr2, &val);
  if(ret_status != INVALID_AST)
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
