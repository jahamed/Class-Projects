#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

/**
 * CMSC 212, 2008 Fall, Project #4
 * Public Test #12, public12.c
 *
 * Tests evaluate()'s persistent state for storing variables.
 */

static void test_failed(int line_no);

int main(int argc, char **argv) {

  AST_node *expr1, *expr2, *expr3;
  
  Eval_return ret_status;
  Value val;

  expr1= create_variable_node("x");

  expr2= create_operator_node(ASSIGN,
            create_variable_node("x"),
            create_int_constant_node(3));

  expr3= create_operator_node(TIMES,
            create_double_constant_node(2.01),
            create_variable_node("x"));

  ret_status= evaluate(expr1, &val);
  if(ret_status != NOT_EVALUATED)
    test_failed(__LINE__);

  ret_status= evaluate(expr2, &val);
  if(ret_status != EVALUATED || val.value_type != IS_INT_VALUE ||
      val.number.int_value != 3)
    test_failed(__LINE__);

  ret_status= evaluate(expr1, &val);
  if(ret_status != EVALUATED || val.value_type != IS_INT_VALUE ||
      val.number.int_value != 3)
    test_failed(__LINE__);

  ret_status= evaluate(expr3, &val);
  if(ret_status != EVALUATED || val.value_type != IS_DOUBLE_VALUE ||
      val.number.double_value - 6.03 > 0.0001)
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
