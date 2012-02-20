#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

/**
 * CMSC 212, 2008 Fall, Project #4
 * Public Test #15, public15.c
 *
 * Tests evaluate()'s one some complex examples.
 */

static void test_failed(int line_no);

int main(int argc, char **argv) {

  AST_node *expr1, *expr2, *expr3, *expr4;
  
  Eval_return ret_status;
  Value val;

  expr1= create_operator_node(ASSIGN,
            create_variable_node("x"),
            create_int_constant_node(1));

  expr2= create_operator_node(MINUS,
            create_operator_node(TIMES,
              create_int_constant_node(4),
              create_operator_node(PLUS,
                create_int_constant_node(3),
                create_int_constant_node(5))),
            create_operator_node(PLUS,
              create_int_constant_node(2),
              create_variable_node("x")));

  expr3= create_operator_node(ASSIGN_PLUS,
            create_variable_node("x"),
            create_int_constant_node(1));

  expr4= create_operator_node(TIMES,
            create_int_constant_node(10),
            create_operator_node(POWER,
              create_int_constant_node(3),
              create_operator_node(TIMES,
                create_double_constant_node(0.5),
                create_variable_node("x"))));

  ret_status= evaluate(expr1, &val);
  if(ret_status != EVALUATED || val.value_type != IS_INT_VALUE ||
      val.number.int_value != 1)
    test_failed(__LINE__);

  ret_status= evaluate(expr2, &val);
  if(ret_status != EVALUATED || val.value_type != IS_INT_VALUE ||
      val.number.int_value != 29)
    test_failed(__LINE__);

  ret_status= evaluate(expr3, &val);
  if(ret_status != EVALUATED || val.value_type != IS_INT_VALUE ||
      val.number.int_value != 2)
    test_failed(__LINE__);

  ret_status= evaluate(expr4, &val);
  if(ret_status != EVALUATED || val.value_type != IS_DOUBLE_VALUE ||
      val.number.int_value - 30 > 0.0001)
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
