#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

/**
 * CMSC 212, 2008 Fall, Project #4
 * Public Test #13, public13.c
 *
 * Tests a more complex example of using variables and persistent states.  Also
 * shows how to swap two numbers without using a temp variable... :)
 */

static void test_failed(int line_no);

int main(int argc, char **argv) {

  AST_node *expr1, *expr2, *expr3, *expr4, *expr5;
  
  Eval_return ret_status;
  Value val;

  Value x_val;
  Value y_val;
  
  char *var_x = "x", *var_y = "y";

  expr1= create_operator_node(ASSIGN,
            create_variable_node(var_x),
            create_int_constant_node(10));

  expr2= create_operator_node(ASSIGN,
            create_variable_node(var_y),
            create_int_constant_node(2));

  expr3= create_operator_node(ASSIGN_PLUS,
            create_variable_node(var_x),
            create_variable_node(var_y));

  expr4= create_operator_node(ASSIGN,
            create_variable_node(var_y),
            create_operator_node(MINUS,
              create_variable_node(var_x),
              create_variable_node(var_y)));

  expr5= create_operator_node(ASSIGN_MINUS,
            create_variable_node(var_x),
            create_variable_node(var_y));

  ret_status= evaluate(expr1, &x_val);
  if(ret_status != EVALUATED || x_val.value_type != IS_INT_VALUE ||
      x_val.number.int_value != 10)
    test_failed(__LINE__);

  ret_status= evaluate(expr2, &y_val);
  if(ret_status != EVALUATED || y_val.value_type != IS_INT_VALUE ||
      y_val.number.int_value != 2)
    test_failed(__LINE__);

  printf("Value of %s is %2d, value of %s is %2d\n", var_x,
      x_val.number.int_value, var_y, y_val.number.int_value);

  ret_status= evaluate(expr3, &val);
  if(ret_status != EVALUATED || val.value_type != IS_INT_VALUE ||
      val.number.int_value != 12)
    test_failed(__LINE__);

  ret_status= evaluate(expr4, &y_val);
  if(ret_status != EVALUATED || y_val.value_type != IS_INT_VALUE ||
      y_val.number.int_value != 10)
    test_failed(__LINE__);

  ret_status= evaluate(expr5, &x_val);
  if(ret_status != EVALUATED || x_val.value_type != IS_INT_VALUE ||
      x_val.number.int_value != 2)
    test_failed(__LINE__);

  printf("Value of %s is %2d, value of %s is %2d\n", var_x,
      x_val.number.int_value, var_y, y_val.number.int_value);

  clear(&expr1);
  clear(&expr2);
  clear(&expr3);
  clear(&expr4);
  clear(&expr5);
  
  printf("Test passed!\n");

  return 0;
}

void test_failed(int line_no) {
  printf("Test failed at line number %d!\n", line_no);
  exit(1);
}
