#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

/**
 * CMSC 212, 2008 Fall, Project #4
 * Public Test #11, public11.c
 *
 * Tests evaluate() on single-operator trees.
 */

static void test_failed(int line_no);

int main(int argc, char **argv) {

  AST_node *expr1, *expr2, *expr3, *expr4;
  
  Eval_return ret_status;
  Value val;

  expr1= create_operator_node(PLUS,
            create_int_constant_node(3),
            create_int_constant_node(5));

  expr2= create_operator_node(MINUS,
            create_int_constant_node(3),
            create_double_constant_node(7.654));

  expr3= create_operator_node(POWER,
            create_int_constant_node(2),
            create_int_constant_node(8));

  expr4= create_operator_node(DIVIDE,
            create_variable_node("x"),
            create_int_constant_node(2));

  ret_status= evaluate(expr1, &val);
  if(ret_status != EVALUATED || val.value_type != IS_INT_VALUE ||
      val.number.int_value != 8)
    test_failed(__LINE__);

  ret_status= evaluate(expr2, &val);
  if(ret_status != EVALUATED || val.value_type != IS_DOUBLE_VALUE ||
      val.number.double_value != -4.654)
    test_failed(__LINE__);

  ret_status= evaluate(expr3, &val);
  if(ret_status != EVALUATED || val.value_type != IS_DOUBLE_VALUE ||
      val.number.double_value != 256.0)
    test_failed(__LINE__);

  ret_status= evaluate(expr4, &val);
  if(ret_status != NOT_EVALUATED)
    test_failed(__LINE__);

  clear(&expr1);
  clear(&expr2);
  clear(&expr3);
  clear(&expr4);
  
  printf("Test passed!\n");

  return 0;
}

void test_failed(int line_no) {
  printf("Test failed at line number %d!\n", line_no);
  exit(1);
}
